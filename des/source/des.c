#include <stdio.h>
#include <stdint.h>

#include "des.h"
#include "des_internals.h"

DES_STATUS Encrypt(
    const uint8_t*  buffer, 
    const uint64_t  buffer_size, 
    const uint8_t   key[8],
    uint8_t**       cipher,
    uint64_t*       cipher_size
) {
    printf("Encrypt\n");
    return DES_SUCCESS;
}

int Decrypt(void) {
    printf("Decrypt\n");
    return 0;
}