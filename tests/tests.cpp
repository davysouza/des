#include <gtest/gtest.h>

extern "C"{
#include <des.h>
}

TEST(EncryptTest, EcryptSingleBlockSuccess) {
  DES_STATUS status = DES_SUCCESS;
  uint8_t block[8]  = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x44, 0x45, 0x53};
  uint8_t key[8]    = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};

  uint8_t* cipher = NULL;
  uint64_t cipher_size = 0;
  status = Encrypt(block, 8, key, &cipher, &cipher_size);

  uint8_t expected_cipher[8] = {0x59, 0xB0, 0xB0, 0x6C, 0x7A, 0xC2, 0x41, 0x55};

  ASSERT_EQ(status, DES_SUCCESS);
  ASSERT_TRUE(memcmp(cipher, expected_cipher, 8) == 0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
