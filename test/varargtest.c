#include <stdio.h>
#include <stdarg.h>

void test2(int a, char b, int c) {
    printf("%i %c %i",a,b,c);
}

void test (int n, ...) {
    va_list args;
    va_start(args,n);
    printf("%i ", n);
    printf("%c ", (char) va_arg(args,int));
    printf("%i\n", (int) va_arg(args,int));
}

int main () {
    test(1,'a',3);
    test2(2,'b',4);
    return 1;
}