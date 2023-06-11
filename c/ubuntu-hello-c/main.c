#include <stdio.h>

int main() {
    // comment
    int a = 1;
    int b = 2;
    int c = a + b;
    int d = 4;
    if (c > 5) {
        c = 0;
    }
    switch (a) {
        case 1: {
            c = 1;
            break;
        }
        case 2: {
            c = 1;
            break;
        }
        default: {
            c = 3;
            break;
        }
    }
    char* s = "hello world";
    printf("\nHello World!\n");
    return 0;
}