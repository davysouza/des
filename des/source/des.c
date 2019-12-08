#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "des.h"
#include "des_internals.h"

// 
// Utils
// 

void PrintBlockHex (
    const char*    label,
    const uint8_t* block,
    const uint32_t block_size
  )
{
    printf("%5s: ", label);
    for(uint32_t i = 0; i < block_size; i++) {
        printf("0x%02X ", block[i]);
    }
    printf("\n");
}

void ConvertBlockToValue (
    const uint8_t* block, 
    uint64_t       block_size, 
    uint64_t*      value
  )
{
    *value = block[0];
    for(uint64_t i = 1; i < (block_size / 8); i++) {
        *value = (*value << 8) | block[i];
    }
}

void ConvertValueToBlock (
    const uint64_t value, 
    uint64_t       value_size, 
    uint8_t*       block
  )
{
    // Cleaning result block
    memset(block, 0x00, value_size / 8);

    // calculate extra bytes to be removed
    int32_t extra_bytes = (BLOCK_SIZE - value_size) / 8;

    // Copying value to block
    for(uint64_t i = 0; i < (value_size / 8); i++) {
        block[i] = (value >> (BLOCK_SIZE - ((i + extra_bytes + 1)*8))) & 0x00000000000000FF;
    }
}

// 
// DES
// 

void Permutation (
    uint8_t*       block,
    const uint8_t* permutation,
    uint64_t       permutation_size,
    uint8_t*       result
  ) 
{
    uint64_t block_64bit;
    ConvertBlockToValue(block, BLOCK_SIZE, &block_64bit);

    uint64_t result_64bit = 0x0000000000000000;
    for (uint8_t i = 0; i < permutation_size; i++) {
        // Switch bit
        uint64_t mask = 0x0000000000000001;
        mask <<= (64 - permutation[i]);

        // Shift length
        int8_t shift_length = permutation[i] - (i+1);

        if(shift_length > 0) {
            result_64bit |= ((mask & block_64bit) << shift_length);
        } else {
            result_64bit |= ((mask & block_64bit) >> (-shift_length));
        }
    }
    result_64bit >>= BLOCK_SIZE - permutation_size;

    ConvertValueToBlock(result_64bit, permutation_size, result);
}

// 
// External functions
// 

DES_STATUS Encrypt (
    const uint8_t*  buffer, 
    const uint64_t  buffer_size, 
    const uint8_t   key[8],
    uint8_t**       cipher,
    uint64_t*       cipher_size
  ) 
{
    printf("Encrypt\n");

    uint8_t* key_64bit = NULL;
    uint8_t* key_56bit = NULL;

    // Allocating and initializing cipher
    *cipher = (uint8_t*) malloc(buffer_size);
    memcpy(*cipher, buffer, buffer_size);

    // Allocating and initializing internal key
    key_64bit = (uint8_t*) malloc(8);
    memcpy(key_64bit, key, 8);

    // Initial transformation (PC-1)
    key_56bit = (uint8_t*) malloc(7);
    Permutation(key_64bit, pc1, 56, key_56bit);
    PrintBlockHex("PC-1", key_56bit, 7);

    // Initial Permutation (IP)
    Permutation(*cipher, initial_permutation, 64, *cipher);
    PrintBlockHex("IP", *cipher, 8);

    // TODO: Transformation rounds
    // TODO: Feistel
    // TODO: Encryption rounds

    // TODO: Final Permutation

    if(key_64bit != NULL) {
        free(key_64bit);
        key_64bit = NULL;
    }

    if(key_56bit != NULL) {
        free(key_56bit);
        key_56bit = NULL;
    }

    return DES_SUCCESS;
}

int Decrypt(void) {
    printf("Decrypt\n");
    return 0;
}