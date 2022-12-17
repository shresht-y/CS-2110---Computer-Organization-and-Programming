/**
 * @file cryptography.c
 * @author YOUR NAME HERE
 * @brief rsa encryption and decryption helper functions
 * @date 2022-10-xx
 */

#include "cryptography.h"

/** encrypt
 *
 * @brief encrypts (through RSA) a plaintext (decrypted) null-terminated string and writes 
 *        into a ciphertext (encrypted) integer array 
 *          NOTE: the helper function "power_and_mod" must be used or else overflow will occur
 *
 * @param "ciphertext" pointer to an integer that represents an ciphertext integer array
 * @param "plaintext" string that represents the plaintext to be encrypted
 * @param "pub_key" struct public_key that is used for the RSA encryption
 * @return void
 */
void encrypt(int ciphertext[], char *plaintext, struct public_key pub_key) {
    int i = 0;
    char currChar = *(plaintext + i);
    while (currChar != '\0') {
        currChar = *(plaintext + i);
        int charInt = (int) currChar;
        int outputVal = power_and_mod(charInt, pub_key.e, pub_key.n);
        ciphertext[i] = outputVal;
        i++;
    }
}

/** decrypt
 *
 * @brief decrypts (through RSA) a ciphertext (encrypted) integer array and writes 
 *        into a string that is null-terminated
 *          NOTE: the helper function "power_and_mod" must be used or else overflow will occur
 *
 * @param "ciphertext" pointer to an integer that represents an ciphertext integer array to be decrypted
 * @param "plaintext" string that represents the decrypted string of the ciphertext
 * @param "plaintext_length" the length that the plaintext should be
 * @param "pri_key" struct private_key that is used for the RSA decryption
 * @return void
 */
void decrypt(char *plaintext, int *ciphertext, int plaintext_length, struct private_key pri_key) {
    int i = 0;
    while (i < plaintext_length) {
        int num = ciphertext[i];
        int originalNum = power_and_mod(num, pri_key.d, pri_key.n);
        char number = (char) originalNum;
        *(plaintext + i) = number;
        i++;
    }
    *(plaintext + i) = '\0';
}

/*
 * Calculates (b^e)%n without overflow
 */
int power_and_mod(int b, int e, int n) {
    long int currNum = 1;
    for (int i = 0; i < e; i++) {
        currNum *= b;
        if (currNum >= n) {
            currNum %= n;
        }
    }
    return (int) currNum % n;
}