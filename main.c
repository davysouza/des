#include <stdio.h>
#include <stdint.h>

#include "des.h"

int main() {
    DES_STATUS status = DES_SUCCESS;
    uint8_t block[8] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x44, 0x45, 0x53};
    uint8_t key[8]   = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
    
    printf("========== DES Test ==========\n");

    // ----- PLAIN TEXT ----- //
    printf("PLAIN TEXT (Ascii): \"");
    for(uint8_t i = 0; i < 8; i++) {
    	printf("%c", block[i]);
    }
    printf("\"\n");
    
    printf("PLAIN TEXT ( Hex ): ");
    for(uint8_t i = 0; i < 8; i++) {
    	printf("0x%02X ", block[i]);
    }
    printf("\n\n");
    
    uint8_t* cipher = NULL;
    uint64_t cipher_size = 0;
    status = Encrypt(block, 8, key, &cipher, &cipher_size);

    if(status != DES_SUCCESS)
        return 1;
    
    return 0;
}