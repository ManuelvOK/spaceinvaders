#include <stdio.h>
#include <stdarg.h>

void test2(va_list args) {
    printf("%c ", (char) va_arg(args,int));
    printf("%i\n", (int) va_arg(args,int));
}

void test (int n, ...) {
    va_list args;
    va_start(args,n);
    printf("%i ", n);
    test2(args);
}

int main () {
    test(1,'a',3);
    return 1;
}