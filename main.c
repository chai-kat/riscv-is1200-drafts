#include "implementprintf.c"

int main() {
    test_printf("The chosen number is %i\n", 42);
    test_printf("The negative chosen number is %d\n", -42);
    test_printf("The unsigned chosen number is %u\n", -1);
    test_printf("The chosen character is %c\n", 'A');
    test_printf("The chosen string is %s\n", "Hello, World!");
    test_printf("The chosen hexadecimal number is %x\n", 64);
    test_printf("The chosen truncated long hexadecimal number is %x\n", 0xdeadbeef12345678);
    test_printf("The chosen octal number is %o\n", 64);
    test_printf("The chosen floating point number is %.04f\n", 3.14);


    int x = 5;
    long ptr = 0xdeadbeef12345678;

    test_printf("The pointer to x is %p\n", (void*) &x);
    test_printf("ptr is %p\n", (void*) ptr);

    return 0;
}