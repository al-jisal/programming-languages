#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buffer = malloc(8);

    // Intentionally misalign the pointer
    int *ptr = (int *)(buffer + 1);

    *ptr = 42;

    printf("Value: %d\n", *ptr);

    free(buffer);
    return 0;
}
