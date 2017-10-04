# IoT Devices - I2C Memory Slave Device for mBed

This firmware is for the LPC1768 mBed device. It emulates a very simple I2C memory device.

## I2C Characteristics

* SDA defaults to p28
* SCL default to p27
* 8-bit I2C address defaults to 0x24
* Frequency default to 100kHz

Caution because mBed uses 8-bit I2C addresses while Linux uses 7-bit.
