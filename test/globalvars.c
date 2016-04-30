#include <stdio.h>

int main();

struct dict {
    int a;
    int b;
};

struct test {
    int *a;
    int (*f)();
    struct dict d;
};

struct test t = {NULL,main,{1,2}};

int main() {
    printf("%i",(-7)%3);
    return 0;
}