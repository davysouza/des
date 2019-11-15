/**
 * @file des.h
 * @author Davy A. Souza
 * @date 13 Nov 2019
 * @brief DES library
 * 
 * @details An implementation of DES algorithm.This code is for study purpose 
 * only. If you are thinking about use this code for any other purpose besides 
 * that, you should reconsiderate using a more reliable library.
 *
 * @see https://www.youtube.com/channel/UC1usFRN4LCMcfIV7UjHNuQg/videos
 */
#ifndef DES_H_
#define DES_H_

/**
 * @brief Encrypt
 * 
 * @param[in]
 * @param[in]
 * @param[out]
 *
 * @return
 */
int Encrypt(void);
// int Encrypt(uint8_t plain_text[], uint8_t key[], uint8_t block_cipher[]);
// int Encrypt(uint64_t plain_text, uint64_t key, uint64_t block_cipher);
// int Encrypt(uint64_t plain_text[], uint64_t key, uint64_t block_cipher[]);
// int Encrypt(void* plain_text, size_t plain_text_size, void* key, void* block_cipher, size_t block_cipher_size);

/**
 * @brief Decrypt
 * 
 * @param[in]
 * @param[in]
 * @param[out]
 *
 * @return
 */
int Decrypt(void);
// int Decrypt(uint8_t block_cipher[], uint8_t key[], uint8_t plain_text[]);

#endif  // DES_H_
