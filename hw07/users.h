// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global macros, structures and fields to be used by the
 * users program.
 */
#ifndef USERS_H
#define USERS_H

#include "cryptography.h"
#include "my_string.h"
#include <stddef.h>

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

#endif
