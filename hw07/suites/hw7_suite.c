/**
 * @file hw7_suite.c
 * @author Alice, Corey, Nick, Udit
 * @brief Testing Suites to HW7 - Summer 2022
 * @date 2022-06-30
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
static void _add_user(int id, const char * name, const char * password, double salary, const char * company, struct public_key pub_key);
static void _encrypt(int *ciphertext, char *plaintext, struct public_key pub_key);

///////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************* TESTS ***********************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/* addUser() tests */
// Test that addUser works when called once (this is the "basic" intro test, easy test case)
START_TEST(test_addUser_single)
{
    // Step 1: the setup() function is called automagically
    // We don't really need to change it, all it does is clear the array, set size=0 and detect illegal #includes

    // Step 2: per-test setup
    // If we want to do anything particular for this test (maybe have some data already in the array, we should add it here)
    // It's fine if we start from an empty array for this test, so nothing needed here either
    // Frequently, we have helper methods to help with setup. Check out the _add_user function; this is
    //   entirely separate from the student's addUser function and is essentially a "working" implementation
    //   (without error handling) that you can use to add test data to the array.

    // Step 3: make the function call we're testing (in this case, addUser)
    const char *company = "gatech";
    const int id = 0;
    const double salary = 6.5;
    const char *name = "Bob";
    const char *password = "123";
    struct public_key pub_key;
    pub_key.n = 3;
    pub_key.e = 4;
    
    int retVal = addUser(id, name, password, salary, company, pub_key);

    // Step 4: Test that the return value is correct
    // If the first parameter is false, then the autograder test case will fail and print the message
    // If the first parameter is true, then it'll just keep going
    ck_assert_msg(retVal == SUCCESS, "Expected return value to be SUCCESS (%d) when inserting into empty users, got %d", SUCCESS, retVal);

    // Step 5: Make sure the internal state is correct
    // This function updates the pokedex, so we should make sure that the correct values were inserted
    // You should also check that the other entries already in the pokedex aren't deleted (there aren't an y in this case)
    // For other functions that don't update the pokedex, you would still want to check that didn't accidentally get changed
    // We don't need to test that the values at nickname and speciesName haven't changed, since they are pointers to const chars
    //printf("\n%s %d %f %s\n", species, id, hungerScale, habitat);
    //printf("%s %d %f %s\n\n", animals[0].species, animals[0].id, animals[0].hungerScale, animals[0].habitat);
    ck_assert_msg(size == 1, "Expected size to be 1 after inserting into empty users, was %d", size);
    ck_assert_msg(strncmp(users[0].company, company, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);
}
END_TEST // if you get weird compiler error messages, you probably forgot the END_TEST

// Now, repeat the process above until the function is fully tested.
// Make sure you test all "regular" cases (if the pokedex is empty, if there are already entries, etc.) as well as
//  also testing the edge cases (if the name is longer than the max length, if the company name is longer than the
//  max length, if both of those are true, etc.)

START_TEST(test_addUser_multiple_1) {
    const char *company1 = "WahiCo";
    const int id1 = 0;
    const double salary1 = 6.5;
    const char *name1 = "Alice";
    const char *password1 = "goodpass";
    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    int retVal1 = addUser(id1, name1, password1, salary1, company1, pub_key1);

    const char *company2 = "Youtube";
    const int id2 = 1;
    const double salary2 = 2.3;
    const char *name2 = "Dayne";
    const char *password2 = "passbad";
    struct public_key pub_key2;
    pub_key2.n = 7;
    pub_key2.e = 3;
    int retVal2 = addUser(id2, name2, password2, salary2, company2, pub_key2);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);

    ck_assert_msg(size == 2, "Expected size to be 2 after inserting into users, was %d", size);

    ck_assert_msg(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0, "User company not set correctly");
    ck_assert_msg(users[0].id == id1, "User ID not set correctly");
    ck_assert_msg(users[0].salary == salary1, "Expected salary to be %f, was %f", salary1, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name1, MAX_NAME_LENGTH) == 0, "User name not set correctly");
    ck_assert_msg(strncmp(users[0].password, password1, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password1, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key1.n, "Expected pub_key.n to be %d, was %d", pub_key1.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key1.e, "Expected pub_key.e to be %d, was %d", pub_key1.e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0, "User company not set correctly");
    ck_assert_msg(users[1].id == id2, "User ID not set correctly");
    ck_assert_msg(users[1].salary == salary2, "Expected salary to be %f, was %f", salary2, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name2, MAX_NAME_LENGTH) == 0, "User name not set correctly");
    ck_assert_msg(strncmp(users[1].password, password2, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password2, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key2.n, "Expected pub_key.n to be %d, was %d", pub_key2.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key2.e, "Expected pub_key.e to be %d, was %d", pub_key2.e, users[1].pub_key.e);
}
END_TEST

START_TEST(test_addUser_multiple_2) {
    for (int i = 0; i < 25; i++) {
        // Deterministically generate users
        char company[10];
        sprintf(company, "company%d", i);
        int id = i;
        double salary = (i*3)/10;
        char name[10];
        sprintf(name, "bob%d", i);
        char password[10];
        sprintf(password, "wahiFit%d", i);
        struct public_key pub_key;
        pub_key.n = i + 2;
        pub_key.e = i + 4;

        int retVal = addUser(id, name, password, salary, company, pub_key);
        ck_assert_int_eq(retVal, SUCCESS);
    }

    ck_assert_int_eq(size, 25);

    // Check the backing array after ALL students have been inserted
    for (int i = 0; i < 25; i++) {
        char company[10];
        sprintf(company, "company%d", i);
        int id = i;
        double salary = (i*3)/10;
        char name[10];
        sprintf(name, "bob%d", i);
        char password[10];
        sprintf(password, "wahiFit%d", i);
        struct public_key pub_key;
        pub_key.n = i + 2;
        pub_key.e = i + 4;

        ck_assert_msg(strncmp(users[i].company, company, MAX_COMPANY_LENGTH) == 0, "User company expected %s but was %s", company, users[i].company);
        ck_assert_msg(users[i].id == id, "User ID expected %d but was %d", id, users[i].id);
        ck_assert_msg(users[i].salary == salary, "Expected salary to be %f, was %f", salary, users[i].salary);
        ck_assert_msg(strncmp(users[i].name, name, MAX_NAME_LENGTH) == 0, "User name not set correctly");
        ck_assert_msg(strncmp(users[i].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[i].password);
        ck_assert_msg(users[i].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[i].pub_key.n);
        ck_assert_msg(users[i].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[i].pub_key.e);

    }
}
END_TEST

//Test checks if null-terminator is inserted correctly
START_TEST(test_addUser_null_terminator) {
    // ensures there will be some data around if they don't properly null terminate
    struct public_key pub_key_temp;
    pub_key_temp.n = 3;
    pub_key_temp.e = 9;
    _add_user(45, "BulbasaurIvysaurVenusaur", "wordyPassword", 4.0, "biggest pokemon ever", pub_key_temp);
    size--;

    const char *company = "Figma";
    int id = 20;
    double salary = 95.7;
    const char *name = "Adrien";
    const char *password = "Go0dGrade";
    struct public_key pub_key;
    pub_key.n = 11;
    pub_key.e = 5;
    
    int retVal = addUser(id, name, password, salary, company, pub_key);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);

    ck_assert_msg(strncmp(users[0].company, company, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);
}
END_TEST

// Test check for truncation
START_TEST(test_addUser_long_company)
{
    const char *company = "Amazo- MicroAppl TwoSigMeta lol"; // This nickname should get truncated appropriately, do not expect failure
    const char* truncatedCompany = "Amazo- Mi";
    int id = 21;
    double salary = 4.5;
    const char *name = "Sophie";
    const char *password = "weeeWooo";
    struct public_key pub_key;
    pub_key.n = 2;
    pub_key.e = 9;
    int retVal = addUser(id, name, password, salary, company, pub_key);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);
    ck_assert_msg(strncmp(users[0].company, truncatedCompany, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", truncatedCompany, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);
}
END_TEST

// maybe add comprehensive test for adding a user with a long company, name, and password
// although this does sort of get tested later maybe possibly? guess I'll keep an eye out TODO

// why are there different lengths for the strings here? TODO
START_TEST(test_addUser_too_many_users) {
    for (int i = 0; i < MAX_USERS_LENGTH; i++) {
        // Deterministically generate students
        char company[7];
        sprintf(company, "%02d", i);
        int id = 18 + i;
        double salary = 20.0 - i / 4.0;
        char name[8];
        sprintf(name, "%02d", i);
        char password[9];
        sprintf(password, "%02d", i);
        struct public_key pub_key;
        pub_key.n = 2*i;
        pub_key.e = 3*i;

        _add_user(id, name, password, salary, company, pub_key);
    }
    struct public_key pub_key_temp;
    pub_key_temp.n = 7;
    pub_key_temp.e = 3;
    // should exceed capacity
    int retVal = addUser(100, "One Mohr", "asdfjkl;", 2.0, "TIME", pub_key_temp);
    ck_assert_int_eq(retVal, FAILURE);

    ck_assert_int_eq(size, MAX_USERS_LENGTH);

    // The students we inserted manually should remain unchanged
    for (int i = 0; i < MAX_USERS_LENGTH; i++) {
        char company[7];
        sprintf(company, "%02d", i);
        int id = 18 + i;
        double salary = 20.0 - i / 4.0;
        char name[8];
        sprintf(name, "%02d", i);
        char password[9];
        sprintf(password, "%02d", i);
        struct public_key pub_key;
        pub_key.n = 2*i;
        pub_key.e = 3*i;

        ck_assert_msg(strncmp(users[i].company, company, MAX_COMPANY_LENGTH) == 0, "User company expected %s but was %s", company, users[i].company);
        ck_assert_msg(users[i].id == id, "User ID expected %d but was %d", id, users[i].id);
        ck_assert_msg(users[i].salary == salary, "Expected salary to be %f, was %f", salary, users[i].salary);
        ck_assert_msg(strncmp(users[i].name, name, MAX_NAME_LENGTH) == 0, "User name not set correctly");
        ck_assert_msg(strncmp(users[i].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[i].password);
        ck_assert_msg(users[i].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[i].pub_key.n);
        ck_assert_msg(users[i].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[i].pub_key.e);
    }
}
END_TEST

START_TEST(test_updateUserCompany_basic) {
    // The only thing that matters is the company
    const char *sp1 = "Kum&Go";
    const char *sp2 = "Cutco";
    const char *sp3 = "Twitter";
    const char *sp4 = "Qwerty";
    int id1 = 20;
    int id2 = 11;
    double salary = 6.8;
    const char *name = "ShawnWahi";
    const char *password = "weeeWooo";
    struct public_key pub_key;
    pub_key.n = 2;
    pub_key.e = 9;

    // Even if the only difference is company, it should work
    _add_user(id1, name, password, salary, sp1, pub_key);
    _add_user(id2, name, password, salary, sp2, pub_key);

    // regular update test
    int retVal1 = updateUserCompany(users[0], sp3);

    // The id is the only part of the struct that actually matters when we're searching
    // Make sure the students aren't checking using the whole struct

    // mess up user[1] besides the ID
    struct decrypted_user search = users[1];
    strcpy(search.company, "Slytherin");
    search.salary -= 2;
    strcpy(search.name, "Slytherin");
    strcpy(search.password, "Slytherin");
    search.pub_key.n--;
    search.pub_key.e--;
    int retVal2 = updateUserCompany(search, sp4);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);
    ck_assert_int_eq(size, 2);

    ck_assert_msg(strncmp(users[0].company, sp3, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", sp3, users[0].company);
    ck_assert_msg(users[0].id == id1, "Expected id to be %d, was %d", id1, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);


    ck_assert_msg(strncmp(users[1].company, sp4, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", sp4, users[1].company);
    ck_assert_msg(users[1].id == id2, "Expected id to be %d, was %d", id2, users[1].id);
    ck_assert_msg(users[1].salary == salary, "Expected salary to be %f, was %f", salary, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[1].name);
    ck_assert_msg(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[1].pub_key.e);
}
END_TEST

START_TEST(test_updateUserCompany_long) {
    const char *company = "Ronald McDonald's"; // This company should get truncated appropriately, do not expect failure
    const char *truncatedCompany = "Ronald Mc";
    const char *oldCompany = "Macca's";
    int id = 18;
    double salary = 3.3;
    const char *name = "Eric";
    const char *password = "secret*";
    struct public_key pub_key;
    pub_key.n = 17;
    pub_key.e = 29;
    _add_user(id, name, password, salary, oldCompany, pub_key);
    int retVal = updateUserCompany(users[0], company);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);

    ck_assert_msg(strncmp(users[0].company, truncatedCompany, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", truncatedCompany, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);

}
END_TEST

START_TEST(test_updateUserCompany_failure) {
    for (int i = 0; i < 15; i++) {
        // Deterministically generate users
        char company[8];
        sprintf(company, "comp%d", i);
        int id = 18 + i;
        double salary = 4.0 - i/10;
        char name[10];
        sprintf(name, "BobNum%d", i);
        char password[10];
        sprintf(password, "wahiFit%d", i);
        struct public_key pub_key;
        pub_key.n = i + 7;
        pub_key.e = i + 4;
        _add_user(id, name, password, salary, company, pub_key);
    }

    ck_assert_int_eq(size, 15);

    const char *company = "Siemens";
    int id = 2;
    double salary = 10.0;
    const char *name = "Udit";
    const char *password = "noNe";


    struct decrypted_user search;
    strcpy(search.company, company);
    search.id = id;
    search.salary = salary;
    strcpy(search.name, name);
    strcpy(search.password, password);
    search.pub_key.n = 79;
    search.pub_key.e = 69;

    int retVal = updateUserCompany(search, "Shnape");

    ck_assert_int_eq(retVal, FAILURE);
}
END_TEST

START_TEST(test_updateUserCompany_empty_array) {
    const char *company = "NASA";
    int id = 20;
    double salary = 3.6;
    const char *name = "Irene";
    const char *password = "bicyLe";
    struct public_key pub_key;
    pub_key.n = 69;
    pub_key.e = 13;
    
    _add_user(id, name, password, salary, company, pub_key);
    size--; // This entry isn't actually in the array!

    int retVal = updateUserCompany(users[0], "MarsCo");

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST

START_TEST(test_swapUser_basic) {
    int index1 = 0;
    int index2 = 2;

    const char *company1 = "Alice";
    const char *company2 = "Nick";
    const char *company3 = "Shawn";
    const char *company4 = "Kevin";
    int id = 1;
    int id2 = 4;
    double salary = 3.3;
    const char *name = "Bulbasaur";
    const char *name2 = "Charmande";
    const char *password = "bicyLe";
    const char *password2 = "unicycle";
    struct public_key pub_key;
    pub_key.n = 69;
    pub_key.e = 13;
    struct public_key pub_key2;
    pub_key2.n = 1;
    pub_key2.e = 2;

    _add_user(id, name, password, salary, company1, pub_key);
    _add_user(id, name, password, salary, company2, pub_key);
    _add_user(id2, name2, password2, salary, company3, pub_key2);
    _add_user(id, name, password, salary, company4, pub_key);

    int retVal = swapUsers(index1, index2);
    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 4);

    //index 1 = index2

    ck_assert_msg(strncmp(users[index1].company, company3, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company3, users[index1].company);
    ck_assert_msg(users[index1].id == id2, "Expected id to be %d, was %d", id2, users[index1].id);
    ck_assert_msg(users[index1].salary == salary, "Expected salary to be %f, was %f", salary, users[index1].salary);
    ck_assert_msg(strncmp(users[index1].name, name2, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name2, users[index1].name);
    ck_assert_msg(strncmp(users[index1].password, password2, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password2, users[index1].password);
    ck_assert_msg(users[index1].pub_key.n == pub_key2.n, "Expected pub_key.n to be %d, was %d", pub_key2.n, users[index1].pub_key.n);
    ck_assert_msg(users[index1].pub_key.e == pub_key2.e, "Expected pub_key.e to be %d, was %d", pub_key2.e, users[index1].pub_key.e);

    //index2 = index1

    ck_assert_msg(strncmp(users[index2].company, company1, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company1, users[index2].company);
    ck_assert_msg(users[index2].id == id, "Expected id to be %d, was %d", id, users[index2].id);
    ck_assert_msg(users[index2].salary == salary, "Expected salary to be %f, was %f", salary, users[index2].salary);
    ck_assert_msg(strncmp(users[index2].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[index2].name);
    ck_assert_msg(strncmp(users[index2].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[index2].password);
    ck_assert_msg(users[index2].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[index2].pub_key.n);
    ck_assert_msg(users[index2].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[index2].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company2, users[1].company);
    ck_assert_msg(users[1].id == id, "Expected id to be %d, was %d", id, users[1].id);
    ck_assert_msg(users[1].salary == salary, "Expected salary to be %f, was %f", salary, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[1].name);
    ck_assert_msg(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[3].company, company4, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company4, users[3].company);
    ck_assert_msg(users[3].id == id, "Expected id to be %d, was %d", id, users[3].id);
    ck_assert_msg(users[3].salary == salary, "Expected salary to be %f, was %f", salary, users[3].salary);
    ck_assert_msg(strncmp(users[3].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[3].name);
    ck_assert_msg(strncmp(users[3].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[3].password);
    ck_assert_msg(users[3].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[3].pub_key.n);
    ck_assert_msg(users[3].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[3].pub_key.e);

}
END_TEST

START_TEST(test_swapUser_same) {
    const char *company1 = "Nick";
    const char *company2 = "Mick";
    const char *company3 = "Tim";
    const char *company4 = "YOLO";
    int id = 2;
    int id2 = 8;
    double salary = 3.3;
    const char *name = "Ivysaur";
    const char *name2 = "Wartortle";
    const char *password = "Sunny";
    const char *password2 = "rainY";
    struct public_key pub_key;
    pub_key.n = 9;
    pub_key.e = 10;
    struct public_key pub_key2;
    pub_key2.n = 11;
    pub_key2.e = 12;

    _add_user(id, name, password, salary, company1, pub_key);
    _add_user(id, name, password, salary, company2, pub_key);
    _add_user(id2, name2, password2, salary, company3, pub_key2);
    _add_user(id, name, password, salary, company4, pub_key);

    int retVal = swapUsers(1, 1);

    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 4);

    ck_assert_msg(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company1, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company2, users[1].company);
    ck_assert_msg(users[1].id == id, "Expected id to be %d, was %d", id, users[1].id);
    ck_assert_msg(users[1].salary == salary, "Expected salary to be %f, was %f", salary, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[1].name);
    ck_assert_msg(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[2].company, company3, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company3, users[2].company);
    ck_assert_msg(users[2].id == id2, "Expected id to be %d, was %d", id2, users[2].id);
    ck_assert_msg(users[2].salary == salary, "Expected salary to be %f, was %f", salary, users[2].salary);
    ck_assert_msg(strncmp(users[2].name, name2, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name2, users[2].name);
    ck_assert_msg(strncmp(users[2].password, password2, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password2, users[2].password);
    ck_assert_msg(users[2].pub_key.n == pub_key2.n, "Expected pub_key.n to be %d, was %d", pub_key2.n, users[2].pub_key.n);
    ck_assert_msg(users[2].pub_key.e == pub_key2.e, "Expected pub_key.e to be %d, was %d", pub_key2.e, users[2].pub_key.e);

    ck_assert_msg(strncmp(users[3].company, company4, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company4, users[3].company);
    ck_assert_msg(users[3].id == id, "Expected id to be %d, was %d", id, users[3].id);
    ck_assert_msg(users[3].salary == salary, "Expected salary to be %f, was %f", salary, users[3].salary);
    ck_assert_msg(strncmp(users[3].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[3].name);
    ck_assert_msg(strncmp(users[3].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[3].password);
    ck_assert_msg(users[3].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[3].pub_key.n);
    ck_assert_msg(users[3].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[3].pub_key.e);

}
END_TEST

START_TEST(test_swapUser_index_out_of_bounds_1) {
    int index1 = -2; //out of bounds
    int index2 = 2;

    const char *company1 = "Luna";
    const char *company2 = "squid";
    const char *company3 = "game";
    const char *company4 = "Nick";
    int id = 7;
    double salary = 3.3;
    const char *name = "Squirtle";

    const char *password = "bicyLe";
    struct public_key pub_key;
    pub_key.n = 3;
    pub_key.e = 1;

    _add_user(id, name, password, salary, company1, pub_key);
    _add_user(id, name, password, salary, company2, pub_key);
    _add_user(id, name, password, salary, company3, pub_key);
    _add_user(id, name, password, salary, company4, pub_key);

    int retVal = swapUsers(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[0].id, id);
    ck_assert(users[0].salary == salary);
    ck_assert(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[0].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[0].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[1].id, id);
    ck_assert(users[1].salary == salary);
    ck_assert(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[1].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[1].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[2].company, company3, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[2].id, id);
    ck_assert(users[2].salary == salary);
    ck_assert(strncmp(users[2].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[2].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[2].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[2].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[3].company, company4, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[3].id, id);
    ck_assert(users[3].salary == salary);
    ck_assert(strncmp(users[3].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[3].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[3].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[3].pub_key.e, pub_key.e);
}
END_TEST

START_TEST(test_swapUser_index_out_of_bounds_2) {
    int index1 = 1;
    int index2 = 5; //out of bounds

    const char *company1 = "sparkey";
    const char *company2 = "fly";
    const char *company3 = "Aang";
    const char *company4 = "naruto";
    int id = 21;
    double salary = 3.3;
    const char *name = "Spearow";
    const char *password = "mcQueen";
    struct public_key pub_key;
    pub_key.n = 3;
    pub_key.e = 1;

    _add_user(id, name, password, salary, company1, pub_key);
    _add_user(id, name, password, salary, company2, pub_key);
    _add_user(id, name, password, salary, company3, pub_key);
    _add_user(id, name, password, salary, company4, pub_key);

    int retVal = swapUsers(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[0].id, id);
    ck_assert(users[0].salary == salary);
    ck_assert(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[0].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[0].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[1].id, id);
    ck_assert(users[1].salary == salary);
    ck_assert(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[1].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[1].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[2].company, company3, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[2].id, id);
    ck_assert(users[2].salary == salary);
    ck_assert(strncmp(users[2].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[2].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[2].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[2].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[3].company, company4, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[3].id, id);
    ck_assert(users[3].salary == salary);
    ck_assert(strncmp(users[3].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[3].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[3].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[3].pub_key.e, pub_key.e);
}
END_TEST

START_TEST(test_swapUser_index_out_of_bounds_3) {
    int index1 = 1;

    const char *company1 = "Pika";
    const char *company2 = "Bill";
    const char *company3 = "Thor";
    const char *company4 = "Art";
    int id = 26;
    double salary = 3.3;
    const char *name = "Raichu";

    const char *password = "fireTruk";
    struct public_key pub_key;
    pub_key.n = 10;
    pub_key.e = 7;

    _add_user(id, name, password, salary, company1, pub_key);
    _add_user(id, name, password, salary, company2, pub_key);
    _add_user(id, name, password, salary, company3, pub_key);
    _add_user(id, name, password, salary, company4, pub_key);

    int index2 = size; //out of bounds

    int retVal = swapUsers(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[0].id, id);
    ck_assert(users[0].salary == salary);
    ck_assert(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[0].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[0].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[1].id, id);
    ck_assert(users[1].salary == salary);
    ck_assert(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[1].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[1].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[2].company, company3, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[2].id, id);
    ck_assert(users[2].salary == salary);
    ck_assert(strncmp(users[2].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[2].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[2].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[2].pub_key.e, pub_key.e);

    ck_assert(strncmp(users[3].company, company4, MAX_COMPANY_LENGTH) == 0);
    ck_assert_int_eq(users[3].id, id);
    ck_assert(users[3].salary == salary);
    ck_assert(strncmp(users[3].name, name, MAX_NAME_LENGTH) == 0);
    ck_assert(strncmp(users[3].password, password, MAX_PASSWORD_LENGTH) == 0);
    ck_assert_int_eq(users[3].pub_key.n, pub_key.n);
    ck_assert_int_eq(users[3].pub_key.e, pub_key.e);
}
END_TEST

// ---------------------------------------------------------
/* removeUser tests */
// ---------------------------------------------------------
START_TEST(test_removeUser_basic_1) {

    const char *company1 = "Sam";
    const char *company2 = "Matt";
    const char *company3 = "Amanda";
    const char *company4 = "Chris";
    int id1 = 28;
    int id2 = 8;
    int id3 = 18;
    int id4 = 6;
    double salary = 20.3;
    const char *name = "Sandslash";
    const char *password = "Ground";
    struct public_key pub_key;
    pub_key.n = 22;
    pub_key.e = 25;

    _add_user(id1, name, password, salary, company1, pub_key);
    _add_user(id2, name, password, salary, company2, pub_key); // element to remove
    _add_user(id3, name, password, salary, company3, pub_key);
    _add_user(id4, name, password, salary, company4, pub_key);

    int retVal = removeUser(users[1]);

    ck_assert_int_eq(size, 3);
    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_msg(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company1, users[0].company);
    ck_assert_msg(users[0].id == id1, "Expected id to be %d, was %d", id1, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company3, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company3, users[1].company);
    ck_assert_msg(users[1].id == id3, "Expected id to be %d, was %d", id3, users[1].id);
    ck_assert_msg(users[1].salary == salary, "Expected salary to be %f, was %f", salary, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[1].name);
    ck_assert_msg(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[2].company, company4, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company4, users[2].company);
    ck_assert_msg(users[2].id == id4, "Expected id to be %d, was %d", id4, users[2].id);
    ck_assert_msg(users[2].salary == salary, "Expected salary to be %f, was %f", salary, users[2].salary);
    ck_assert_msg(strncmp(users[2].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[2].name);
    ck_assert_msg(strncmp(users[2].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[2].password);
    ck_assert_msg(users[2].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[2].pub_key.n);
    ck_assert_msg(users[2].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[2].pub_key.e);

}
END_TEST

START_TEST(test_removeUser_basic_2) {

    const char *company1 = "thia";
    const char *company2 = "gary";
    const char *company3 = "Rock";
    const char *company4 = "Chris";
    int id1 = 2;
    int id2 = 8;
    int id3 = 18;
    int id4 = 6;
    double salary = 13.3;
    const char *name = "Meowth";

    const char *password = "Physic";
    struct public_key pub_key;
    pub_key.n = 54;
    pub_key.e = 2;

    _add_user(id1, name, password, salary, company1, pub_key);
    _add_user(id2, name, password, salary, company2, pub_key); 
    _add_user(id3, name, password, salary, company3, pub_key);
    _add_user(id4, name, password, salary, company4, pub_key); // element to remove

    int retVal = removeUser(users[3]);

    ck_assert_int_eq(size, 3);
    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_msg(strncmp(users[0].company, company1, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company1, users[0].company);
    ck_assert_msg(users[0].id == id1, "Expected id to be %d, was %d", id1, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company2, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company2, users[1].company);
    ck_assert_msg(users[1].id == id2, "Expected id to be %d, was %d", id2, users[1].id);
    ck_assert_msg(users[1].salary == salary, "Expected salary to be %f, was %f", salary, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[1].name);
    ck_assert_msg(strncmp(users[1].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[2].company, company3, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company3, users[2].company);
    ck_assert_msg(users[2].id == id3, "Expected id to be %d, was %d", id3, users[2].id);
    ck_assert_msg(users[2].salary == salary, "Expected salary to be %f, was %f", salary, users[2].salary);
    ck_assert_msg(strncmp(users[2].name, name, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name, users[2].name);
    ck_assert_msg(strncmp(users[2].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[2].password);
    ck_assert_msg(users[2].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[2].pub_key.n);
    ck_assert_msg(users[2].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[2].pub_key.e);

}
END_TEST

START_TEST(test_removeUser_user_does_not_exist) {
    const char *company1 = "Nemul";
    const char *company2 = "Nadir";
    const char *company3 = "Toast";
    const char *company4 = "Char";
    int id = 54;
    double salary = 33.3;
    const char *name = "Psyduck";

    const char *password = "Gangnam";
    struct public_key pub_key;
    pub_key.n = 14;
    pub_key.e = 5;

    _add_user(id, name, password, salary, company1, pub_key);
    _add_user(id, name, password, salary, company2, pub_key); 
    _add_user(id, name, password, salary, company3, pub_key);
    _add_user(id, name, password, salary, company4, pub_key);


    const char *company5 = "Paul";
    int id2 = 60;
    double salary2 = 3.35;
    const char *name2 = "Poliwag";
    const char *password2 = "Swirly";

    struct decrypted_user s;
    strcpy(s.company, company5);
    s.id = id2;
    s.salary = salary2;
    strcpy(s.name, name2);
    strcpy(s.password, password2);
    s.pub_key.n = 1;
    s.pub_key.e = 5;

    int retVal = removeUser(s);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

}
END_TEST

START_TEST(test_removeUser_empty_array) {
    const char *company = "Astro";
    int id = 65;
    double salary = 0.0;
    const char *name = "Alakazam";
    const char *password = "stargaze";
    struct public_key pub_key;
    pub_key.n = 4;
    pub_key.e = 3;

    _add_user(id, name, password, salary, company, pub_key);
    size--; // This entry doesn't actually exist in the array!

    int retVal = removeUser(users[0]);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST

START_TEST(test_compareUser_basic_equal) {
    const char *company = "Jeff'sCo";
    int id = 77;
    double salary1 = 3.38;
    double salary2 = 3.90;
    const char *name1 = "Ponyta";
    const char *name2 = "Ponyta";

    const char *password1 = "stargaze";
    const char *password2 = "firetruck";
    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    struct public_key pub_key2;
    pub_key2.n = 3;
    pub_key2.e = 8;

    // same name
    _add_user(id, name1, password1, salary1, company, pub_key1);
    _add_user(id, name2, password2, salary2, company, pub_key2);


    int retVal = compareName(users[0], users[1]);

    ck_assert_int_eq(retVal, 0);
}
END_TEST

START_TEST(test_compareUser_basic_less_than_1) {
    const char *company1 = "Jeff";
    const char *company2 = "Victor";
    int id = 77;

    double salary1 = 3.38;
    double salary2 = 3.90;
    const char *name1 = "Ponyta";
    const char *name2 = "Raichu";

    const char *password1 = "john";
    const char *password2 = "cena";
    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    struct public_key pub_key2;
    pub_key2.n = 3;
    pub_key2.e = 8;

    // name1 < name2
    _add_user(id, name1, password1, salary1, company1, pub_key1);
    _add_user(id, name2, password2, salary2, company2, pub_key2);


  int retVal = compareName(users[0], users[1]);

  ck_assert_int_lt(retVal, 0);
}
END_TEST

START_TEST(test_compareUser_basic_less_than_2) {
    const char *company1 = "Geo";
    const char *company2 = "Jelly";
    int id1 = 70;
    int id2 = 72;
    double salary1 = 20.88;
    double salary2 = 13.11;
    const char *name1 = "Geodude";
    const char *name2 = "Tentacool";

    const char *password1 = "Wahi's";
    const char *password2 = "Fit(bad)";
    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    struct public_key pub_key2;
    pub_key2.n = 3;
    pub_key2.e = 8;

    // name1 < name2
    _add_user(id1, name1, password1, salary1, company1, pub_key1);
    _add_user(id2, name2, password2, salary2, company2, pub_key2);

  int retVal = compareName(users[0], users[1]);

  ck_assert_int_lt(retVal, 0);
}
END_TEST

START_TEST(test_compareUser_basic_greater_than_1) {
  const char *company1 = "Vic";
  const char *company2 = "Nick";
  int id1 = 80;
  int id2 = 79;
  double salary1 = 14.88;
  double salary2 = 13.11;
  const char *name1 = "Tentacool";
  const char *name2 = "Slowbro";
  const char *password1 = "coolkidz";
    const char *password2 = "123456";
    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    struct public_key pub_key2;
    pub_key2.n = 3;
    pub_key2.e = 8;

    _add_user(id1, name1, password1, salary1, company1, pub_key1);
    _add_user(id2, name2, password2, salary2, company2, pub_key2);

  //name1 > name2

  int retVal = compareName(users[0], users[1]);

  ck_assert_int_gt(retVal, 0);
}
END_TEST

START_TEST(test_compareUser_basic_greater_than_2) {
  const char *company1 = "vic";
  const char *company2 = "plant_boy";
  int id1 = 70;
  int id2 = 71;
  double salary1 = 2.88;
  double salary2 = 3.11;
  const char *name1 = "Victreebel";
  const char *name2 = "Geodude";

  const char *password1 = "aPples";
    const char *password2 = "OranGes";
    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    struct public_key pub_key2;
    pub_key2.n = 3;
    pub_key2.e = 8;

    _add_user(id1, name1, password1, salary1, company1, pub_key1);
    _add_user(id2, name2, password2, salary2, company2, pub_key2);

  int retVal = compareName(users[0], users[1]);

  ck_assert_int_gt(retVal, 0);
}
END_TEST

//********* ADD TESTS FOR SAME name, DIFFERENT Salary ************
/*START_TEST(test_compareUser_same_name1){

const char *company1 = "vic";
  const char *company2 = "plant_boy";
  int id1 = 1;
  int id2 = 71;
  double salary1 = 2.0;
  double salary2 = 3.11;
  const char *name1 = "Earth";
  const char *name2 = "Earth";

  // users[0] < users[1]
  _add_animal(company1, id1, salary1, name1);
  _add_animal(company2, id2, salary2, name2);

  //retVal should be < 0
  int retVal = comparename(users[0], users[1]);

  ck_assert_int_lt(retVal, 0);

}
END_TEST

START_TEST(test_compareUser_same_name2){

const char *company1 = "vic";
  const char *company2 = "plant_boy";
  int id1 = 1;
  int id2 = 71;
  double salary1 = 4.0;
  double salary2 = 3.11;
  const char *name1 = "Earth";
  const char *name2 = "Earth";

  // users[0] > users[1]
  _add_animal(company1, id1, salary1, name1);
  _add_animal(company2, id2, salary2, name2);

  //retVal should be < 0
  int retVal = comparename(users[0], users[1]);

  ck_assert_int_gt(retVal, 0);

}
END_TEST*/

/*
----------------------------------------------------------------------------------------------
------------------------------------- RESUME -------------------------------------------------
----------------------------------------------------------------------------------------------
*/

// -------------------------------
/* sortUser tests */
// --------------------------------
START_TEST(test_sortUser_1) {
    const char *company1 = "Maeve"; // sorted: 1
    const char *company2 = "Dave"; // sorted: 2
    const char *company3 = "Eve"; // sorted: 0
    int id1 = 20;
    int id2 = 23;
    int id3 = 19;
    double salary1 = 2.77;
    double salary2 = 2.94;
    double salary3 = 3.98;
    const char *name1 = "Forest";
    const char *name2 = "Ocean";
    const char *name3 = "Desert";

    const char *password1 = "Red";
    const char *password2 = "Green";
    const char *password3 = "Blue";

    struct public_key pub_key1;
    pub_key1.n = 1;
    pub_key1.e = 2;
    struct public_key pub_key2;
    pub_key2.n = 3;
    pub_key2.e = 8;
    struct public_key pub_key3;
    pub_key3.n = 19;
    pub_key3.e = 4;

    _add_user(id1, name1, password1, salary1, company1, pub_key1);
    _add_user(id2, name2, password2, salary2, company2, pub_key2);
    _add_user(id3, name3, password3, salary3, company3, pub_key3);

    sortUsersByName();

    ck_assert_int_eq(size, 3);

    ck_assert_msg(strncmp(users[0].company, company3, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company3, users[0].company);
    ck_assert_msg(users[0].id == id3, "Expected id to be %d, was %d", id3, users[0].id);
    ck_assert_msg(users[0].salary == salary3, "Expected salary to be %f, was %f", salary3, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name3, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name3, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password3, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password3, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key3.n, "Expected pub_key.n to be %d, was %d", pub_key3.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key3.e, "Expected pub_key.e to be %d, was %d", pub_key3.e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company1, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company1, users[1].company);
    ck_assert_msg(users[1].id == id1, "Expected id to be %d, was %d", id1, users[1].id);
    ck_assert_msg(users[1].salary == salary1, "Expected salary to be %f, was %f", salary1, users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name1, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name1, users[1].name);
    ck_assert_msg(strncmp(users[1].password, password1, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password1, users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key1.n, "Expected pub_key.n to be %d, was %d", pub_key1.n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key1.e, "Expected pub_key.e to be %d, was %d", pub_key1.e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[2].company, company2, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company2, users[2].company);
    ck_assert_msg(users[2].id == id2, "Expected id to be %d, was %d", id2, users[2].id);
    ck_assert_msg(users[2].salary == salary2, "Expected salary to be %f, was %f", salary2, users[2].salary);
    ck_assert_msg(strncmp(users[2].name, name2, MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name2, users[2].name);
    ck_assert_msg(strncmp(users[2].password, password2, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password2, users[2].password);
    ck_assert_msg(users[2].pub_key.n == pub_key2.n, "Expected pub_key.n to be %d, was %d", pub_key2.n, users[2].pub_key.n);
    ck_assert_msg(users[2].pub_key.e == pub_key2.e, "Expected pub_key.e to be %d, was %d", pub_key2.e, users[2].pub_key.e);

}
END_TEST

START_TEST(test_sortUser_2) {
    const char *company[] = {"Neville", "Dean", "Seamus", "Lavender", "Parvati"};
              // sorted: {"Neville", "Lavender", "Dean", "Seamus", "Parvati"}
              //           0         3           1       2         4
    int id[] = {18, 21, 21, 19, 23};
    double salary[] = {1.00, 3.42, 2.99, 3.56, 4.00};
    const char *name[] = {
        "ABC",
        "HIJ",
        "DEF",
        "XYZ",
        "BCD"
    };
    const char *password[] = {
        "Weee",
        "Wooo",
        "eeWe",
        "bonk",
        "jank"
    };
    struct public_key pub_key[] = {
        {.n = 1},
        {.n = 2},
        {.n = 3},
        {.n = 4},
        {.n = 5},
        {.e = 6},
        {.e = 7},
        {.e = 8},
        {.e = 9},
        {.e = 10},

    };

    for (int i = 0; i < 5; i++) {
        _add_user(id[i], name[i], password[i], salary[i], company[i], pub_key[i]);
    }

    sortUsersByName();

    ck_assert_int_eq(size, 5);

    ck_assert_msg(strncmp(users[0].company, company[0], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[0], users[0].company);
    ck_assert_msg(users[0].id == id[0], "Expected id to be %d, was %d", id[0], users[0].id);
    ck_assert_msg(users[0].salary == salary[0], "Expected salary to be %f, was %f", salary[0], users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name[0], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[0], users[0].name);
    ck_assert_msg(strncmp(users[0].password, password[0], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[0], users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key[0].n, "Expected pub_key.n to be %d, was %d", pub_key[0].n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key[0].e, "Expected pub_key.e to be %d, was %d", pub_key[0].e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company[4], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[4], users[1].company);
    ck_assert_msg(users[1].id == id[4], "Expected id to be %d, was %d", id[4], users[1].id);
    ck_assert_msg(users[1].salary == salary[4], "Expected salary to be %f, was %f", salary[4], users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name[4], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[4], users[1].name);
    ck_assert_msg(strncmp(users[1].password, password[4], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[4], users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key[4].n, "Expected pub_key.n to be %d, was %d", pub_key[4].n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key[4].e, "Expected pub_key.e to be %d, was %d", pub_key[4].e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[2].company, company[2], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[2], users[2].company);
    ck_assert_msg(users[2].id == id[2], "Expected id to be %d, was %d", id[2], users[2].id);
    ck_assert_msg(users[2].salary == salary[2], "Expected salary to be %f, was %f", salary[2], users[2].salary);
    ck_assert_msg(strncmp(users[2].name, name[2], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[2], users[2].name);
    ck_assert_msg(strncmp(users[2].password, password[2], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[2], users[2].password);
    ck_assert_msg(users[2].pub_key.n == pub_key[2].n, "Expected pub_key.n to be %d, was %d", pub_key[2].n, users[2].pub_key.n);
    ck_assert_msg(users[2].pub_key.e == pub_key[2].e, "Expected pub_key.e to be %d, was %d", pub_key[2].e, users[2].pub_key.e);

    ck_assert_msg(strncmp(users[3].company, company[1], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[1], users[3].company);
    ck_assert_msg(users[3].id == id[1], "Expected id to be %d, was %d", id[1], users[3].id);
    ck_assert_msg(users[3].salary == salary[1], "Expected salary to be %f, was %f", salary[1], users[3].salary);
    ck_assert_msg(strncmp(users[3].name, name[1], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[1], users[3].name);
    ck_assert_msg(strncmp(users[3].password, password[1], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[1], users[3].password);
    ck_assert_msg(users[3].pub_key.n == pub_key[1].n, "Expected pub_key.n to be %d, was %d", pub_key[1].n, users[3].pub_key.n);
    ck_assert_msg(users[3].pub_key.e == pub_key[1].e, "Expected pub_key.e to be %d, was %d", pub_key[1].e, users[3].pub_key.e);

    ck_assert_msg(strncmp(users[4].company, company[3], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[3], users[4].company);
    ck_assert_msg(users[4].id == id[3], "Expected id to be %d, was %d", id[3], users[4].id);
    ck_assert_msg(users[4].salary == salary[3], "Expected salary to be %f, was %f", salary[3], users[4].salary);
    ck_assert_msg(strncmp(users[4].name, name[3], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[3], users[4].name);
    ck_assert_msg(strncmp(users[4].password, password[3], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[3], users[4].password);
    ck_assert_msg(users[4].pub_key.n == pub_key[3].n, "Expected pub_key.n to be %d, was %d", pub_key[3].n, users[4].pub_key.n);
    ck_assert_msg(users[4].pub_key.e == pub_key[3].e, "Expected pub_key.e to be %d, was %d", pub_key[3].e, users[4].pub_key.e);
  
}
END_TEST

//Same name
//Sort by salary
START_TEST(test_sortUser_3) {
    const char *company[] = {"Draco", "Vincent", "Gregory", "Blaise", "Theodore", "Pansy", "Millicant", "Daphne"};
    //           after removing last two:
    //           sorted: {"Blaise", "Draco", "Theodore", "Gregory", "Pansy", "Vincent"}
    //                     3        0        4           2          5        1
    int id[] = {18, 121, 73, 9, 18, 99, 118, 21};
    // salary below
    double salary[] = {8.00, //0
                           5.42, //3
                           6.99, //2
                           2.56, //4
                           7.50, //1
                           1.00, //5
                           2.3,
                            1.89};
    const char *name[] = {
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
        "Slytheri",
    };

    const char *password[] = {
        "Never",
        "Gonna",
        "Give",
        "You",
        "Up",
        "Nevah",
        "Gunna",
        "Let"
    };
    struct public_key pub_key[] = {
        {.n = 11},
        {.n = 12},
        {.n = 13},
        {.n = 14},
        {.n = 15},
        {.n = 16},
        {.n = 17},
        {.n = 18},
        {.e = 19},
        {.e = 20},
        {.e = 21},
        {.e = 22},
        {.e = 23},
        {.e = 24},
        {.e = 25},
        {.e = 26},

    };


    for (int i = 0; i < 8; i++) {
        _add_user(id[i], name[i], password[i], salary[i], company[i], pub_key[i]);
    }
    size -= 2; // Millicant and Daphne don't exist :(

    sortUsersByName();

    ck_assert_int_eq(size, 6);

    ck_assert_msg(strncmp(users[0].company, company[0], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[0], users[0].company);
    ck_assert_msg(users[0].id == id[0], "Expected id to be %d, was %d", id[0], users[0].id);
    ck_assert_msg(users[0].salary == salary[0], "Expected salary to be %f, was %f", salary[0], users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name[0], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[0], users[0].name);
    ck_assert_msg(strncmp(users[0].password, password[0], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[0], users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key[0].n, "Expected pub_key.n to be %d, was %d", pub_key[0].n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key[0].e, "Expected pub_key.e to be %d, was %d", pub_key[0].e, users[0].pub_key.e);

    ck_assert_msg(strncmp(users[1].company, company[4], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[4], users[1].company);
    ck_assert_msg(users[1].id == id[4], "Expected id to be %d, was %d", id[4], users[1].id);
    ck_assert_msg(users[1].salary == salary[4], "Expected salary to be %f, was %f", salary[4], users[1].salary);
    ck_assert_msg(strncmp(users[1].name, name[4], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[4], users[1].name);
    ck_assert_msg(strncmp(users[1].password, password[4], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[4], users[1].password);
    ck_assert_msg(users[1].pub_key.n == pub_key[4].n, "Expected pub_key.n to be %d, was %d", pub_key[4].n, users[1].pub_key.n);
    ck_assert_msg(users[1].pub_key.e == pub_key[4].e, "Expected pub_key.e to be %d, was %d", pub_key[4].e, users[1].pub_key.e);

    ck_assert_msg(strncmp(users[2].company, company[2], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[2], users[2].company);
    ck_assert_msg(users[2].id == id[2], "Expected id to be %d, was %d", id[2], users[2].id);
    ck_assert_msg(users[2].salary == salary[2], "Expected salary to be %f, was %f", salary[2], users[2].salary);
    ck_assert_msg(strncmp(users[2].name, name[2], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[2], users[2].name);
    ck_assert_msg(strncmp(users[2].password, password[2], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[2], users[2].password);
    ck_assert_msg(users[2].pub_key.n == pub_key[2].n, "Expected pub_key.n to be %d, was %d", pub_key[2].n, users[2].pub_key.n);
    ck_assert_msg(users[2].pub_key.e == pub_key[2].e, "Expected pub_key.e to be %d, was %d", pub_key[2].e, users[2].pub_key.e);


   ck_assert_msg(strncmp(users[3].company, company[1], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[1], users[3].company);
    ck_assert_msg(users[3].id == id[1], "Expected id to be %d, was %d", id[1], users[3].id);
    ck_assert_msg(users[3].salary == salary[1], "Expected salary to be %f, was %f", salary[1], users[3].salary);
    ck_assert_msg(strncmp(users[3].name, name[1], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[1], users[3].name);
    ck_assert_msg(strncmp(users[3].password, password[1], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[1], users[3].password);
    ck_assert_msg(users[3].pub_key.n == pub_key[1].n, "Expected pub_key.n to be %d, was %d", pub_key[1].n, users[3].pub_key.n);
    ck_assert_msg(users[3].pub_key.e == pub_key[1].e, "Expected pub_key.e to be %d, was %d", pub_key[1].e, users[3].pub_key.e);

    
    ck_assert_msg(strncmp(users[4].company, company[3], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[3], users[4].company);
    ck_assert_msg(users[4].id == id[3], "Expected id to be %d, was %d", id[3], users[4].id);
    ck_assert_msg(users[4].salary == salary[3], "Expected salary to be %f, was %f", salary[3], users[4].salary);
    ck_assert_msg(strncmp(users[4].name, name[3], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[3], users[4].name);
    ck_assert_msg(strncmp(users[4].password, password[3], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[3], users[4].password);
    ck_assert_msg(users[4].pub_key.n == pub_key[3].n, "Expected pub_key.n to be %d, was %d", pub_key[3].n, users[4].pub_key.n);
    ck_assert_msg(users[4].pub_key.e == pub_key[3].e, "Expected pub_key.e to be %d, was %d", pub_key[3].e, users[4].pub_key.e);


    ck_assert_msg(strncmp(users[5].company, company[5], MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company[5], users[5].company);
    ck_assert_msg(users[5].id == id[5], "Expected id to be %d, was %d", id[5], users[5].id);
    ck_assert_msg(users[5].salary == salary[5], "Expected salary to be %f, was %f", salary[5], users[5].salary);
    ck_assert_msg(strncmp(users[5].name, name[5], MAX_NAME_LENGTH) == 0, "Expected name name to be %s, was %s", name[5], users[5].name);
    ck_assert_msg(strncmp(users[5].password, password[5], MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password[5], users[5].password);
    ck_assert_msg(users[5].pub_key.n == pub_key[5].n, "Expected pub_key.n to be %d, was %d", pub_key[5].n, users[5].pub_key.n);
    ck_assert_msg(users[5].pub_key.e == pub_key[5].e, "Expected pub_key.e to be %d, was %d", pub_key[5].e, users[5].pub_key.e);

}
END_TEST

// -------------------------------
/* averageSalary tests */
// --------------------------------

START_TEST(test_averagesalary_basic) {

    double avg = 0.0;
    const char *company = "Human";
    const int id = 0;
    const double salary = 7.2;
    const char *name = "Earth";
    const char *password = "wateR";
    struct public_key pub_key;
    pub_key.n = 19;
    pub_key.e = 2;

    for(int i = 0; i < 5; i ++) {
        avg += salary;
        _add_user(id, name, password, salary, company, pub_key);
    }

    avg /= 5;

    ck_assert_int_eq(size, 5);

    //ck_assert_uint_eq(avg, averagesalary(company));
    double temp = averageSalary(company);
    ck_assert_msg(avg == temp, "Average Salary incorrect, your value was: %f", temp);
}
END_TEST

START_TEST(test_averagesalary_no_company) {
    double avg = 0.0;
    const char *company = "Human";
    const int id = 0;
    const double salary = 1.0;
    const char *name = "Earth";
    const char *password = "wateR";
    struct public_key pub_key;
    pub_key.n = 19;
    pub_key.e = 2;

    for(int i = 0; i < 5; i ++) {
        avg += salary;
        _add_user(id, name, password, salary, company, pub_key);
    }


    ck_assert_int_eq(size, 5);

    //ck_assert_uint_eq(0.0, averagesalary("no_company"));
    ck_assert_msg(0.0 == averageSalary("no_company"), "Average salary incorrect");
}
END_TEST

START_TEST(test_averagesalary_many_company) {

    const char *company[] = {"Neville", "Dean", "Seamus", "Lavender", "Parvati"};
              // sorted: {"Neville", "Lavender", "Dean", "Seamus", "Parvati"}
              //           0         3           1       2         4
    int id[] = {18, 21, 21, 19, 23};
    double salary[] = {1.00, 3.42, 2.99, 3.56, 4.00};
    const char *name[] = {
        "ABC",
        "HIJ",
        "DEF",
        "XYZ",
        "BCD"
    };

    const char *password[] = {
        "Weee",
        "Wooo",
        "eeWe",
        "bonk",
        "jank"
    };
    struct public_key pub_key[] = {
        {.n = 1},
        {.n = 2},
        {.n = 3},
        {.n = 4},
        {.n = 5},
        {.e = 6},
        {.e = 7},
        {.e = 8},
        {.e = 9},
        {.e = 10},

    };


    for (int i = 0; i < 5; i++) {
        _add_user(id[i], name[i], password[i], salary[i], company[i], pub_key[i]);
    }

    ck_assert_int_eq(size, 5);

    //ck_assert_uint_eq(salary[1], averagesalary(company[1]));
    ck_assert_msg(salary[1] == averageSalary(company[1]), "Average salary incorrect");

}
END_TEST

// -------------------------------
/* encryptUser tests */
// --------------------------------
START_TEST(test_encryptUser_basic) {
    const char *company = "WahiNotes";
    const int id = 0;
    const double salary = 6.5;
    const char *name = "Sheeeeesh";
    const char *password = "HMMMMMMMM";
    struct public_key pub_key;
    pub_key.n = 1333;
    pub_key.e = 97;
    _add_user(id, name, password, salary, company, pub_key);

    struct encrypted_user e_user;

    int retVal = encryptUser(&e_user, 0);
    int e_name[10];
    int e_password[10];
    int e_company[10];
    _encrypt(e_name, (char *) name, pub_key);
    _encrypt(e_password, (char *) password, pub_key);
    _encrypt(e_company, (char *) company, pub_key);

    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 1);
    ck_assert_msg(e_user.nameLength == 9, "Expected name length to be %d, was %d", 9, e_user.nameLength);
    ck_assert_msg(e_user.passwordLength == 9, "Expected name length to be %d, was %d", 9, e_user.passwordLength);
    ck_assert_msg(e_user.companyLength == 9, "Expected name length to be %d, was %d", 9, e_user.companyLength);

    for (int i = 0; i < (int) strlen(name); i++) {
        ck_assert_int_eq(e_user.name[i], e_name[i]);
        ck_assert_int_eq(e_user.password[i], e_password[i]);
        ck_assert_int_eq(e_user.company[i], e_company[i]);
    }
    ck_assert_msg(e_user.id == id, "Expected id to remain unchanged.");
    ck_assert_msg(e_user.salary == salary, "Expected salary to remain unchanged.");
    ck_assert_msg(e_user.pub_key.n == pub_key.n && e_user.pub_key.e == pub_key.e, "Expected public key to remain unchanged.");

}
END_TEST

START_TEST(test_encryptUser_multiple) {
    const char *company1 = "WookieHut";
    const int id1 = 0;
    const double salary1 = 4.2;
    const char *name1 = "Chewbacca";
    const char *password1 = "AAAHHHHHH";
    struct public_key pub_key1;
    pub_key1.n = 1333;
    pub_key1.e = 97;
    _add_user(id1, name1, password1, salary1, company1, pub_key1);

    const char *company2 = "DELIVERBL";
    const int id2 = 1;
    const double salary2 = 12.6;
    const char *name2 = "Ava Naren";
    const char *password2 = "MeetAt209";
    struct public_key pub_key2;
    pub_key2.n = 526567;
    pub_key2.e = 65537;
    _add_user(id2, name2, password2, salary2, company2, pub_key2);

    struct encrypted_user e_user1;
    struct encrypted_user e_user2;

    int retVal1 = encryptUser(&e_user1, 0);
    int e_name1[10];
    int e_password1[10];
    int e_company1[10];
    _encrypt(e_name1, (char *) name1, pub_key1);
    _encrypt(e_password1, (char *) password1, pub_key1);
    _encrypt(e_company1, (char *) company1, pub_key1);

    int retVal2 = encryptUser(&e_user2, 1);
    int e_name2[10];
    int e_password2[10];
    int e_company2[10];
    _encrypt(e_name2, (char *) name2, pub_key2);
    _encrypt(e_password2, (char *) password2, pub_key2);
    _encrypt(e_company2, (char *) company2, pub_key2);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);
    ck_assert_int_eq(size, 2);
    ck_assert_msg(e_user1.nameLength == 9, "Expected name length to be %d, was %d", 9, e_user1.nameLength);
    ck_assert_msg(e_user1.passwordLength == 9, "Expected name length to be %d, was %d", 9, e_user1.passwordLength);
    ck_assert_msg(e_user1.companyLength == 9, "Expected name length to be %d, was %d", 9, e_user1.companyLength);

    for (int i = 0; i < (int) strlen(name1); i++) {
        ck_assert_int_eq(e_user1.name[i], e_name1[i]);
        ck_assert_int_eq(e_user1.password[i], e_password1[i]);
        ck_assert_int_eq(e_user1.company[i], e_company1[i]);
    }
    ck_assert_msg(e_user1.id == id1, "Expected id to remain unchanged.");
    ck_assert_msg(e_user1.salary == salary1, "Expected salary to remain unchanged.");
    ck_assert_msg(e_user1.pub_key.n == pub_key1.n && e_user1.pub_key.e == pub_key1.e, "Expected public key to remain unchanged.");

    ck_assert_msg(e_user2.nameLength == 9, "Expected name length to be %d, was %d", 9, e_user1.nameLength);
    ck_assert_msg(e_user2.passwordLength == 9, "Expected name length to be %d, was %d", 9, e_user1.passwordLength);
    ck_assert_msg(e_user2.companyLength == 9, "Expected name length to be %d, was %d", 9, e_user1.companyLength);

    for (int i = 0; i < (int) strlen(name2); i++) {
        ck_assert_int_eq(e_user2.name[i], e_name2[i]);
        ck_assert_int_eq(e_user2.password[i], e_password2[i]);
        ck_assert_int_eq(e_user2.company[i], e_company2[i]);
    }
    ck_assert_msg(e_user2.id == id2, "Expected id to remain unchanged.");
    ck_assert_msg(e_user2.salary == salary2, "Expected salary to remain unchanged.");
    ck_assert_msg(e_user2.pub_key.n == pub_key2.n && e_user2.pub_key.e == pub_key2.e, "Expected public key to remain unchanged.");


}
END_TEST

START_TEST(test_encryptUser_failure) {
    struct encrypted_user e_user;

    int retVal = encryptUser(&e_user, 0);

    ck_assert_int_eq(retVal, FAILURE);


    const char *company = "Peanutty!";
    const int id = 0;
    const double salary = 6.5;
    const char *name = "WickyTick";
    const char *password = "FoodsFood";
    struct public_key pub_key;
    pub_key.n = 1333;
    pub_key.e = 97;
    _add_user(id, name, password, salary, company, pub_key);

    retVal = encryptUser(&e_user, 1);
    ck_assert_int_eq(retVal, FAILURE);

    retVal = encryptUser(&e_user, -1);
    ck_assert_int_eq(retVal, FAILURE);

    ck_assert_msg(size == 1, "Expected size to be 1, was %d", size);
    ck_assert_msg(strncmp(users[0].company, company, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);

}
END_TEST

// -------------------------------
/* decryptAndAppendUser tests */
// --------------------------------

START_TEST(test_decryptUser_basic) {
    const char *company = "Bharanchy";
    const int id = 0;
    const double salary = 8.6;
    const char *name = "BradGoyal";
    const char *password = "DressinUp";
    struct public_key pub_key;
    pub_key.n = 1333;
    pub_key.e = 97;

    struct encrypted_user e_user;
    e_user.id = id;
    _encrypt(e_user.name, (char *) name, pub_key);
    e_user.nameLength = strlen(name);
    _encrypt(e_user.password, (char *) password, pub_key);
    e_user.passwordLength = strlen(password);
    e_user.salary = salary;
    _encrypt(e_user.company, (char *) company, pub_key);
    e_user.companyLength = strlen(company);
    e_user.pub_key = pub_key;
    struct private_key priv_key = {1333, 13};

    int retVal = decryptAndAppendUser(&e_user, priv_key);
    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_msg(size == 1, "Expected size to be 1, was %d", size);
    ck_assert_msg(strncmp(users[0].company, company, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);
}
END_TEST

START_TEST(test_decryptUser_multiple) {
    struct public_key pub_key0 = {1333, 97};
    struct public_key pub_key1 = {143, 23};
    struct public_key pub_key2 = {526567, 65537};
    struct public_key pub_key[] = {pub_key0, pub_key1, pub_key2};

    struct private_key priv_key0 = {1333, 13};
    struct private_key priv_key1 = {143, 47};
    struct private_key priv_key2 = {526567, 4157};
    struct private_key priv_key[] = {priv_key0, priv_key1, priv_key2};

    const char *company = "Pigeon :)";
    const int id = 0;
    const double salary = 8.6;
    const char *name = "SmallBirb";
    const char *password = "qwertyuio";

    for (int i = 0; i < 3; i++) {
        struct encrypted_user e_user;
        e_user.id = id;
        _encrypt(e_user.name, (char *) name, pub_key[i]);
        e_user.nameLength = strlen(name);
        _encrypt(e_user.password, (char *) password, pub_key[i]);
        e_user.passwordLength = strlen(password);
        e_user.salary = salary;
        _encrypt(e_user.company, (char *) company, pub_key[i]);
        e_user.companyLength = strlen(company);
        e_user.pub_key = pub_key[i];
        
        int retVal = decryptAndAppendUser(&e_user, priv_key[i]);
        ck_assert_int_eq(retVal, SUCCESS);
        ck_assert_msg(size == i + 1, "Expected size to be 1, was %d", size);
    }
    
    for (int i = 0; i < 3; i++) {
        ck_assert_msg(strncmp(users[i].company, company, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company, users[i].company);
        ck_assert_msg(users[i].id == id, "Expected id to be %d, was %d", id, users[i].id);
        ck_assert_msg(users[i].salary == salary, "Expected salary to be %f, was %f", salary, users[i].salary);
        ck_assert_msg(strncmp(users[i].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[i].name);
        ck_assert_msg(strncmp(users[i].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[i].password);
        ck_assert_msg(users[i].pub_key.n == pub_key[i].n, "Expected pub_key.n to be %d, was %d", pub_key[i].n, users[i].pub_key.n);
        ck_assert_msg(users[i].pub_key.e == pub_key[i].e, "Expected pub_key.e to be %d, was %d", pub_key[i].e, users[i].pub_key.e);
    }
    
}
END_TEST

START_TEST(test_decryptUser_failure) {
    struct private_key p = {13, 5};
    int retVal = decryptAndAppendUser(0, p);

    ck_assert_int_eq(retVal, FAILURE);

    const char *company = "Wooohoooo";
    const int id = 0;
    const double salary = 8.6;
    const char *name = "BurgerKid";
    const char *password = "UhhhOHHHH";
    struct public_key pub_key;
    pub_key.n = 1333;
    pub_key.e = 97;
    _add_user(id, name, password, salary, company, pub_key);

    struct encrypted_user e_user;
    e_user.id = id;
    _encrypt(e_user.name, (char *) name, pub_key);
    e_user.nameLength = strlen(name);
    _encrypt(e_user.password, (char *) password, pub_key);
    e_user.passwordLength = strlen(password);
    e_user.salary = salary;
    _encrypt(e_user.company, (char *) company, pub_key);
    e_user.companyLength = strlen(company);
    e_user.pub_key = pub_key;
    struct private_key priv_key = {1333, -13};

    retVal = decryptAndAppendUser(&e_user, priv_key);
    ck_assert_int_eq(retVal, FAILURE);

    ck_assert_msg(size == 1, "Expected size to be 1, was %d", size);
    ck_assert_msg(strncmp(users[0].company, company, MAX_COMPANY_LENGTH) == 0, "Expected company to be %s, was %s", company, users[0].company);
    ck_assert_msg(users[0].id == id, "Expected id to be %d, was %d", id, users[0].id);
    ck_assert_msg(users[0].salary == salary, "Expected salary to be %f, was %f", salary, users[0].salary);
    ck_assert_msg(strncmp(users[0].name, name, MAX_NAME_LENGTH) == 0, "Expected name to be %s, was %s", name, users[0].name);
    ck_assert_msg(strncmp(users[0].password, password, MAX_PASSWORD_LENGTH) == 0, "Expected password to be %s, was %s", password, users[0].password);
    ck_assert_msg(users[0].pub_key.n == pub_key.n, "Expected pub_key.n to be %d, was %d", pub_key.n, users[0].pub_key.n);
    ck_assert_msg(users[0].pub_key.e == pub_key.e, "Expected pub_key.e to be %d, was %d", pub_key.e, users[0].pub_key.e);
}
END_TEST
///////////////////////////////////////////////////////////////////////////////////////////////////
/************************************** HELPER FUNCTIONS *****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Wipe out the array - since they are globals, it is reasonable for students to expect the array to be zeroed and size to be 0 before each test
 * Also try to detect any funky stuff going on with including <string(s).h>
 */
static void setup(void)
{
    memset(users, 0, sizeof(struct decrypted_user) * MAX_USERS_LENGTH);
    size = 0;
}


static void _add_user(int id, const char * name, const char * password, double salary, const char * company, struct public_key pub_key) {
    // the strlens here were the my_strlen, do we want to keep this? TODO
    strncpy(users[size].name, name, strlen(name) + 1);
    strncpy(users[size].password, password, strlen(password) + 1);
    strncpy(users[size].company, company, strlen(company) + 1);
    users[size].id = id;
    users[size].salary = salary;
    users[size].pub_key = pub_key;
    size++;
}

static void _encrypt(int *ciphertext, char *plaintext, struct public_key pub_key) {
    int plaintext_len = my_strlen(plaintext);

    for (int i = 0; i < plaintext_len; i++) {
        int val = (int) plaintext[i];

        int cipher_number = power_and_mod(val, pub_key.e, pub_key.n);

        ciphertext[i] = cipher_number;
    }
}

Suite *hw7_suite(void)
{
    Suite *s = suite_create("hw7_suite");

    // USER ADDS
    tcase_hack(s, setup, NULL, test_addUser_single);
    tcase_hack(s, setup, NULL, test_addUser_multiple_1);
    tcase_hack(s, setup, NULL, test_addUser_multiple_2);
    tcase_hack(s, setup, NULL, test_addUser_null_terminator);
    tcase_hack(s, setup, NULL, test_addUser_long_company);
    tcase_hack(s, setup, NULL, test_addUser_too_many_users);

    // COMPANY TESTS
    tcase_hack(s, setup, NULL, test_updateUserCompany_basic);
    tcase_hack(s, setup, NULL, test_updateUserCompany_long);
    tcase_hack(s, setup, NULL, test_updateUserCompany_failure);
    tcase_hack(s, setup, NULL, test_updateUserCompany_empty_array);

    // SWAP
    tcase_hack(s, setup, NULL, test_swapUser_basic);
    tcase_hack(s, setup, NULL, test_swapUser_same);
    tcase_hack(s, setup, NULL, test_swapUser_index_out_of_bounds_1);
    tcase_hack(s, setup, NULL, test_swapUser_index_out_of_bounds_2);
    tcase_hack(s, setup, NULL, test_swapUser_index_out_of_bounds_3);

    // REMOVE
    tcase_hack(s, setup, NULL, test_removeUser_basic_1);
    tcase_hack(s, setup, NULL, test_removeUser_basic_2);
    tcase_hack(s, setup, NULL, test_removeUser_user_does_not_exist);
    tcase_hack(s, setup, NULL, test_removeUser_empty_array);
    
    // COMPARE
    tcase_hack(s, setup, NULL, test_compareUser_basic_equal);
    tcase_hack(s, setup, NULL, test_compareUser_basic_less_than_1);
    tcase_hack(s, setup, NULL, test_compareUser_basic_less_than_2);
    tcase_hack(s, setup, NULL, test_compareUser_basic_greater_than_1);
    tcase_hack(s, setup, NULL, test_compareUser_basic_greater_than_2);
    
    // SORT
    tcase_hack(s, setup, NULL, test_sortUser_1);
    tcase_hack(s, setup, NULL, test_sortUser_2);
    tcase_hack(s, setup, NULL, test_sortUser_3);

    // SALARY
    tcase_hack(s, setup, NULL, test_averagesalary_basic);
    tcase_hack(s, setup, NULL, test_averagesalary_no_company);
    tcase_hack(s, setup, NULL, test_averagesalary_many_company);

    // ENCRYPT
    tcase_hack(s, setup, NULL, test_encryptUser_basic);
    tcase_hack(s, setup, NULL, test_encryptUser_multiple);
    tcase_hack(s, setup, NULL, test_encryptUser_failure);
    
    // DECRYPT
    tcase_hack(s, setup, NULL, test_decryptUser_basic);
    tcase_hack(s, setup, NULL, test_decryptUser_multiple);
    tcase_hack(s, setup, NULL, test_decryptUser_failure);

    // Return Testing Suite
    return s;
}
