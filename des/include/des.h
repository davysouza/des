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

#include <stdint.h>

typedef enum _DES_STATUS {
    DES_SUCCESS = 0,
} DES_STATUS;

/**
 * @brief Encrypts @p buffer using @p key and returns the ciphered buffer on 
 *        @p cipher
 * 
 * @param[in]  buffer       Buffer of bytes to be encrypted
 * @param[in]  buffer_size  Size of @p buffer
 * @param[in]  key          8-byte key used to encrypt @p buffer
 * @param[out] cipher       Cipher resulted from @p buffer encryption
 * @param[out] cipher_size  Size of @p cipher
 *
 * @return Returns @p DES_SUCCESS on a successful buffer encryption, or an error 
 *         code otherwise.
 */
DES_STATUS Encrypt(
    const uint8_t*  buffer, 
    const uint64_t  buffer_size, 
    const uint8_t   key[8],
    uint8_t**       cipher,
    uint64_t*       cipher_size
);

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
