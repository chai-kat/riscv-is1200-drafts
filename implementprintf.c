// written by Chaitanya Katpatal 
// latest update on 2021-06-02

#include <stdarg.h>
// #include <stdio.h>

extern int putchar(char c);
typedef unsigned long size_t;

// using geeksforgeeks.org/implement-itoa/, they use a helper reverse function
void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void* memcpy(void* to, void* from, size_t count) {
    char* t = (char*) to;
    char* f = (char*) from;
    for (int i = 0; i < count; i++) {
        t[i] = f[i];
    }
    return to;
}

int strlen(char* str) {
    int count = 0;
    while (*str) {
        count++;
        str++;
    }
    return count;

}

char* strcpy(char* to, char* from) {
    char* t = to;
    while (*from) {
        *t = *from;
        t++;
        from++;
    }
    *t = '\0';
    return to;
}

// this implementation differs somewhat from geeksforgeeks.org/implement-itoa/ 
// it does not handle the sign
char* itoa_sgnd(int num, char* buffer, int base) {
    int i = 0;
    // int isNegative = 0;

    // handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // in standard itoa, negative numbers are handled only with base 10
    // otherwise numbers are considered unsigned
    if (num < 0 && base == 10) {
        // isNegative = 1;
        num = -num;
    }

    // process individual digits
    while (num != 0) {
        int rem = num % base;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // // if number is negative, append '-'
    // if (isNegative) {
    //     buffer[i++] = '-';
    // }

    buffer[i] = '\0'; // null terminate string

    // reverse the string
    reverse(buffer, i);

    return buffer;

}

char* itoa_unsgnd(unsigned int num, char* buffer, int base) {
    int i = 0;

    // handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // process individual digits
    while (num != 0) {
        int rem = num % base;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    buffer[i] = '\0'; // null terminate string

    // reverse the string
    reverse(buffer, i);

    return buffer;
}

char* ftoa(float num, char* buffer, int afterpoint) {
    int i = 0;
    int integer = (int) num;
    float fraction = num - integer;

    char intBuffer[21];
    char* integerString = itoa_sgnd(integer, intBuffer, 10);
    int intLength = strlen(integerString);

    memcpy(buffer, integerString, intLength);

    i += intLength; // move write position forward
    buffer[i++] = '.'; // add decimal point
    
    for(int j = 0; j < afterpoint; j++) {
        fraction *= 10;
    }

    int fractionInt = (int) fraction;
    char* fractionBuffer[afterpoint + 1];
    char* fractionString = itoa_sgnd(fractionInt, fractionBuffer, 10);

    strcpy(buffer + i, fractionString);

    return buffer;
}

int test_printf(char *fstring, ...) {
    int counter = 0;
    va_list ap;
    va_start(ap, fstring);

    while (*fstring) {

        // handle a format code
        if(*fstring == '%') {
            // move to the next character to see the code
            fstring++;

            // fill out the flag fields
            if  (*fstring == '-') {
                // do nothing with - flag for now
                // this left-justifies the output
                fstring++;
            }

            char sign = '!';
            if (*fstring == '+' || *fstring == ' ') {
                sign = *fstring;
                fstring++;
            }

            if(*fstring == '#') {
                // do nothing with # for now
                fstring++;
            }
            if(*fstring == '0') {
                // do nothing with 0 flag for now
                fstring++;
            }

            // if it's a number, fill out the width first
            int width = 0;
            while (*fstring >= '0' && *fstring <= '9') {
                width = width * 10 + (*fstring - '0');
                fstring++;
            }

            // if it's a period followed by a number, fill out the precision
            int precision = 0;
            int precisionIsSet = 0;
            if (*fstring == '.') {
                precisionIsSet = 1;
                fstring++;
                while (*fstring >= '0' && *fstring <= '9') {
                    precision = precision * 10 + (*fstring - '0');
                    fstring++;
                }
            }

            // handle %d, print an integer in decimal
            if (*fstring == 'd' || *fstring == 'i') {
                int num = va_arg(ap, int);
                int isNegative = (num < 0)? 1 : 0;
                if (isNegative) {
                    num = -num;
                }

                if (sign == '+') {
                    if (isNegative) {
                        putchar('-');
                    }
                    else {
                        putchar('+');
                    }
                    counter++;
                }
                else if (sign == ' ') {
                    if (isNegative) {
                        putchar('-');
                    }
                    else {
                        putchar(' ');
                    }
                    counter++;
                }
                else {
                    if (isNegative) {
                        putchar('-');
                    }
                    counter++;
                }

                // log_10(2 ^ 64) = 19.26, so 21 characters is always enough for the buffer (incl. '\0') (incl. '\0')
                // in fact, we could do with 19 since the int is signed
                char buffer[21];
                char* b = itoa_sgnd(num, buffer, 10);
                
                // we use *b in place of buffer,
                // (arrays are not modifiable lvalues in C, but pointers are)
                while (*b) {
                    putchar(*b);
                    b++;
                    counter++;
                }
            }

            // handle %u, print an unsigned integer
            else if (*fstring == 'u') {
                int num = va_arg(ap, int);
                // log_10(2 ^ 64) = 19.26, so 21 characters is always enough for the buffer (incl. '\0')
                char buffer[21];
                char* b = itoa_unsgnd((unsigned int) num, buffer, 10);

                // we use *b in place of buffer,
                // (arrays are not modifiable lvalues in C, but pointers are)
                while (*b) {
                    putchar(*b);
                    b++;
                    counter++;
                }
            }

            // handle %o, print an octal integer
            else if (*fstring == 'o') {
                // TODO: add code to print out '0' if # flag given

                int num = va_arg(ap, int);
                // log_10(2 ^ 64) = 19.26, so 21 characters is always enough for the buffer (incl. '\0')
                char buffer[21];
                char* b = itoa_unsgnd((unsigned int) num, buffer, 8);

                // we use *b in place of buffer,
                // (arrays are not modifiable lvalues in C, but pointers are)
                while (*b) {
                    putchar(*b);
                    b++;
                    counter++;
                }
            }

            // handle %x, print a hexadecimal integer
            else if (*fstring == 'x') {
                // TODO: add code to print out '0x' if # flag given

                int num = va_arg(ap, int);
                // log_10(2 ^ 64) = 19.26, so 21 characters is always enough for the buffer (incl. '\0')
                char buffer[21];
                char* b = itoa_unsgnd((unsigned int) num, buffer, 16);

                // we use *b in place of buffer,
                // (arrays are not modifiable lvalues in C, but pointers are)
                while (*b) {
                    putchar(*b);
                    b++;
                    counter++;
                }
            }

            // handle %X, print a hexadecimal integer (uppercase)
            else if (*fstring == 'X') {
                // TODO: add code to print out '0X' if # flag given

                int num = va_arg(ap, int);
                // log_10(2 ^ 64) = 19.26, so 21 characters is always enough for the buffer (incl. '\0')
                char buffer[21];
                char* b = itoa_unsgnd((unsigned int) num, buffer, 8);

                // capital values are 32 less than lowercase values
                for(int i = 0; i < 21; i++) {
                    if (buffer[i] == '\0') {
                        break;
                    }

                    if (buffer[i] >= 'a' && buffer[i] <= 'f') {
                        buffer[i] -= 32;
                    }
                }

                // we use *b in place of buffer,
                // (arrays are not modifiable lvalues in C, but pointers are)
                while (*b) {
                    putchar(*b);
                    b++;
                    counter++;
                }
            }

            // handle %f or %F, print a decimal floating point number (lowercase and uppercase, respectively)
            else if (*fstring == 'f' || *fstring == 'F') {
                float num = va_arg(ap, double);

                // by default, 6 decimal places are printed
                if (!precisionIsSet) {
                    precision = 6;
                }

                // we need (int precision) characters for the fraction, 
                // plus up to 22 for the integer + null terminator + decimal point
                char buffer[precision + 22];
                char* b = ftoa(num, buffer, precision);

                while (*b) {
                    putchar(*b);
                    b++;
                    counter++;
                }

            }

            // handle %e, print a floating point number in scientific notation
            else if (*fstring == 'e') {

            }

            // handle %E, print a floating point number in scientific notation (uppercase)
            else if (*fstring == 'E') {

            }

            // won't handle %g, %A


            // handle %c, print a character
            else if (*fstring == 'c') {
                char ch = va_arg(ap, char);
                putchar(ch);
                counter++;
            }

            // handle %s, print a string
            else if (*fstring == 's') {
                char *str = va_arg(ap, char*);
                while (*str) {
                    putchar(*str);
                    str++;
                    counter++;
                }
            }


            // handle %p, print a pointer address
            else if (*fstring == 'p') {

            }

            // handle %n, nothing printed
            // argument must be pointer to a signed int
            // number of characters printed so far stored in signed location
            else if (*fstring == 'n') {
                int *location = va_arg(ap, int*);
                *location = counter;
            }

            // handle %%
            if (*fstring == '%') {
                putchar('%');
                counter++;
            }


        }
        else {
            putchar(*fstring);
            counter++;
        }
        fstring++;
    }

    va_end(ap);
    return counter;
}


void* self_malloc() {
    return 0;
}

void free() {}