#ifndef DES_INTERNALS_H_
#define DES_INTERNALS_H_

#define BLOCK_SIZE 64

/**
 * @brief Initial permutation table
 */
const uint8_t initial_permutation[64] = { 
  58, 50, 42, 34, 26, 18, 10,  2, 
  60, 52, 44, 36, 28, 20, 12,  4,
  62, 54, 46, 38, 30, 22, 14,  6, 
  64, 56, 48, 40, 32, 24, 16,  8,
  57, 49, 41, 33, 25, 17,  9,  1, 
  59, 51, 43, 35, 27, 19, 11,  3,
  61, 53, 45, 37, 29, 21, 13,  5, 
  63, 55, 47, 39, 31, 23, 15,  7
};

/**
 * @brief Final permutation table
 */
const uint8_t final_permutation[64] = {
  40,  8, 48, 16, 56, 24, 64, 32, 
  39,  7, 47, 15, 55, 23, 63, 31,
  38,  6, 46, 14, 54, 22, 62, 30, 
  37,  5, 45, 13, 53, 21, 61, 29,
  36,  4, 44, 12, 52, 20, 60, 28, 
  35,  3, 43, 11, 51, 19, 59, 27,
  34,  2, 42, 10, 50, 18, 58, 26, 
  33,  1, 41,  9, 49, 17, 57, 25
};

/**
 * @brief Expansion table
 */
const uint8_t expansion[48] = {
  32,  1,  2,  3,  4,  5,
   4,  5,  6,  7,  8,  9,
   8,  9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,
  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32,  1
};

/**
 * @brief Permutation table
 */
const uint8_t permutation[32] = {
  16,  7, 20, 21, 29, 12, 28, 17,
   1, 15, 23, 26,  5, 18, 31, 10,
   2,  8, 24, 14, 32, 27,  3,  9,
  19, 13, 30,  6, 22, 11,  4, 25
};

/**
 * @brief Permuted Choice (PC-1) table
 */
const uint8_t pc1[56] = {
  57, 49, 41, 33, 25, 17,  9,
   1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27,
  19, 11,  3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
  14,  6, 61, 53, 45, 37, 29,
  21, 13,  5, 28, 20, 12,  4
};

/**
 * @brief Permuted Choice (PC-2) table
 */
const uint8_t pc2[48] = {
  14, 17, 11, 24,  1,  5,
   3, 28, 15,  6, 21, 10,
  23, 19, 12,  4, 26,  8,
  16,  7, 27, 20, 13,  2,
  41, 52, 31, 37, 47, 55,
  30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53,
  46, 42, 50, 36, 29, 32
};

/**
 * @brief DES S-Boxes
 */
const uint8_t s_boxes[8][4][16] = {
  {
    {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
  },
  {
    {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12, 0,  5, 10},
    { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6, 9, 11,  5},
    { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9, 3,  2, 15},
    {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0, 5, 14,  9}
  },
  {
    {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
    {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
    {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
    { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
  },
  {
    { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
    {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
    {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
    { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
  },
  {
    { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
    {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
    { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
    {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
  },
  {
    {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
    {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
    { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
    { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
  },
  {
    { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
    {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
    { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
    { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
  },
  {
    {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
    { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
    { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
    { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
  },
};

/**
 * @brief Print block in hex format
 * 
 * @param[in] label       Label to identify the block
 * @param[in] block       Block to be printed
 * @param[in] block_size  Size of @p block
 */
void PrintBlockHex (
    const char*    label,
    const uint8_t* block,
    const uint32_t block_size
  );

/**
 * @brief Convert a block to a 64-bit value. The block must be at most 8 bytes 
 *        (64 bits).
 * 
 * @param[in]  block       Pointer to the block to be converted
 * @param[in]  block_size  Size of @p block (bits)
 * @param[out] value       64-bit variable representing the block
 */
void ConvertBlockToValue (
    const uint8_t* block, 
    uint64_t       block_size, 
    uint64_t*      value
  );

/**
 * @brief Convert a 64-bit value to a block.
 * 
 * @param[in]  value       Value to be converted
 * @param[in]  value_size  Size of @p value (bits)
 * @param[out] block       Block representation of @p value
 */
void ConvertValueToBlock (
    const uint64_t value, 
    uint64_t       value_size, 
    uint8_t*       block
  );

/**
 * @brief Permute bits of @p block using the permutation table specified
 * 
 * @details Shift the bits of @p block, according to the permutation table 
 * 
 * @param[in]  block            Block to be permutated
 * @param[in]  permutation      Permutation table
 * @param[in]  permutation_size Permutation table size
 * @param[out] result           Permutated block
 */
void Permutation (
    uint8_t*       block,
    const uint8_t* permutation,
    uint64_t       permutation_size,
    uint8_t*       result
  );

/**
 * @brief Split a 56-bit key into two 28-bit keys left aligned
 * 
 * @param[in]  key       56-bit key to be splited
 * @param[out] left_key  left key
 * @param[out] right_key right key
 */
void KeySplit (
    uint8_t* key,
    uint8_t* left_key, 
    uint8_t* right_key
  );

/**
 * @brief Concatenate a two 28-bit keys into a single 56-bit key (left aligned)
 * 
 * @param[in]  left_key         Left 28-bit key to be concatenated
 * @param[in]  right_key        Right 28-bit key to be concatenated
 * @param[out] concatenated_key 56-bit key returned
 */
void Concatenate56BitKey (
    uint8_t left_key[4],
    uint8_t right_key[4],
    uint8_t concatenated_key[8]
  );

/**
 * @brief Makes a left cycle shift at @p key generating @p new_key
 * 
 * @param[in]  key     key to be shifted
 * @param[out] new_key Left cycle shifted key
 */
void KeyLeftCycleShift (
    const uint8_t key[4], 
    uint8_t       new_key[4]
  );

/**
 * @brief Generate subkey
 * 
 * @details Generate a subkey based on the key of the previous round
 * 
 * @param[in,out] C     C-Array containing the 28-bit subkeys of all previous 
 *                      rounds and where the current subkey will be stored
 * @param[in,out] D     D-Array containing the 28-bit subkeys of all previous
 *                      rounds and where the current subkey will be stored
 * @param[in]     round Current round
 */
void GenerateSubkey (
    uint8_t C[17][4],
    uint8_t D[17][4],
    uint8_t round
  );

/**
 * @brief Generate a 48-bit key making a permutation with PC-2 table and the 
 *        28-bit subkeys of the current round
 * 
 * @param[in]  C         C-Array containing all 28-bit subkeys up to the current
 *                       round
 * @param[in]  D         D-Array containing all 28-bit subkeys up to the current
 *                       round 
 * @param[in]  round     Current round
 * @param[out] key_48bit 48-bit key generated
 */
void Generate48BitKey (
    uint8_t C[17][4], 
    uint8_t D[17][4],
    uint8_t round,
    uint8_t key_48bit[16][6]
  );

/**
 * @brief Feistel function
 * 
 * @param[in]  right          Right half of bytes to be used on Feistel function
 * @param[in]  key            48-bit key to be used on Feistel function
 * @param[out] feistel_cipher Feistel cipher generated
 */
void Feistel (
    uint8_t       right[4], 
    const uint8_t key[6], 
    uint8_t       feistel_cipher[4]
  );

#endif  // DES_INTERNALS_H_
