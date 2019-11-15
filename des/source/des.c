#include <stdio.h>
#include <stdint.h>

#include "des.h"
#include "des_internals.h"

int Encrypt(void) {
    printf("Encrypt\n");
    printf("Initial Permutation: %d\n", initial_permutation[0]);
    return 0;
}

int Decrypt(void) {
    printf("Decrypt\n");
    return 0;
}