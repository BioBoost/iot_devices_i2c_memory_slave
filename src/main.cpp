#include "mbed.h"
#include "memory.h"
#include "i2c_memory.h"

#define DEBUG_MODE 1
#include "log.h"

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);

int main() {
    pc.baud(115200);
    SimplyLog::Log::i("I2C Memory Slave loading ...\r\n");

    I2cMemoryDevice::Memory memory(32);
    I2cMemoryDevice::I2cMemory i2cMemory(p28, p27, &memory, 0x24);

    memory.print();

    int i = 0;
    while(1) {
        i2cMemory.check_for_instruction();

        i++;
        if (i >= 300000) {
            i = 0;
            myled = !myled;
        }
    }
}
