#pragma once

#include "mbed.h"
#include <stdio.h>
#include <stdarg.h>
#include <ctime>

// Define this before loading the header file to enable debug mode
//#define DEBUG_MODE 1

namespace SimplyLog
{
    class Log
    {
        public:
            static void e(char* fmt, ...) {
                char buffer [80];
                Log::getTimestamp(buffer);

                va_list args;
                va_start(args,fmt);
                printf("%s ", buffer);
                printf("[ERROR] ");
                vprintf(fmt,args);
                va_end(args);
            }

            static void w(char* fmt, ...) {
                char buffer [80];
                Log::getTimestamp(buffer);

                va_list args;
                va_start(args,fmt);
                printf("%s ", buffer);
                printf("[WARNING] ");
                vprintf(fmt,args);
                va_end(args);
            }

            static void d(char* fmt, ...) {
                #ifdef DEBUG_MODE
                char buffer [80];
                Log::getTimestamp(buffer);

                va_list args;
                va_start(args,fmt);
                printf("%s ", buffer);
                printf("[DEBUG] ");
                vprintf(fmt,args);
                va_end(args);
                #endif
            }

            static void i(char* fmt, ...) {
                #ifdef DEBUG_MODE
                char buffer [80];
                Log::getTimestamp(buffer);

                va_list args;
                va_start(args,fmt);
                printf("%s ", buffer);
                printf("[INFO] ");
                vprintf(fmt,args);
                va_end(args);
                #endif
            }

        private:
            static void getTimestamp(char * buffer) {
                time_t rawtime;
                struct tm * timeinfo;

                time (&rawtime);
                timeinfo = localtime (&rawtime);

                strftime(buffer, 80, "%d-%m-%Y|%H:%M:%S", timeinfo);
            }
    };
}