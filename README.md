# CC1120
Repository for working with the TI CC1120 transceivers. 

## I2C Test Project
Working I2C connection between a Raspberry Pi 3 B Model and an STM32 NUCLEO-F446RE development board.

#### Hardware Setup
- Connect pins ```PB8 (SCL)``` and ```PB9 (SDA)``` on the nucelo board to two empty rows on a breadboard.
- Connect pins  ```GPIO5 (SCL)``` and ```GPIO3 (SDA)``` on the Rasperry Pi to their respective rows on the breadboard.
- Connect the ground pins between the nucleo board and the Rasperry PI.
- From either Rasperry PI or nucleo board supply a power rail on the breadboard with 3.3 volts. 
- Connect a ```4.7k Ohm``` pull-up resistor from the supply power rail to each of the I2C lines.    

#### Software Setup - Nucleo Board
- Under *Connectivity* in the STM32 CubeIDE, select ```I2C1``` and chose mode as ```I2C```.
- Select the clock speed to match that of the Raspberry PI (100000).
- Choose a Primary Slave Adrress. I have found that lower numbers are the only ones that will show up on the I2C bus. I used a slave address of ```0x04``` 

#### Software Setup - Rasperry PI
I just followed this tutorial to setup the PI. ```https://radiostud.io/howto-i2c-communication-rpi/```

