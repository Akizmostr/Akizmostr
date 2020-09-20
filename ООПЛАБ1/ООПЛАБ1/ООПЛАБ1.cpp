#include<stdio.h> 
#include<stdarg.h>                      
#include <iostream>
#include <iomanip>

using namespace std;

void Myprintf(const char*, ...);              //Our printf function
char* convert(unsigned int, int);       //Convert integer number into octal, hex, etc.


int main() {
    Myprintf("Formatting... %f \n", 0349000.696990000000000000);
    printf_s("Formatting... %f \n", 0349000.69699000000000000000);

    Myprintf("Formatting... %d \n", 309);
    printf_s("Formatting... %d \n", 309);

    Myprintf("Formatting... %s \n", "Boom");
    printf_s("Formatting... %s \n", "Boom");

    Myprintf("Formatting... %c \n", '|');
    printf_s("Formatting... %c \n", '|');

    return 0;
}


void Myprintf(const char* format, ...) {
    char c;
    int i;
    char* s;
    double f;

    //Initializing Myprintf's arguments 
    va_list arg;
    va_start(arg, format);

    for (char j = 0; format[j] != '\0'; j++) {
        c = format[j];
        if (c != '%') {
            cout << c;
            continue;
        }

        c = format[++j];

        //Fetching and executing arguments
        switch (c) {
        case 'c': i = va_arg(arg, int);     //Fetch char argument
            cout << char(i);
            break;

        case 'd': i = va_arg(arg, int);         //Fetch Decimal/Integer argument
            if (i < 0) {
                i = -i;
                cout << '-';
            }
            cout << i;
            break;
        case 's': s = va_arg(arg, char*);       //Fetch string
            cout << s;
            break;
        case 'f': f = va_arg(arg, double);
            cout << fixed << setprecision(6) << f;
        }
        
    }

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg);
}

char* convert(unsigned int num, int base) {
    static char Representation[] = "0123456789ABCDEF";
    static char buffer[50];
    char* ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = Representation[num % base];
        num /= base;
    } while (num != 0);

    return(ptr);
}