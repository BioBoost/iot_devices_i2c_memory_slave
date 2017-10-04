#include "i2c_memory.h"
#include "mbed.h"

#define DEBUG_MODE 1
#include "log.h"

namespace I2cMemoryDevice {

    I2cMemory::I2cMemory(PinName sda, PinName scl, Memory * memory, int address, int frequency)
        : I2CSlave(sda, scl) {

        this->address(address);
        this->frequency(frequency);
        SimplyLog::Log::i("Created I2c slave @ %d with f = %d\r\n", address, frequency);

        this->memory = memory;
        addressPointer = 0;
    }

    void I2cMemory::check_for_instruction(void) {
        int received = this->receive();
        switch (received) {
            case I2CSlave::ReadAddressed:
            {
                SimplyLog::Log::d("Master requests ReadAddressed\r\n");
                send_data_to_master();
                break;
            }
            case I2CSlave::WriteAddressed:
            {
                SimplyLog::Log::d("Master requests WriteAddressed\r\n");
                receive_instruction_from_master();
                break;
            }
        }
    }

    void I2cMemory::send_data_to_master(void) {
        char buffer[BUFFER_SIZE];

        // Data is located @ address pointer
        int value = memory->read(addressPointer);

        // First bytes = address
        unsigned int offset = int_to_byte(buffer, addressPointer);
        int_to_byte(buffer+offset, value);

        if (!this->write(buffer, 2*sizeof(int))) {
            SimplyLog::Log::d("Sending data to master: %d @%d\r\n", value, addressPointer);
        } else {
            SimplyLog::Log::d("Failed to send to master %d @%d\r\n", value, addressPointer);
        }
    }

    unsigned int I2cMemory::int_to_byte(char * buffer, int value) {
        *((int *)buffer) = value;
        return sizeof(int);
    }

    int I2cMemory::byte_to_int(char * buffer) {
        return (*((int*)(buffer)));
    }

    void I2cMemory::receive_instruction_from_master(void) {
        // First we read the command byte
        int command = this->read();
        switch (command) {
            case CLEAR:
                SimplyLog::Log::i("Got CMD Clear\r\n");
                memory->clear();
                this->stop();   // Required or else write from linux fails
                break;

            case PRINT:
                SimplyLog::Log::i("Got CMD Print\r\n");
                memory->print();
                this->stop();   // Required or else write from linux fails
                break;

            case WRITE_ADDRESS:
                SimplyLog::Log::i("Got CMD Write Address\r\n");
                write_memory_pointer();
                break;

            case WRITE_DATA:
                SimplyLog::Log::i("Got CMD Write Data\r\n");
                write_memory_data();
                break;

            default:
                SimplyLog::Log::e("Unknown command byte from master\r\n");
        }
    }

    void I2cMemory::write_memory_pointer(void) {
        char buffer[BUFFER_SIZE];

        // Expect 4 more bytes [address]
        if(!this->read(buffer, sizeof(int))) {
            int address = byte_to_int(buffer);
            SimplyLog::Log::d("Setting address pointer to %d\r\n", address);
            if (address < memory->get_size()) {
                addressPointer = address;
            } else {
                SimplyLog::Log::e("Address out of boundary\r\n");
            }
        } else {
            SimplyLog::Log::e("WRITE_ADDRESS or WRITE_DATA received with missing address\r\n");
        }
    }

    void I2cMemory::write_memory_data(void) {
        char buffer[BUFFER_SIZE];

        // Expect 4 more bytes [data]
        if(!this->read(buffer, sizeof(int))) {
            int value = byte_to_int(buffer);
            memory->write(addressPointer, value);
            SimplyLog::Log::d("Storing %d@%d\r\n", value, addressPointer);
        } else {
            SimplyLog::Log::e("WRITE_DATA received with missing data\r\n");
        }
    }
};
