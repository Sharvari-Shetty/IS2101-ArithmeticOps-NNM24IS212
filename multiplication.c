#include <stdio.h>
#include <stdint.h>

// Function to print n-bit binary of a number
void print_bin_u64(uint64_t x, int bits) {
    for (int i = bits - 1; i >= 0; --i)
        putchar((x >> i) & 1 ? '1' : '0');
}

int main(void) {
    int m, q;
    printf("Enter multiplicand and multiplier (signed integers): ");
    scanf("%d %d", &m, &q);

    int n = 8; // bit width for simulation
    uint64_t mask = (1ULL << n) - 1; // mask to keep numbers within n bits

    uint64_t A = 0;          // Accumulator
    uint64_t M = m & mask;   // Multiplicand
    uint64_t Q = q & mask;   // Multiplier

    printf("\nInitial: A="); print_bin_u64(A, n);
    printf(" Q="); print_bin_u64(Q, n); printf("\n");

    // Repeat n times
    for (int i = 0; i < n; i++) {
        // If Q0 (LSB of Q) is 1, add M to A
        if (Q & 1) A = (A + M) & mask;

        // Combine A and Q into one temp register and right shift
        uint64_t temp = (A << n) | Q;
        temp >>= 1;

        // Split back into A and Q
        A = (temp >> n) & mask;
        Q = temp & mask;

        printf("Step %d: A=", i+1); print_bin_u64(A, n);
        printf(" Q="); print_bin_u64(Q, n); printf("\n");
    }

    // Final product stored in (A,Q)
    uint64_t product = (A << n) | Q;
    printf("\nProduct = %lld\n", (long long)((int64_t)product));
    return 0;
}
