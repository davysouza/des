
# Simple DES Library

This is a simple implementation of DES algorithm. DES (Data Encryption Standard) is a symetric-key algorithm for the encryption of digital data. Although its short key length of 56 bits makes it too insecure for modern applications, it has been highly influential in the advancement of cryptography and its a good case study for cryptography students.

  

## The Library

The library is composed by only two functions, **Encrypt** and **Decrypt**:

```c

DES_STATUS Encrypt  (

const uint8_t* buffer,

const uint64_t buffer_size,

const uint8_t key[8],

uint8_t** cipher,

uint64_t* cipher_size

);

// TODO: Decrypt function

int  Decrypt(void);

```

## Compiling

To compile and execute both library and tests:

```sh

$ make all

```

  

To compile the ``simpledes.so`` library:

```sh

$ make lib

```

This command will create an `.so` file with their respective symbolic links.

  

If you want to compile only the tests, you can execute:

```sh

$ make tests

```

  

If you already had compiled the source code and want just to execute the generated files, you may want to run:

```sh

$ make run_main_tests

```

  
  

## Unit Tests
*TBD*