#include <stdio.h>

void modify_variable(int* ptr) {
    if (ptr == nullptr)
    {
        return;
    }
    *ptr += 10;
}

void print_variable(const int* value) {
    printf("Variable value: %d\n", *value);
}

int main() {
    int a = 3;
    int b = 4;
    modify_variable(&a);
    print_variable(&a);
    return 0;
}