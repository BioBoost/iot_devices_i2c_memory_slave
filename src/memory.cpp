#include "memory.h"
#include "mbed.h"

#define DEBUG_MODE 1
#include "log.h"

namespace I2cMemoryDevice {

    Memory::Memory(unsigned int size) {

        this->size = size;
        data = new int[size];
        SimplyLog::Log::i("Created memory of size = %d\r\n", size);
        clear();
    }

    Memory::~Memory(void) {
        delete data;
        data = 0;
    }

    unsigned int Memory::get_size(void) {
        return size;
    }

    void Memory::clear()
    {
        SimplyLog::Log::i("Clearing memory\r\n");
        for (unsigned int i = 0; i < size; i++) {
            this->data[i] = 0;
        }
    }

    int Memory::read(unsigned int address) {
        if (address < size) {
            SimplyLog::Log::d("Reading %d from %d\r\n", data[address], address);
            return data[address];
        } else {
            return 0;
        }
    }

    void Memory::write(unsigned int address, int value) {
        if (address < size) {
            SimplyLog::Log::d("Writing %d to %d\r\n", value, address);
            data[address] = value;
        }
    }

    void Memory::print(void) {
        for (unsigned int i = 0; i < size; i++) {
          printf("\t[%#04x]: %6d", i, data[i]);
          if ((i % 4) == 3) {
            printf("\r\n");
          }
        }
        printf("\r\n");
        fflush(stdout);
    }

};
