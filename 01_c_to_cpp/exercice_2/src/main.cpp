#include <stdio.h>

int my_library_sum(int a, int b) {
    return a + b;
}

int main() {
    int result = my_library_sum(3, 4);
    printf("The sum is: %d\n", result);
    return 0;
}