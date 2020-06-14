# Simple DES Library
This is a simple implementation of DES algorithm. DES (Data Encryption Standard) is a symetric-key algorithm for the encryption of digital data. Although its short key length of 56 bits makes it too insecure for modern applications, it has been highly influential in the advancement of cryptography and its a good case study for cryptography students.

## The Library
The library is composed by only two functions, **Encrypt** and **Decrypt**:
```c
DES_STATUS Encrypt (
    const uint8_t*  buffer, 
    const uint64_t  buffer_size, 
    const uint8_t   key[8],
    uint8_t**       cipher,
    uint64_t*       cipher_size
  );
  
// TODO: Decrypt function
int Decrypt(void);
```
## Compiling
To compile the library and tests:
```sh
$ make all
```

To compile only the library:
```sh
$ make lib
```

To compile only the tests:
```sh
$ make tests
```

## Unit Tests
