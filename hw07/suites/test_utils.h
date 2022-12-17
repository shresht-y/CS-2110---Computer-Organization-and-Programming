
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *hw7_suite(void);
extern Suite *my_string_suite(void);
extern Suite *cryptography_suite(void);

#define tcase_hack(suite, setup_fixture, teardown_fixture, func)        \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** hw7 Header Info *********************************/
/******************************************************************************/

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially

// Sizes for different arrays
#define MAX_NAME_LENGTH  10
#define MAX_PASSWORD_LENGTH  10
#define MAX_COMPANY_LENGTH   10
#define MAX_USERS_LENGTH   64

// Success and failure codes for function return
#define SUCCESS 1
#define FAILURE 0

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

// encrypted_user struct
struct encrypted_user {
  int id;
  int name[MAX_NAME_LENGTH];
  int nameLength;
  int password[MAX_PASSWORD_LENGTH];
  int passwordLength;
  double salary;
  int company[MAX_COMPANY_LENGTH];
  int companyLength;
  struct public_key pub_key;
};

// decrypted_user struct
struct decrypted_user {
  int id;
  char name[MAX_NAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  double salary;
  char company[MAX_COMPANY_LENGTH];
  struct public_key pub_key;
};
extern struct decrypted_user users[];
extern int size;

// Function prototypes for my_string.c
size_t my_strlen(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strncat(char *dest, const char *src, size_t n);
void *my_memset(void *str, int c, size_t n);

// Prototype users.c functions
int addUser(int id, const char * name, const char * password, double salary, const char * company, struct public_key pub_key);
int updateUserCompany(struct decrypted_user, const char *);
int swapUsers(int, int);
int removeUser(struct decrypted_user);
void sortUsersByName(void);
int compareName(struct decrypted_user, struct decrypted_user);
double averageSalary(const char *);
int encryptUser(struct encrypted_user *, int index);
int decryptAndAppendUser(struct encrypted_user *, struct private_key private_key);

// Prototype cryptography.c functions
void encrypt(int *ciphertext, char *plaintext, struct public_key pub_key);
void decrypt(char *plaintext, int *ciphertext, int plaintext_length, struct private_key pri_key);
int power_and_mod(int b, int e, int n);

