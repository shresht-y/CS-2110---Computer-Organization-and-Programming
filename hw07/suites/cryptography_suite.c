/**
 * @file cryptography_suite.c
 * @author Adrien
 * @brief Testing Suites to HW7 - Fall 2022
 * @date 2022-10-14
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

#define INCORRECT_RESULT_MSG "array at index %d not populated correctly. Expected: %s, %d, %d (in order).\nargv[1]='%s'\n"

// Helper function prototypes
static void setup(void);
static void _encrypt(int *ciphertext, char *plaintext, struct public_key pub_key);

///////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************* TESTS ***********************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/* encrypt() tests */
START_TEST(test_encrypt_1) {
    char *string = "Mint chocolate chip is a bad flavor.";
    struct public_key pub_key = {1333, 97};
    const int length = 36;
    int ciphertext[36];
    int actual[36];

    encrypt(ciphertext, string, pub_key);
    _encrypt(actual, string, pub_key);

  for (int i = 0; i < length; i++) {
    ck_assert_int_eq(ciphertext[i], actual[i]);
  }
}
END_TEST

START_TEST(test_encrypt_2) {
    char *string = "Cowboys don't belong anywhere near a Super Bowl.";
    const struct public_key pub_key = {526567, 65537};
    const int length = 48;
    int ciphertext[48];
    int expected[48];

    encrypt(ciphertext, string, pub_key);
    _encrypt(expected, string, pub_key);

  for (int i = 0; i < length; i++) {
    ck_assert_int_eq(ciphertext[i], expected[i]);
  }
}
END_TEST

/* decrypt() tests */
START_TEST(test_decrypt_1) {
    char *string = "Mint chocolate chip is a bad flavor.";
    const struct public_key pub_key = {1333, 97};
    const int length = 36;
    int ciphertext[36];
    _encrypt(ciphertext, string, pub_key);

    char actual[37];

    const struct private_key priv_key = {1333, 13};
    decrypt(actual, ciphertext, length, priv_key);
    
    ck_assert_msg(actual[length] == 0, "Expected null terminator at the end of decrypted message.");
    ck_assert_msg(strncmp(actual, string, length) == 0, "Expected message to be %s, was %s", string, actual);
}
END_TEST

START_TEST(test_decrypt_2) {
    char *string = "Cowboys don't belong anywhere near a Super Bowl.";
    const struct public_key pub_key = {526567, 65537};
    const int length = 48;
    int ciphertext[48];
    _encrypt(ciphertext, string, pub_key);

    char actual[49];

    const struct private_key priv_key = {526567, 4157};
    decrypt(actual, ciphertext, length, priv_key);

    ck_assert_msg(actual[length] == 0, "Expected null terminator at the end of decrypted message.");
    ck_assert_msg(strncmp(actual, string, length) == 0, "Expected message to be %s, was %s", string, actual);
}
END_TEST

/* test encrypt() and decrypt() together */
START_TEST(test_encrypt_and_decrypt) {
    char *string = "This is a super secret and highly classified message that should be encrypted...";
    const struct public_key pub_key = {526567, 65537};
    const int length = strlen(string);
    int ciphertext[104];
    encrypt(ciphertext, string, pub_key);

    char actual[105];

    const struct private_key priv_key = {526567, 4157};
    decrypt(actual, ciphertext, length, priv_key);

    ck_assert_msg(actual[length] == 0, "Expected null terminator at the end of decrypted message.");
    ck_assert_msg(strncmp(actual, string, length) == 0, "Expected message to be %s, was %s", string, actual);
}
END_TEST

///////////////////////////////////////////////////////////////////////////////////////////////////
/************************************** HELPER FUNCTIONS *****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

static void setup(void)
{
}

static void _encrypt(int *ciphertext, char *plaintext, struct public_key pub_key) {
    int plaintext_len = my_strlen(plaintext);

    for (int i = 0; i < plaintext_len; i++) {
        int val = (int) plaintext[i];

        int cipher_number = power_and_mod(val, pub_key.e, pub_key.n);

        ciphertext[i] = cipher_number;
    }
}

Suite *cryptography_suite(void)
{
    Suite *s = suite_create("cryptography_suite");

    tcase_hack(s, setup, NULL, test_encrypt_1);
    tcase_hack(s, setup, NULL, test_encrypt_2);
    tcase_hack(s, setup, NULL, test_decrypt_1);
    tcase_hack(s, setup, NULL, test_decrypt_2);
    tcase_hack(s, setup, NULL, test_encrypt_and_decrypt);
    

    // Return Testing Suite
    return s;
}
