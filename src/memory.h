#ifndef MEMORY_HEADER
#define MEMORY_HEADER

#include "mbed.h"

namespace I2cMemoryDevice {

    class Memory {

        private:
            int * data;
            unsigned int size;

        public:
            Memory(unsigned int size=32);
            ~Memory(void);

        public:
            unsigned int get_size(void);

        public:
            void clear(void);
            void print(void);

        public:
            int read(unsigned int address);
            void write(unsigned int address, int value);
    };

};

#endif
