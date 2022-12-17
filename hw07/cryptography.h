// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global macros, structures and fields to be used by the
 * rsa file.
 */
#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "my_string.h"

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially

// public_key struct
struct public_key {
    int n;
    int e;
};

// private_key struct
struct private_key {
    int n;
    int d;
};

// Prototype cryptography.c functions
void encrypt(int *ciphertext, char *plaintext, struct public_key pub_key);
void decrypt(char *plaintext, int *ciphertext, int plaintext_length, struct private_key pri_key);
int power_and_mod(int b, int e, int n);

#endif
