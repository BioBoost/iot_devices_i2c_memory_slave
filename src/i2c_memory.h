#ifndef I2C_MEMORY
#define I2C_MEMORY

#include "mbed.h"
#include "memory.h"

namespace I2cMemoryDevice
{
    enum I2cCommand { CLEAR, PRINT, WRITE_ADDRESS, WRITE_DATA };

    class I2cMemory : public I2CSlave {

        private:
            const static unsigned int BUFFER_SIZE = 8;

        private:
            Memory * memory;
            unsigned int addressPointer;

        public:
            I2cMemory(PinName sda, PinName scl, Memory * memory, int address, int frequency=100000);

        public:
            void check_for_instruction(void);

        private:
            void send_data_to_master(void);
            void receive_instruction_from_master(void);
            void write_memory_pointer(void);
            void write_memory_data(void);

        public:
            static unsigned int int_to_byte(char * buffer, int value);
            static int byte_to_int(char * buffer);

    };

}

#endif
