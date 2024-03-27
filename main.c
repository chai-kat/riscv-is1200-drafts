#include "implementprintf.c"

int main() {
    test_printf("The chosen number is %i\n", 42);
    test_printf("The negative chosen number is %d\n", -42);
    test_printf("The unsigned chosen number is %u\n", -1);
    test_printf("The chosen character is %c\n", 'A');
    test_printf("The chosen string is %s\n", "Hello, World!");
    test_printf("The chosen hexadecimal number is %x\n", 64);
    test_printf("The chosen octal number is %o\n", 64);
    test_printf("The chosen floating point number is %f\n", 3.14);
    

    return 0;
}