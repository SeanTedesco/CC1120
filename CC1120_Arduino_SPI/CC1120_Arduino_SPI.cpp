/******************************************************************************
 * INCLUDES
 */

#include "CC1120_Arduino_SPI.h"

/******************************************************************************
 * FUNCTIONS
 */
/******************************************************************************
 * @fn          spiInterfaceInit
 *
 * @brief       Function to initialize SPI on Arduino. CC112 operates at 
 *              a 40 MHz, but Arduino support a maximum of 16 MHz.
 *              CC112x operates on SPI_MODE0 and MSBFIRST
 *
 * @param       speedMaximum - The maximum speed of communication.
 * @param       dataOrder - MSBFIRST or LSBFIRST
 * @param       dataMode - SPI_MODE0, SPI_MODE1, SPI_MODE2, or SPI_MODE3
 *
 * @return      void
 */
void spiInterfaceInit()
{
  cc_spi_settings = SPISettings(4000000, MSBFIRST, SPI_MODE0);
}
/******************************************************************************
 * @fn          writeSettings
 *
 * @brief       Writes byte value to each of the configuration registers 
 *              specified in settings array. 
 *
 * @param       settings - array of registerSetting_t objects. Each object must   
 *                          have address and data bytes. 
 *
 * @return      void
 */
void writeSettings(registerSetting_t *settings){
  uint8 statusByte;
  uint8 marcstate;

  radio.registerConfig(settings, sizeof(settings)/sizeof(registerSetting_t));

  statusByte = radio.ccReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("register conf: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}
/*******************************************************************************
*   @fn         registerConfig
*
*   @brief      Write register settings as given by SmartRF Studio found in
*               cc112x_easy_link_reg_config.h
*
*   @param      setting - the setting to be written (address and data)
*   @param      len - length of the array of settings to be written
*
*   @return     none
*/
void registerConfig(registerSetting_t * setting, uint16 len) {
    uint8 writeByte;

    // Reset radio
    ccStrobeCommand(CC112X_SRES);

    delay(1000); // TODO This is probably generous. See if can be lowered.

    // Write registers to radio
    for(uint16 i = 0; i < len; i++) {
        writeByte = s[i].data;
        ccWriteReg(s[i].addr, &writeByte, 1);
    }

    for(uint16 i = 0; i < len; i++) {
        ccReadReg(s[i].addr, &writeByte, 1);
        Serial.println(writeByte, HEX);
    }
}
/*******************************************************************************
 * @fn          ccStrobeCommand
 *
 * @brief       Send command strobe to the radio. Returns status byte read
 *              during transfer of command strobe. Validation of provided
 *              is not done. Function assumes chip is ready.
 *
 * @param       cmd - command strobe
 *
 * @return      status byte
 */
status_t ccStrobeCommand(uint8 cmd)
{
  uint8 rc;
  SPI.beginTransaction(cc_spi_settings);
  digitalWrite(CC112X_CHIP_SELECT, LOW); // Bring chip select low to start

  rc = SPI.transfer(cmd);

  digitalWrite(CC112X_CHIP_SELECT, HIGH); // Bring chip select high to stop
  SPI.endTransaction();

  return rc;
}

/******************************************************************************
 * @fn          ccReadReg
 *
 * @brief       Read value(s) from config/status/extended radio register(s).
 *              If len  = 1: Reads a single register
 *              if len != 1: Reads len register values in burst mode
 *
 * @param       addr   - address of first register to read
 * @param       *pData - pointer to data array where read bytes are saved
 * @param       len   - number of bytes to read
 *
 * output parameters
 *
 * @return      status_t
 */
status_t ccReadReg(uint16 addr, uint8 *pData, uint8 len)
{
  uint8 tempExt  = (uint8)(addr>>8);
  uint8 tempAddr = (uint8)(addr & 0x00FF);
  uint8 rc;

  /* Checking if this is a FIFO access -> returns chip not ready  */
  if((CC112X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;

  /* Decide what register space is accessed */
  if(!tempExt)
  {
    rc = registerAccess_8B((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempAddr,pData,len);
  }
  else if (tempExt == 0x2F)
  {
    rc = registerAccess_16B((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempExt,tempAddr,pData,len);
  }
  return (rc);
}
/******************************************************************************
 * @fn          ccWriteReg
 *
 * @brief       Write value(s) to config/status/extended radio register(s).
 *              If len  = 1: Writes a single register
 *              if len  > 1: Writes len register values in burst mode
 *
 * input parameters
 *
 * @param       addr   - address of first register to write
 * @param       *pData - pointer to data array that holds bytes to be written
 * @param       len    - number of bytes to write
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
status_t ccWriteReg(uint16 addr, uint8 *pData, uint8 len)
{
  uint8 tempExt  = (uint8)(addr>>8);
  uint8 tempAddr = (uint8)(addr & 0x00FF);
  uint8 rc;

  /* Checking if this is a FIFO access - returns chip not ready */
  if((CC112X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;

  /* Decide what register space is accessed */
  if(!tempExt)
  {
    rc = registerAccess_8B((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempAddr,pData,len);
  }
  else if (tempExt == 0x2F)
  {
    rc = registerAccess_16B((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempExt,tempAddr,pData,len);
  }
  return (rc);
}
/*******************************************************************************
 * @fn          registerAccess_8B
 *
 * @brief       Read or write from / to an 8 bit register (normal address space).
 *              The function handles burst and single read / write as specfied in
 *              addrByte. Function assumes that chip is ready.
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS / RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS / RADIO_READ_ACCESS.
 * @param       addrByte - address byte of register.
 * @param       pData    - data array
 * @param       len      - Length of array to be read(TX) / written(RX)
 *
 * @return      chip status
 */
status_t registerAccess_8B(uint8 accessType, uint8 addrByte, uint8 *pData, uint8 len)
{
  uint8 returnValue; 

  SPI.beginTransaction(cc_spi_settings);   
  digitalWrite(CC112X_CHIP_SELECT, LOW);    // bring chip select low to start comms

  returnValue = SPI.transfer(accessType | addrByte);    // write the address we are accessing
  ccReadWriteBurstSingle(accessType | addrByte, pData, len);    // read or write data

  digitalWrite(CC112X_CHIP_SELECT, HIGH); // Bring chip select high to stop
  SPI.endTransaction();

  return returnValue;
}
/******************************************************************************
 * @fn          registerAccess_16B
 *
 * @brief       Read or write in the extended adress space of CC112X.
 *              The function handles burst and single read / write as specified
 *              in addrByte. Function assumes that chip is ready. 
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       extAddr - Extended register space address = 0x2F.
 * @param       regAddr - Register address in the extended address space.
 * @param       *pData  - Pointer to data array for communication
 * @param       len     - Length of bytes to be read/written from/to radio
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
status_t registerAccess_16B(uint8 accessType, uint8 extAddr, uint8 regAddr, uint8 *pData, uint8 len)
{
  uint8 returnValue;

  SPI.beginTransaction(cc_spi_settings);    
  digitalWrite(CC112X_CHIP_SELECT, LOW);    // bring chip select low to start

  returnValue = SPI.transfer(accessType|extAddr);   // command to access extended registers
  SPI.transfer(regAddr);    // The first byte following this command is interpreted as the extended address
  ccReadWriteBurstSingle(accessType|extAddr, pData, len);   // Exactly one data byte is expected after the extended address byte

  digitalWrite(CC112X_CHIP_SELECT, HIGH); // Bring chip select high to stop
  SPI.endTransaction();

  return returnValue;
}
/*******************************************************************************
 * @fn          trxReadWriteBurstSingle
 *
 * @brief       When the address byte is sent to the SPI slave, the next byte
 *              communicated is the data to be written or read. The address
 *              byte that holds information about read/write -and single/
 *              burst-access is provided to this function.
 *
 *              Depending on these two bits this function will write len bytes to
 *              the radio in burst mode or read len bytes from the radio in burst
 *              mode if the burst bit is set. If the burst bit is not set, only
 *              one data byte is communicated.
 *
 * @param       addr      - address byte of register.
 * @param       pData     - data array
 * @param       len       - Length of array to be read(TX) / written(RX)
 *
 * @return      void
 */
static void ccReadWriteBurstSingle(uint8 addr, uint8 *pData, uint16 len)
{
	uint16 i;
	
  /* reading */
  if(addr & RADIO_READ_ACCESS)
  {

    /* reading and burst mode */
    if(addr&RADIO_BURST_ACCESS)
    {
      for (i = 0; i < len; i++)
      {

          *pData = SPI.transfer(0);     /* Store pData from last pData RX */
          pData++;
      }
    }
    /* reading and single mode */
    else
    {

      *pData = SPI.transfer(0);
    }
  }
  /* writing */ 
  else
  {
    /* writing and burst mode */
    if(addr&RADIO_BURST_ACCESS)
    {
      /* Communicate len number of bytes: if TX - the procedure doesn't overwrite pData */
      for (i = 0; i < len; i++)
      {
        SPI.transfer(*pData);
        pData++;
      }
    }

    /* writing and single mode*/
    else
    {
      SPI.transfer(*pData);
    }
  }
  return;
}
/*******************************************************************************
 * @fn          sendSPI
 *
 * @brief       Sends 1 byte on the SPI line. This function does not use the SPI
 *              transfer function included in the Arduino SPI library, but uses 
 *              manual setting of the SCLK. 
 *
 * @param       data     - byte to be sent (data or address)
 *
 * @return      status_t
 */
status_t sendSPI(uint8 data){
  
  uint8 returnValue = 0x00;
  
  // data transfer
  for (uint8 i = 7; i >= 0; i--) 
  {
    // Slave Input write
    digitalWrite(CC112X_SPI_MOSI, (data >> i) & 0x01);
    delay(1);
    
    // SCLK up
    digitalWrite(CC112X_SERIAL_CLOCK, HIGH);
    
    // Slave Output read
    returnValue |= (uint8)(digitalRead(CC112X_SPI_MISO) << i);
    delay(1);
    
    // SCLK down
    digitalWrite(CC112X_SPI_MOSI, LOW);
    delay(1);
  }
  
  return returnValue;
}