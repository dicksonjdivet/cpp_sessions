#include <stdio.h>

extern "C"
{
    void print_int(int value) {
        printf("%d\n", value);
    }

    void print_double(double value) {
        printf("%f\n", value);
    }
}


int main() {
    print_int(42);
    print_double(3.14);
    return 0;
}