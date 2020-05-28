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
#ifdef DEBUG
    printf("%15s: ", label);
    for(uint32_t i = 0; i < block_size; i++) {
        printf("0x%02X ", block[i]);
    }
    printf("\n");
#endif
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

void KeySplit (
    uint8_t* key,
    uint8_t* left_key, 
    uint8_t* right_key
  )
{
    // Copying left key (first 4 bytes)
    memcpy(left_key, key, 4);

    // Copying right key (last 4 bytes)
    memcpy(right_key, &key[3], 4);
    
    // Remove last 4 bits
    left_key[3] &= 0xF0;

    uint8_t bits_next_pos = 0x00;
    uint8_t bits_curr_pos = 0x00;

    // Shift left bits of the vector (4 positions)
    for(int i = 3; i >= 0; --i) {
        bits_curr_pos = right_key[i] & 0xF0;
        right_key[i] <<= 4;
        bits_next_pos >>= 4;
        right_key[i] |= bits_next_pos;
        bits_next_pos = bits_curr_pos;
    }
}

void Concatenate56BitKey (
    uint8_t left_key[4],
    uint8_t right_key[4],
    uint8_t concatenated_key[8]
  )
{
    // Copying left key
    memcpy(concatenated_key, left_key, 4);

    // Copying right key
    memcpy(concatenated_key + 4, right_key, 4);

    uint8_t bits_next_pos = 0;
    uint8_t bits_curr_pos = 0;

    // Shift left bits of the vector (4 positions)
    for(int i = 7; i >= 4; --i) {
        bits_curr_pos = concatenated_key[i] & 0xF0;
        concatenated_key[i] <<= 4;
        concatenated_key[i] |= bits_next_pos;
        bits_next_pos = bits_curr_pos;
        bits_next_pos >>= 4;
    }

    concatenated_key[3] |= bits_next_pos;
}

void KeyLeftCycleShift (
    const uint8_t key[4], 
    uint8_t       new_key[4]
  )
{
    // Shift the bytes 1, 2 and 3
    uint32_t key28 = key[0];
    for(uint8_t i = 1; i < 4; i++) {
        key28 = (key28 << 8) | key[i];
    }

    // Copy the first bit of byte 0
    uint32_t first_bit = 0;
    first_bit = 0x80000000 & key28;

    key28 <<= 1;
    key28 = key28 | (first_bit >> 27);

    // uint32_t to uint8_t
    memset(new_key, 0x00, 4);
    for(uint8_t i = 0; i < 4; i++) {
        new_key[i] = (key28 >> (32 - ((i+1)*8))) & 0x000000FF;
    }
}

void GenerateSubkey (
    uint8_t C[17][4],
    uint8_t D[17][4],
    uint8_t round
  )
{
    if(round == 1 || round == 2 || round == 9 || round == 16) {
        KeyLeftCycleShift(C[round-1], C[round]);
        KeyLeftCycleShift(D[round-1], D[round]);
    } else {
        KeyLeftCycleShift(C[round-1], C[round]);
        KeyLeftCycleShift(D[round-1], D[round]);

        KeyLeftCycleShift(C[round], C[round]);
        KeyLeftCycleShift(D[round], D[round]);
    }
}

void Generate48BitKey (
    uint8_t C[17][4], 
    uint8_t D[17][4],
    uint8_t round,
    uint8_t key_48bit[16][6]
  )
{
    uint8_t concatenated_key[8] = {0x00};
    Concatenate56BitKey(C[round], D[round], concatenated_key);
    Permutation(concatenated_key, pc2, 48, key_48bit[round-1]);
}

void Feistel (
    uint8_t       right[4], 
    const uint8_t key[6], 
    uint8_t       feistel_cipher[4]
  )
{
    // Expansion
    uint8_t expanded[6];
    Permutation(right, expansion, 48, expanded);
    PrintBlockHex("Expansion", expanded, 6);

    // XOR operation between right block expanded and the 48-bit subkey
    uint8_t xor_key_exp[6];
    for(uint8_t i = 0; i < 6; i++) {
        xor_key_exp[i] = expanded[i] ^ key[i];
    }
    PrintBlockHex("XOR key", xor_key_exp, 6);

    // Substitution choice (S-BOX)
    uint64_t block48;
    ConvertBlockToValue(xor_key_exp, 48, &block48);
    block48 <<= 16;

    uint64_t mask        = 0xFC00000000000000;
    uint64_t current6    = 0x0000000000000000;
    uint64_t row         = 0x0000000000000000;
    uint64_t column      = 0x0000000000000000;
    uint64_t result      = 0x0000000000000000;
    uint64_t mask_result = 0x000000000000000F;

    for(uint8_t i = 0; i < 8; i++) {
        current6 = (mask & block48) >> (64 - (i+1)*6);
        row = (current6 & 0x0000000000000001) | ((current6 & 0x0000000000000020) >> 4);
        column = (current6 & 0x000000000000001E) >> 1;
        result |= (mask_result & s_boxes[i][row][column]) << (64 - (i+1)*4);
        mask >>= 6;        
    }
    result >>= 32;
    
    uint8_t block_result[4] = {0x00};
    ConvertValueToBlock(result, 32, block_result);
    PrintBlockHex("S-box", block_result, 4);

    // Permutation
    Permutation(block_result, permutation, 32, feistel_cipher);
    PrintBlockHex("Permutation", feistel_cipher, 4);
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
#ifdef DEBUG
    printf("Encrypt\n");
#endif

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

    // Key split. 
    // At this step we create the first 28-bit subkeys (C[0] and D[0])
    uint8_t C[17][4];
    uint8_t D[17][4];
    KeySplit(key_56bit, C[0], D[0]);

    // Initial Permutation (IP)
    Permutation(*cipher, initial_permutation, 64, *cipher);
    PrintBlockHex("IP", *cipher, 8);

    // 48-bit keys
    uint8_t key_48bit[16][6];

    // Left and right 32-bits block halves
    uint8_t left[17][4];
    memcpy(left[0], *cipher, 4);

    uint8_t right[17][4];
    memcpy(right[0], (*cipher) + 4, 4);

    // Rounds
    uint8_t feistel_cipher[16][4];
    for(uint8_t round = 1; round <= 16; round++) {
#ifdef DEBUG
        printf("\nRound %d\n", round);
#endif
        // 56-bit key generation
        GenerateSubkey(C, D, round);

        // 48-bit key generation
        Generate48BitKey(C, D, round, key_48bit);
        PrintBlockHex("Round key", key_48bit[round-1], 6);

        memcpy(left[round], right[round-1], 4);
        Feistel(right[round-1], key_48bit[round-1], feistel_cipher[round-1]);

        // XOR between feistel cipher and the left 32-bit block half
        for (uint8_t j = 0; j < 4; j++) {
            right[round][j] = left[round-1][j] ^ feistel_cipher[round-1][j];
        }
    }

    memcpy(*cipher, right[16], 4);
    memcpy((*cipher) + 4, left[16], 4);
    
    // Final Permutation
    Permutation(*cipher, final_permutation, 64, *cipher);

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