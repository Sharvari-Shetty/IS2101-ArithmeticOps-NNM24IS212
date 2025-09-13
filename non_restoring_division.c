#include <stdio.h>
#include <stdint.h>

// Print binary with given bit width
void print_bin(int x, int bits) {
    for (int i = bits - 1; i >= 0; --i)
        putchar((x >> i) & 1 ? '1' : '0');
}

int main(void) {
    unsigned int dividend, divisor;
    printf("Enter dividend and divisor (positive integers): ");
    scanf("%u %u", &dividend, &divisor);

    int n = 8; // bit width
    int A = 0;  // Accumulator
    unsigned int Q = dividend, M = divisor;

    printf("\nInitial: A="); print_bin(A, n+1);
    printf(" Q="); print_bin(Q, n); printf("\n");

    for (int i = 0; i < n; i++) {
        // Left shift (A, Q)
        A = (A << 1) | (Q >> (n-1));
        Q = (Q << 1) & ((1 << n) - 1);

        // If A >= 0, subtract M
        if (A >= 0) {
            A = A - M;
            if (A >= 0) Q |= 1;
        } 
        // If A < 0, add M
        else {
            A = A + M;
            if (A >= 0) Q |= 1;
        }

        printf("Step %d: A=", i+1); print_bin(A, n+1);
        printf(" Q="); print_bin(Q, n); printf("\n");
    }

    // Final correction if A < 0
    if (A < 0) A += M;

    printf("\nQuotient = %u, Remainder = %d\n", Q, A);
    return 0;
}
