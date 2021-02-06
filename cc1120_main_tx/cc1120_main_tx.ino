#include "CC1120_Arduino_SPI.hpp"

/*************************************************************************
 * DEFINES
 */
#define PKTLEN 30 

/*************************************************************************
 * Local Variables
 */ uint16_t packetCounter = 0;

/*************************************************************************
 * Static Functions
 */
static void createPacket(uint8_t randBuffer[]);
/*************************************************************************
 * register settings
 */
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
    pinMode(CC112X_CHIP_RESET, OUTPUT);          //reset pin --> output
    pinMode(CC112X_SPI_MOSI, OUTPUT);        //mosi pin --> output
    pinMode(CC112X_SPI_MISO, INPUT);          //miso pin --> input
    pinMode(CC112X_SERIAL_CLOCK, OUTPUT);       //sclk pin --> output
    pinMode(CC112X_CHIP_SELECT, OUTPUT);    //ss pin --> output
    digitalWrite(CC112X_CHIP_SELECT,HIGH);  //disable deivce communication
    digitalWrite(CC112X_CHIP_RESET, HIGH);       //reset off

    Serial.begin(9600);              //start Serial
    Serial.println("<start program>");

    Serial.println("<begin init>");
    SPI_settingsInit();
    CC_writeSettings(preferredSettings);    // write settings from prefered setting array
    Serial.println("<end init>");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  uint8 txBuffer[PKTLEN+1] = {0}; 

  //update packet counter
  packetCounter++; 

  //create a random packet
  createPacket(txBuffer);

  //write packet to TX FIFO
  CC_SPI_writeTxFIFO(txBuffer, sizeof(txBuffer));

  //strobe tx to send packet
  CC_SPI_strobeCommand(CC112X_STX); 
  
  delay(1000);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
*   @fn         createPacket
*
*   @brief      This function is called before a packet is transmitted. It fills
*               the txBuffer with a packet consisting of a length byte, two
*               bytes packet counter and n random bytes.
*
*   @param       Pointer to start of txBuffer
*
*   @return      none
*/
static void createPacket(uint8 txBuffer[]) {

    txBuffer[0] = PKTLEN;                           // Length byte
    txBuffer[1] = (uint8) (packetCounter >> 8);     // MSB of packetCounter
    txBuffer[2] = (uint8)  packetCounter;           // LSB of packetCounter

    // Fill rest of buffer with random bytes
    for(uint8 i = 3; i < (PKTLEN + 1); i++) {
        txBuffer[i] = (uint8)rand();
    }
}
