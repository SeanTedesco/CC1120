#define SPICLOCK  13   //SCLK --> pin 13
#define DATAOUT 11     //MOSI --> pin 11
#define DATAIN  12     //MISO --> pin 12
#define SLAVESELECT 10 //SS --> pin 10
#define RESET 9        //RESET --> pin 9


#define WRSR  1        //write protection command
#define WRITE 2        //write command
#define READ  3        //read command
#define WRDI  4        //write disable command
#define RDSR  5        //buffer command
#define WREN  6        //write enable command

//define configuration registers
#define IOCFG3 0x00    
#define IOCFG2 0x01
#define IOCFG1 0x02
#define IOCFG0 0x03
#define SYNC3 0x04
#define SYNC2 0x05
#define SYNC1 0x06
#define SYNC0 0x07
#define SYNC_CFG1 0x08
#define SYNC_CFG0 0x09
#define DEVIATION_M 0x0A
#define MODCFG_DEV_E 0x0B
#define DCFILT_CFG 0x0C
#define PREAMBLE_CFG1 0x0D
#define PREAMBLE_CFG0 0x0E
#define FREQ_IF_CFG 0x0F
#define IQIC 0x10
#define CHAN_BW 0x11
#define MDMCFG1 0x12
#define MDMCFG0 0x13
#define SYMBOL_RATE2 0x14
#define SYMBOL_RATE1 0x15
#define SYMBOL_RATE0 0x16
#define AGC_REF 0x17
#define AGC_CS_THR 0x18
#define AGC_GAIN_ADJUST 0x19
#define AGC_CFG3 0x1A
#define AGC_CFG2 0x1B
#define AGC_CFG1 0x1C
#define AGC_CFG0 0x1D
#define FIFO_CFG 0x1E
#define DEV_ADDR 0x1F
#define SETTLING_CFG 0x20
#define FS_CFG 0x21
#define WOR_CFG1 0x22
#define WOR_CFG0 0x23
#define WOR_EVENT0_MSB 0x24
#define WOR_EVENT0_LSB 0x25
#define PKT_CFG2 0x26
#define PKT_CFG1 0x27
#define PKT_CFG0 0x28
#define RFEND_CFG1 0x29
#define RFEND_CFG0 0x2A
#define PA_CFG2 0x2B
#define PA_CFG1 0x2C
#define PA_CFG0 0x2D
#define PKT_LEN 0x2E

//define extended address
#define EXTENDED ADDRESS 0x2F

//define extended registers
#define IF_MIX_CFG 0x00    
#define FREQOFF_CFG 0x01
#define TOC_CFG 0x02
#define MARC_SPARE 0x03
#define ECG_CFG 0x04
#define CFM_DATA_CFG 0x05
#define EXT_CTRL 0x06
#define RCCAL_FINE 0x07
#define RCCAL_COARSE 0x08
#define RCCAL_OFFSET 0x09
#define FREQOFF1 0x0A
#define FREQOFF0 0x0B
#define FREQ2 0x0C
#define FREQ1 0x0D
#define FREQ0 0x0E
#define IF_ADC2 0x0F
#define IF_ADC1 0x10
#define IF_ADC0 0x11
#define FS_DIG1 0x12
#define FS_DIG0 0x13
#define FS_CAL3 0x14
#define FS_CAL2 0x15
#define FS_CAL1 0x16
#define FS_CAL0 0x17
#define FS_CHP 0x18
#define FS_DIVTWO 0x19
#define FS_DSM1 0x1A
#define FS_DSM0 0x1B
#define FS_DVC1 0x1C
#define FS_DVC0 0x1D
#define FS_LBI 0x1E
#define FS_PFD 0x1F
#define FS_PRE 0x20
#define FS_REG_DIV_CML 0x21
#define FS_SPARE 0x22
#define FS_VCO4 0x23
#define FS_VCO3 0x24
#define FS_VCO2 0x25
#define FS_VCO1 0x26
#define FS_VCO0 0x27
#define GBIAS6 0x28
#define GBIAS5 0x29
#define GBIAS4 0x2A
#define GBIAS3 0x2B
#define GBIAS2 0x2C
#define GBIAS1 0x2D
#define GBIAS0 0x2E
#define IFAMP 0x2F
#define LNA 0x30
#define RXMIX 0x31
#define XOSC5 0x32
#define XOSC4 0x33
#define XOSC3 0x34
#define XOSC2 0x35
#define XOSC1 0x36
#define XOSC0 0x37
#define ANALOG_SPARE 0x38
#define PA_CFG3 0x39
#define WOR_TIME1 0x64
#define WOR_TIME0 0x65
#define WOR_CAPTURE1 0x66
#define WOR_CAPTURE0 0x67
#define BIST 0x68
#define DCFILTOFFSET_I1 0x69
#define DCFILTOFFSET_I0 0x6A
#define DCFILTOFFSET_Q1 0x6B
#define DCFILTOFFSET_Q0 0x6C
#define IQIE_I1 0x6D
#define IQIE_I0 0x6E
#define IQIE_Q1 0x6F
#define IQIE_Q0 0x70
#define RSSI1 0x71
#define RSSI0 0x72
#define MARCSTATE 0x73
#define LQI_VAL 0x74
#define PQT_SYNC_ERR 0x75
#define DEM_STATUS 0x76
#define FREQOFF_EST1 0x77
#define FREQOFF_EST0 0x78
#define AGC_GAIN3 0x79
#define AGC_GAIN2 0x7A
#define AGC_GAIN1 0x7B
#define AGC_GAIN0 0x7C
#define CFM_RX_DATA_OUT 0x7D
#define CFM_TX_DATA_IN 0x7E
#define ASK_SOFT_RX_DATA 0x7F
#define RNDGEN 0x80
#define MAGN2 0x81
#define MAGN1 0x82
#define MAGN0 0x83
#define ANG1 0x84
#define ANG0 0x85
#define CHFILT_I2 0x86
#define CHFILT_I1 0x87
#define CHFILT_I0 0x88
#define CHFILT_Q2 0x89
#define CHFILT_Q1 0x8A
#define CHFILT_Q0 0x8B
#define GPIO_STATUS 0x8C
#define FSCAL_CTRL 0x8D
#define PHASE_ADJUST 0x8E
#define PARTNUMBER 0x8F
#define PARTVERSION 0x90
#define SERIAL_STATUS 0x91
#define MODEM_STATUS1 0x92
#define MODEM_STATUS0 0x93
#define MARC_STATUS1 0x94
#define MARC_STATUS0 0x95
#define PA_IFAMP_TEST 0x96
#define FSRF_TEST 0x97
#define PRE_TEST 0x98
#define PRE_OVR 0x99
#define ADC_TEST 0x9A
#define DVC_TEST 0x9B
#define ATEST 0x9C
#define ATEST_LVDS 0x9D
#define ATEST_MODE 0x9E
#define XOSC_TEST1 0x9F
#define XOSC_TEST0 0xA0
#define RXFIRST 0xD2
#define TXFIRST 0xD3
#define RXLAST 0xD4
#define TXLAST 0xD5
#define NUM_TXBYTES 0xD6
#define NUM_RXBYTES 0xD7
#define FIFO_NUM_TXBYTES 0xD8
#define FIFO_NUM_RXBYTES 0xD9

// modes
#define SRES 0x30
#define SFSTXON 0x32
#define SXOFF 0x32
#define SCAL 0x33
#define SRX 0x34
#define STX 0x35
#define SIDLE 0x36
#define SAFC 0x37
#define SWOR 0x38
#define SPWD 0x39
#define SFRX 0x3A
#define SFTX 0x3B
#define SWORRST 0x3C
#define SNOP = 0x3D

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
    pinMode(RESET, OUTPUT);          //reset pin --> output
    pinMode(DATAOUT, OUTPUT);        //mosi pin --> output
    pinMode(DATAIN, INPUT);          //miso pin --> input
    pinMode(SPICLOCK, OUTPUT);       //sclk pin --> output
    pinMode(SLAVESELECT, OUTPUT);    //ss pin --> output
    digitalWrite(SLAVESELECT,HIGH);  //disable deivce communication
    digitalWrite(RESET, HIGH);       //reset off
    Serial.begin(9600);              //start Serial
    Serial.println("<start program>");
    Serial.println("<begin init>");

    writeConfiguration(IOCFG3, 0xB0);        //write settings to c1120
    writeConfiguration(IOCFG2, 0x06);
    writeConfiguration(IOCFG1, 0xB0);
    writeConfiguration(IOCFG0, 0x40);
    writeConfiguration(SYNC3, 0x93);
    writeConfiguration(SYNC2, 0x0B);
    writeConfiguration(SYNC1,0x51);
    writeConfiguration(SYNC0,0xDE);
    writeConfiguration(SYNC_CFG1,0x0B);
    writeConfiguration(SYNC_CFG0,0x17);
    writeConfiguration(DEVIATION_M, 0x06);
    writeConfiguration(MODCFG_DEV_E, 0x03);
    writeConfiguration(DCFILT_CFG, 0x1C);
    writeConfiguration(PREAMBLE_CFG1, 0x18);
    writeConfiguration(PREAMBLE_CFG0,0x2A);
    writeConfiguration(FREQ_IF_CFG, 0x40);
    writeConfiguration(IQIC,0xC6);
    writeConfiguration(CHAN_BW, 0x14);
    writeConfiguration(MDMCFG1,0x46);
    writeConfiguration(MDMCFG0,0x05);
    writeConfiguration(SYMBOL_RATE2,0x43);
    writeConfiguration(SYMBOL_RATE1,0xA9);
    writeConfiguration(SYMBOL_RATE0,0x2A);
    writeConfiguration(AGC_REF,0x20);
    writeConfiguration(AGC_CS_THR,0x19);
    writeConfiguration(AGC_GAIN_ADJUST,0x00);
    writeConfiguration(AGC_CFG3,0x91);
    writeConfiguration(AGC_CFG2,0x20);
    writeConfiguration(AGC_CFG1,0xA9);
    writeConfiguration(AGC_CFG0,0xCF);
    writeConfiguration(FIFO_CFG,0x00);
    writeConfiguration(DEV_ADDR,0x00);
    writeConfiguration(SETTLING_CFG,0x0B);
    writeConfiguration(FS_CFG,0x14);          //carrier
    writeConfiguration(WOR_CFG1,0x08);
    writeConfiguration(WOR_CFG0,0x21);
    writeConfiguration(WOR_EVENT0_MSB,0x00);
    writeConfiguration(WOR_EVENT0_LSB,0x00);
    writeConfiguration(PKT_CFG2,0x04);
    writeConfiguration(PKT_CFG1,0x05);
    writeConfiguration(PKT_CFG0,0x20);
    writeConfiguration(RFEND_CFG1,0x0F);
    writeConfiguration(RFEND_CFG0,0x00);
    writeConfiguration(PA_CFG2,0x7F);
    writeConfiguration(PA_CFG1,0x56);
    writeConfiguration(PA_CFG0,0x7C);
    writeConfiguration(PKT_LEN,0xFF);
    writeExtended(IF_MIX_CFG,0x00);
    writeExtended(FREQOFF_CFG,0x22);
    writeExtended(TOC_CFG,0x0B);
    writeExtended(MARC_SPARE,0x00);
    writeExtended(ECG_CFG,0x00);
    writeExtended(CFM_DATA_CFG,0x00);
    writeExtended(EXT_CTRL,0x01);
    writeExtended(RCCAL_FINE,0x00);
    writeExtended(RCCAL_COARSE,0x00);
    writeExtended(RCCAL_OFFSET,0x00);
    writeExtended(FREQOFF1,0x00);
    writeExtended(FREQOFF0,0x00);
    writeExtended(FREQ2,0x6C);
    writeExtended(FREQ1,0x80);
    writeExtended(FREQ0,0x00);
    writeExtended(IF_ADC2,0x02);
    writeExtended(IF_ADC1,0xA6);
    writeExtended(IF_ADC0,0x04);
    writeExtended(FS_DIG1,0x00);
    writeExtended(FS_DIG0,0x5F);
    writeExtended(FS_CAL3,0x00);
    writeExtended(FS_CAL2,0x20);
    writeExtended(FS_CAL1,0x40);
    writeExtended(FS_CAL0,0x0E);
    writeExtended(FS_CHP,0x28);
    writeExtended(FS_DIVTWO,0x03);
    writeExtended(FS_DSM1,0x00);
    writeExtended(FS_DSM0,0x33);
    writeExtended(FS_DVC1,0xFF);
    writeExtended(FS_DVC0,0x17);
    writeExtended(FS_PRE, 0x6E);      
    writeExtended(FS_REG_DIV_CML, 0x14);       
    writeExtended(FS_SPARE, 0xAC);              
    writeExtended(FS_VCO4, 0x14);              
    writeExtended(FS_VCO3, 0x00);              
    writeExtended(FS_VCO2, 0x00);               
    writeExtended(FS_VCO1, 0x00);              
    writeExtended(FS_VCO0, 0xB4);              
    writeExtended(GBIAS6, 0x00);              
    writeExtended(GBIAS5, 0x02);            
    writeExtended(GBIAS4, 0x00);            
    writeExtended(GBIAS3, 0x00);             
    writeExtended(GBIAS2, 0x10);             
    writeExtended(GBIAS1, 0x00);             
    writeExtended(GBIAS0, 0x00);             
    writeExtended(IFAMP, 0x01);              
    writeExtended(LNA, 0x01);              
    writeExtended(RXMIX, 0x01);            
    writeExtended(XOSC5, 0x0E);            
    writeExtended(XOSC4, 0xA0);            
    writeExtended(XOSC3, 0x03);            
    writeExtended(XOSC2, 0x04);            
    writeExtended(XOSC1, 0x03);            
    writeExtended(XOSC0, 0x00);            
    writeExtended(ANALOG_SPARE, 0x00);       
    writeExtended(PA_CFG3, 0x00);           
    writeExtended(WOR_TIME1, 0x00);        
    writeExtended(WOR_TIME0, 0x00);       
    writeExtended(WOR_CAPTURE1, 0x00);    
    writeExtended(WOR_CAPTURE0, 0x00);    
    writeExtended(BIST, 0x00);        
    writeExtended(DCFILTOFFSET_I1, 0x00);
    writeExtended(DCFILTOFFSET_I0, 0x00);
    writeExtended(DCFILTOFFSET_Q1, 0x00);
    writeExtended(DCFILTOFFSET_Q0, 0x00);
    writeExtended(IQIE_I1, 0x00);   
    writeExtended(IQIE_I0, 0x00);  
    writeExtended(IQIE_Q1, 0x00);  
    writeExtended(IQIE_Q0, 0x00);  
    writeExtended(RSSI1, 0x80);   
    writeExtended(RSSI0, 0x00);   
    writeExtended(MARCSTATE, 0x41);
    writeExtended(LQI_VAL, 0x00);  
    writeExtended(PQT_SYNC_ERR, 0xFF);
    writeExtended(DEM_STATUS, 0x00);  
    writeExtended(FREQOFF_EST1, 0x00);
    writeExtended(FREQOFF_EST0, 0x00);
    writeExtended(AGC_GAIN3, 0x00);  
    writeExtended(AGC_GAIN2, 0xD1);  
    writeExtended(AGC_GAIN1, 0x00);  
    writeExtended(AGC_GAIN0, 0x3F);  
    writeExtended(CFM_RX_DATA_OUT, 0x00);
    writeExtended(CFM_TX_DATA_IN, 0x00); 
    writeExtended(ASK_SOFT_RX_DATA, 0x30);
    writeExtended(RNDGEN, 0x7F);   
    writeExtended(MAGN2, 0x00);   
    writeExtended(MAGN1, 0x00);   
    writeExtended(MAGN0, 0x00);   
    writeExtended(ANG1, 0x00);   
    writeExtended(ANG0, 0x00);   
    writeExtended(CHFILT_I2, 0x08);
    writeExtended(CHFILT_I1, 0x00);
    writeExtended(CHFILT_I0, 0x00);
    writeExtended(CHFILT_Q2, 0x00);
    writeExtended(CHFILT_Q1, 0x00);
    writeExtended(CHFILT_Q0, 0x00);
    writeExtended(GPIO_STATUS, 0x00);
    writeExtended(FSCAL_CTRL, 0x01);   
    writeExtended(PHASE_ADJUST, 0x00);   
    writeExtended(PARTNUMBER, 0x00);   
    writeExtended(PARTVERSION, 0x00);  
    writeExtended(SERIAL_STATUS, 0x00);
    writeExtended(MODEM_STATUS1, 0x01);
    writeExtended(MODEM_STATUS0, 0x00);
    writeExtended(MARC_STATUS1, 0x00); 
    writeExtended(MARC_STATUS0, 0x00); 
    writeExtended(PA_IFAMP_TEST, 0x00);
    writeExtended(FSRF_TEST, 0x00);   
    writeExtended(PRE_TEST, 0x00);   
    writeExtended(PRE_OVR, 0x00);   
    writeExtended(ADC_TEST, 0x00);  
    writeExtended(DVC_TEST, 0x0B);  
    writeExtended(ATEST, 0x40);   
    writeExtended(ATEST_LVDS, 0x00);
    writeExtended(ATEST_MODE, 0x00);
    writeExtended(XOSC_TEST1, 0x3C);
    writeExtended(XOSC_TEST0, 0x00);
    writeExtended(RXFIRST, 0x00);   
    writeExtended(TXFIRST, 0x00);   
    writeExtended(RXLAST, 0x00);   
    writeExtended(TXLAST, 0x00);   
    writeExtended(NUM_TXBYTES, 0x00);
    writeExtended(NUM_RXBYTES, 0x00);   
    writeExtended(FIFO_NUM_TXBYTES, 0x0F);
    writeExtended(FIFO_NUM_RXBYTES, 0x00);
    
    Serial.println("<done init>");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  uint8_t data = 0xAA;
  sendData(data);
  Serial.println(data);
  delay(1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: transmit byte through TX FIFO address space
 * @param: tx_byte, byte to be sent to the TX FIFO address space
 * @return: void
 */
void sendData( uint8_t tx_byte ) 
{
    writeStrobe( SIDLE ); //Set to IDLE MODE
    delay(1);
    
    writeStrobe( STX ); //Set to TX MODE
    delay(1);
          
    writeStrobe( SFSTXON ); //SFSTXON
    delay(1);

    writeStrobe( 0x3F );  //txfifo, size
    delay(1);
    
    writeStrobe( tx_byte );  //txfifo, data, size
    delay(1);
    
    writeStrobe( 0x35 );  //stx
    delay(1);

    writeStrobe( SFTX );  //flush tx fifo
    delay(1); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: receive data in the RX FIFO address space
 * @param: void
 * @return: rx_byte, byte at located at first location in the RX FIFO address space
 */
uint8_t receiveData( void )                               
{
    uint8_t numBytes = 0x00;
    uint8_t address = 0x00;
    uint8_t rx_byte = 0x00; 
  
    writeStrobe( SIDLE ); //Set to IDLE MODE
    delay(1);
    
    writeStrobe( SRX ); //Set to RX MODE
    delay(1);

    if( !readExtended( NUM_RXBYTES ) ) // BYTES_IN_RXFIFO
    {
        Serial.println("<no more bytes>");  // update user 
    }
    else
    {      
        Serial.println("<we got bytes>"); // update user
        
        address = readExtended( RXFIRST );  // get address of the first byte in FIFO
        delay(1); 
        
        rx_byte = readDirect( address ); // read from the provided address
        delay(1);
    } 

    writeStrobe( SIDLE ); // set to IDLE MODE
    delay(1);
    
    writeStrobe( SFRX );  // flush RX FIFO 
    delay(1); 
    
    return rx_byte;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: read from Configuration Register Address Space
 * @param: EEPROM_address, address in normal address space
 * @return: data, byte at location specified with EEPROM_address
 */
uint8_t readConfiguration(uint8_t EEPROM_address)
{
  uint8_t data;
  digitalWrite(SLAVESELECT, LOW);      //enable device communication 
  sendSPI( EEPROM_address + 0x80 );   //send adrress
  data = sendSPI( 0xFF );             //get data
  digitalWrite(SLAVESELECT, HIGH);     //disable device communication 
  return data;                        //return data
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: read from Extended Register Address Space
 * @param: EEPROM_address, address in normal address space
 * @return: data, byte at location specified with EEPROM_address
 */
uint8_t readExtended(uint8_t EEPROM_address) 
{
  uint8_t data;
  digitalWrite(SLAVESELECT, LOW);   // enable device communication 
  sendSPI( 0xAF );                  // send address 1
  sendSPI( EEPROM_address );        // send address 2
  data = sendSPI( 0xFF );           // get data
  digitalWrite(SLAVESELECT, HIGH);  // disable device communication 
  return data;                      // return data
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: read from Direct Memory Access Register
 * @param: EEPROM_address, address in normal address space
 * @return: data, byte at location specified with EEPROM_address
 */
uint8_t readDirect(uint8_t EEPROM_address)
{
  uint8_t data;
  digitalWrite(SLAVESELECT,LOW);     //enable device communication 
  sendSPI( 0x3E );                   //send address to DMA register
  sendSPI( EEPROM_address );         // send address within FIFO
  data = sendSPI( 0xFF );            //get data
  digitalWrite(SLAVESELECT, HIGH);   //disable device communication 
  return data;                       //return data
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: //write to Configuration Register
 * @param: EEPROM_address, address in normal address space
 * @param: EEPROM_data, data to be written
 * @return: void
 */
void writeConfiguration(uint8_t EEPROM_address, uint8_t EEPROM_data)    
{  
  digitalWrite(SLAVESELECT, LOW);   //enable device communication 
  sendSPI( EEPROM_address );       //send address
  sendSPI( EEPROM_data );          //send data
  digitalWrite(SLAVESELECT, HIGH);  //disable device communication 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: write a strobe command
 * @param: EEPROM_data, data to be written
 * @return: void
 */
void writeStrobe(uint8_t EEPROM_data) 
{  
    digitalWrite(SLAVESELECT, LOW);   //enable device communication 
    sendSPI( EEPROM_data );          //write Command Strobe
    digitalWrite(SLAVESELECT, HIGH);  //disable device communication 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: write to extended register address
 * @param: EEPROM_address, address in extended address space
 * @param: EEPROM_data, data to be written to address 
 * @return: void
 */
void writeExtended(uint8_t EEPROM_address, uint8_t EEPROM_data)
{  
  digitalWrite(SLAVESELECT, LOW);  //enable device communication 
  sendSPI( 0x2F );                //send address 1
  sendSPI( EEPROM_address );      //send address 2
  sendSPI( EEPROM_data );         //send data
  digitalWrite(SLAVESELECT,HIGH); //disable device communication 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: write to Direct Memory Access Register
 * @param: EEPROM_address, address in normal address space
 * @param: EEPROM_data, data to be written to address 
 * @return: void
 */
void writeDirect(uint8_t EEPROM_address, uint8_t EEPROM_data)    
{  
  digitalWrite(SLAVESELECT, LOW);   //enable device communication
  sendSPI( 0x3E );                  //send address for direct memory access
  sendSPI( EEPROM_address );        //send address for location in FIFO
  sendSPI( EEPROM_data );           //send data at location in FIFO
  digitalWrite(SLAVESELECT, HIGH);  //disable device communication 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief: send data across SPI connection 
 * @param: mosi_byte, the byte to be sent (can be data or address)
 * @return: miso_byte, the status byte returned on the MISO line
 */
uint8_t sendSPI(uint8_t mosi_byte){
  
  uint8_t miso_byte = 0x00;
  uint8_t i = 0;
  
  // data transfer
  for (i = 8; i > 0; i--) 
  {
    // Slave Input write
    digitalWrite(DATAOUT, (mosi_byte >> i-1) & 0x01);
    delay(1);
    
    // SCLK up
    digitalWrite(SPICLOCK, HIGH);
    
    // Slave Output read
    miso_byte |= (uint8_t) digitalRead(DATAIN) << i-1;
    delay(1);
    
    // SCLK down
    digitalWrite(SPICLOCK, LOW);
    delay(1);
  }
  return miso_byte;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
