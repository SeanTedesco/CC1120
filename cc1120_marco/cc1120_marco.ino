#include "cc112x_spi.h"

/******************************************************************************
 * VARIABLES
 */
// Carrier frequency = 868.000000
// Symbol rate = 1.2
// Bit rate = 1.2
// Deviation = 3.997803
// Manchester enable = false
// Bit rate = 1.2
// Modulation format = 2-FSK
// Bit rate = 1.2
// RX filter BW = 25.000000
// TX power = -6
// PA ramping = true
// Packet length mode = Variable
// Whitening = false
// Address config = No address check.
// Packet length = 255
// Device address = 0
static registerSetting_t preferredSettings[] = {
    {CC112X_RFEND_CFG0,     0x20},
    {CC112X_IOCFG3,         0xB0},
    {CC112X_IOCFG2,         0x06},
    {CC112X_IOCFG1,         0xB0},
    {CC112X_IOCFG0,         0xB0},
    {CC112X_SYNC_CFG1,      0x0B},
    {CC112X_DCFILT_CFG,     0x1C},
    {CC112X_IQIC,           0xC6},
    {CC112X_CHAN_BW,        0x08},
    {CC112X_MDMCFG0,        0x05},
    {CC112X_AGC_REF,        0x20},
    {CC112X_AGC_CS_THR,     0x19},
    {CC112X_AGC_CFG1,       0xA9},
    {CC112X_AGC_CFG0,       0xCF},
    {CC112X_FIFO_CFG,       0x00},
    {CC112X_SETTLING_CFG,   0x03},
    {CC112X_FS_CFG,         0x12},
    {CC112X_PKT_CFG1,       0x05},
    {CC112X_PKT_CFG0,       0x20},
    {CC112X_PA_CFG2,        0x4F},
    {CC112X_PA_CFG1,        0x56},
    {CC112X_PA_CFG0,        0x1C},
    {CC112X_PKT_LEN,        0xFF},
    {CC112X_IF_MIX_CFG,     0x00},
    {CC112X_FREQOFF_CFG,    0x22},
    {CC112X_FREQ2,          0x6C},
    {CC112X_FREQ1,          0x80},
    {CC112X_FREQ0,          0x00},
    {CC112X_FS_DIG1,        0x00},
    {CC112X_FS_DIG0,        0x5F},
    {CC112X_FS_CAL0,        0x0E},
    {CC112X_FS_DIVTWO,      0x03},
    {CC112X_FS_DSM0,        0x33},
    {CC112X_FS_DVC0,        0x17},
    {CC112X_FS_PFD,         0x50},
    {CC112X_FS_PRE,         0x6E},
    {CC112X_FS_REG_DIV_CML, 0x14},
    {CC112X_FS_SPARE,       0xAC},
    {CC112X_XOSC5,          0x0E},
    {CC112X_XOSC3,          0xC7},
    {CC112X_XOSC1,          0x07},
};

CC1120 radio;

void tx_strobe(){
  uint8_t statusByte;
  uint8_t marcstate;
  // Strobe STX to send the packet
  statusByte = radio.pyxSpiCmdStrobe(CC112X_STX);
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("TX Strobe: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void rx_strobe(){
  uint8_t statusByte;
  uint8_t marcstate;
  // Strobe STX to send the packet
  statusByte = radio.pyxSpiCmdStrobe(CC112X_SRX);
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("RX Strobe: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void idle_strobe(){
  uint8_t statusByte;
  uint8_t marcstate;
  // Strobe STX to send the packet
  statusByte = radio.pyxSpiCmdStrobe(CC112X_SIDLE);
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("IDLE Strobe: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void flush_rx(){
  uint8_t statusByte;
  uint8_t marcstate;
  // Strobe STX to send the packet
  statusByte = radio.pyxSpiCmdStrobe(CC112X_SFRX);
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("SFRX Strobe: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void flush_tx(){
  uint8_t statusByte;
  uint8_t marcstate;
  // Strobe STX to send the packet
  statusByte = radio.pyxSpiCmdStrobe(CC112X_SFTX);
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("SFTX Strobe: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void std_fifo_write(){
  uint8_t statusByte;
  uint8_t marcstate;
  uint8_t txBuffer[6] = {5, 109, 97, 114, 99, 111};
  // Write the packet to the TX FIFO on the radio
  statusByte = radio.cc112xSpiWriteTxFifo(txBuffer, sizeof(txBuffer));
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("STD FIFO Write: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void std_fifo_read(){
  uint8_t statusByte;
  uint8_t marcstate;
  uint8_t rxBuffer[256] = {0};
  uint8_t numRxBytes;

  // Write the packet to the TX FIFO on the radio
  statusByte = radio.cc112xSpiReadRxFifo(rxBuffer, 5);
  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("STD FIFO Read: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);

}

void direct_tx_fifo_read(){
  uint8_t statusByte;
  uint8_t marcstate;

  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CC112X_CHIP_SELECT, LOW); // Bring chip select low to start

  SPI.transfer(0xFE);
  SPI.transfer(0x00);
  for(int i = 0; i < 6; i++){
    Serial.println(SPI.transfer(0));
  }

  digitalWrite(CC112X_CHIP_SELECT, HIGH); // Bring chip select high to stop
  SPI.endTransaction();

  statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("direct tx fifo read: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);

}

void tx_pointers_read(){
  uint8_t statusByte;
  uint8_t marcstate;
  uint8_t numTxBytes;
  radio.cc112xSpiReadReg(CC112X_TXFIRST, &numTxBytes, 1);
  Serial.print(numTxBytes);
  Serial.println(" TX First");

  radio.cc112xSpiReadReg(CC112X_TXLAST, &numTxBytes, 1);
  Serial.print(numTxBytes);
  Serial.println(" TX Last");

  statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("tx pointers read: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void write_settings(){
  uint8_t statusByte;
  uint8_t marcstate;

  radio.registerConfig(preferredSettings, sizeof(preferredSettings)/sizeof(registerSetting_t));

  statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("register conf: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}

void tx_buff_size_read(){
  uint8_t statusByte;
  uint8_t marcstate;
  uint8_t numTxBytes;
  // How many bytes are in the TX FIFO
  radio.cc112xSpiReadReg(CC112X_NUM_TXBYTES, &numTxBytes, 1);
  Serial.print(numTxBytes);
  Serial.println(" TX bytes");

  // How many bytes are in the TX FIFO
  radio.cc112xSpiReadReg(CC112X_FIFO_NUM_TXBYTES, &numTxBytes, 1);
  Serial.print(numTxBytes);
  Serial.println(" TX bytes");

  statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("tx buff size read: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);
}


void setup(){
  Serial.begin(9600);
  radio.pyxSPIInterfaceInit();

  Serial.println("Setup Done...");

  /*
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CC112X_CHIP_SELECT, LOW); // Bring chip select low to start

  Serial.println(SPI.transfer(0b01111111));
  Serial.println(SPI.transfer(txBuffer[0]));
  Serial.println(SPI.transfer(txBuffer[1]));
  Serial.println(SPI.transfer(txBuffer[2]));
  Serial.println(SPI.transfer(txBuffer[3]));
  Serial.println(SPI.transfer(txBuffer[4]));
  Serial.println(SPI.transfer(txBuffer[5]));

  digitalWrite(CC112X_CHIP_SELECT, HIGH); // Bring chip select high to stop
  SPI.endTransaction();
  */

}

void loop(){

  if(Serial.available()){
    uint8_t c = Serial.read();

    switch(c){
      case 't':
        tx_strobe();
        break;
      case 'r':
        rx_strobe();
        break;
      case 'i':
        idle_strobe();
        break;
      case 'f':
        flush_rx();
        flush_tx();
        break;
      case 'w':
        std_fifo_write();
        break;
      case 'e':
        std_fifo_read();
        break;
      case 'd':
        direct_tx_fifo_read();
        break;
      case 'p':
        tx_pointers_read();
        break;
      case 's':
        write_settings();
        break;
      case 'b':
        tx_buff_size_read();
        break;
      default:
        idle_strobe();
        break;
    }
  }


  uint8_t statusByte;
  uint8_t marcstate;
  uint8_t gpioStat;

  // Length: 5 | Contents: "marco"
  uint8_t txBuffer[6] = {5, 109, 97, 114, 99, 111};
  uint8_t numTxBytes;

  uint8_t rxBuffer[256] = {0};
  uint8_t numRxBytes;

  char message[256];

  uint16_t packetStatus = 0;

  statusByte = radio.pyxSpiCmdStrobe(CC112X_SCAL);

   //waitForKeyPress();

  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);

  Serial.print("CC1120 Status Byte: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);

  //waitForKeyPress();

  // How many bytes are in the TX FIFO
  radio.cc112xSpiReadReg(CC112X_NUM_RXBYTES, &numRxBytes, 1);
  Serial.print(numRxBytes);
  Serial.println(" RX bytes");

  //waitForKeyPress();


  //waitForKeyPress();

  // How many bytes are in the TX FIFO
  radio.cc112xSpiReadReg(CC112X_NUM_RXBYTES, &numRxBytes, 1);
  Serial.print(numRxBytes);
  Serial.println(" RX bytes");

  
  // Write the packet to the TX FIFO on the radio
  radio.cc112xSpiReadRxFifo(rxBuffer, sizeof(rxBuffer));

  //waitForKeyPress();

  // Strobe STX to send the packet
  statusByte = radio.pyxSpiCmdStrobe(CC112X_SRX);

  radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);


  Serial.print("CC1120 Status Byte: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);

  //waitForKeyPress();


  statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);


  Serial.print("CC1120 Status Byte: ");
  Serial.print(statusByte, HEX);
  Serial.print(" | ");
  Serial.println(marcstate, HEX);

  //waitForKeyPress();

  
    radio.cc112xSpiReadReg(CC112X_NUM_RXBYTES, &numRxBytes, 1);
    Serial.print(numRxBytes);
    Serial.println(" RX bytes");
    delay(1000);
  
  Serial.println("Message sent!");

/*
  // Wait for packet to be sent
  do{
    radio.cc112xSpiReadReg(CC112X_GPIO_STATUS, &gpioStat, 1);
    Serial.print("GPIO status: ");
    Serial.println(gpioStat, BIN);
  }while(!(gpioStat & 0b00000100));
  Serial.println("Message sent!");

  // Set radio to recieve
  radio.pyxSpiCmdStrobe(CC112X_SRX);

  long tick = millis();
  // Wait 5 seconds for a response
  while(millis() - tick < 5000){

    // Read GPIO status register
    radio.cc112xSpiReadReg(CC112X_GPIO_STATUS, &gpioStat, 1);

    Serial.print("GPIO status: ");
    Serial.println(gpioStat, BIN);

    // Did we get a packet?
    if(gpioStat & 0b00000100){
      Serial.println("Message recieved!");

      // How many bytes are in the RX FIFO
      radio.cc112xSpiReadReg(CC112X_NUM_RXBYTES, &numRxBytes, 1);

      Serial.print(numRxBytes);
      Serial.println(" bytes");

      radio.cc112xSpiReadRxFifo(rxBuffer, numRxBytes);

      memcpy(message, rxBuffer, numRxBytes - 2);
      memcpy(packetStatus, &rxBuffer[numRxBytes - 3], 2);

      Serial.print("Message: ");
      Serial.println(message);

      Serial.print("Packet Status: ");
      Serial.println(packetStatus, BIN);

      statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);


      Serial.print("CC1120 Status Byte: ");
      Serial.print(statusByte, HEX);
      Serial.print(" | ");
      Serial.println(marcstate, HEX);
      break;
    }

    statusByte = radio.cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);


    Serial.print("CC1120 Status Byte: ");
    Serial.print(statusByte, HEX);
    Serial.print(" | ");
    Serial.println(marcstate, HEX);


    delay(1000);
  }
  
  //Serial.print("\n\n");
*/
}
