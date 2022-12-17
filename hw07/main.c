/**
 * @file main.c
 * @author YOUR NAME HERE
 * @brief testing and debugging functions written in my_string.c, users.c, cryptography.c
 * @date 2022-10-xx
 */

// You may add and remove includes as necessary to help facilitate your testing
#include <stdio.h>
#include "users.h"
#include "my_string.h"

// Some valid public and private key to use for testing
struct public_key test_pub_key = {
    143, 23
};

struct private_key test_private_key = {
    143, 47
};

/** main
 *
 * @brief used for testing and debugging functions written in my_string.c, cryptography.c, and users.c
 *
 * @param void
 * @return 0 on success
 */
int main(void)
{
    printf("Hello, I will be printed when you run %s and %s!\n", "make hw7", "./hw7");

    // Let's test my_string.c
    const char *s = "I'm a string literal";
    int s_len = my_strlen(s); // just implicitly convert size_t to int so I can use %d
    printf("Len is %d\n", s_len);

    // testing users.c
    printf("size %d\n", size); // size is defined as extern in users.h
    const char *name = "George";
    int id = 66;
    double salary = 1.5;
    const char *password = "pass123";
    const char *company = "CoC";
    int success = addUser(id, name, password, salary, company, test_pub_key);
    // I could put this below line in a for loop to print every single user
    printf("success adding? %d, new size: %d, name: %s, id: %d, salary: %f, password: %s, company: %s \n", success, size, users[0].name, users[0].id, users[0].salary, users[0].password, users[0].company);
}
