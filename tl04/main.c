/**
 * @file main.c
 * @brief testing and debugging functions written in tl04.c
 * @date 2022-11-xx
 */

// You may add and remove includes as necessary to help facilitate your testing
#include <stdio.h>
#include <stddef.h>
#include "tl04.h"

/** main
 *
 * @brief used for testing and debugging functions written in my_string.c and hw7.c
 *
 * @param void
 * @return 0 on success
 */
int main(void)
{
    printf("Hello, I will be printed when you run %s and %s!\n", "make tl04", "./tl04");

    // Let's test tl04.c
    printf("We can access queue_head and queue_tail as shown in this line, %d\n", queue_head == NULL && queue_tail == NULL);
    struct student_t student;
    student.name = "George";
    int success = queue_add(student);
    printf("Success? %d\n", success);

    printf("Whoops! We forgot to add the last name. Lets do that!\n");
    printf("Original name: %s\n", queue_tail->data.name);
    add_last_name(queue_tail, "Burdell");
    printf("New name: %s\n", queue_tail->data.name);

    printf("We now have to encrypt the student's name.\n");
    char *plainName = queue_tail->data.name;
    printf("Plain name: %s \n", plainName);
    uint8_t *encrypted_name = malloc(strlen(plainName) * sizeof(uint8_t));
    uint8_t xor_key = 75;
    encryptName(encrypted_name, plainName, xor_key);
    printf("Cipher name: ");
    for (unsigned int i = 0; i < strlen(plainName); i++) {
        printf("%d", encrypted_name[i]);
    }
    printf("\n");
    char *decrypted_name = malloc(strlen(plainName) + 1);
    decryptName(decrypted_name, encrypted_name, strlen(plainName), xor_key);
    printf("Decrypted cipher name: %s \n", decrypted_name);
}
