#include "shell.h"

void print(const char* format, ...)
{
    const char* p;
    va_list args;
    va_start(args, format);

   
    for (p = format; *p != '\0'; ++p)
    {
        if (*p == '%')
        {
            
            ++p; 

            
            switch (*p)
            {
                case 'd':
                {
                    int value = va_arg(args, int);
                    print("%d", value);
                    break;
                }
                case 'f':
                {
                    double value = va_arg(args, double);
                    print("%f", value);
                    break;
                }
                case 's':
                {
                    char* value = va_arg(args, char*);
                    print("%s", value);
                    break;
                }
                default:
                    putchar(*p);
                    break;
            }
        }
        else
        {
           
            putchar(*p);
        }
    }


    va_end(args);
}