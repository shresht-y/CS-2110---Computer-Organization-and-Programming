/**
 * @file tl4_suite.c
 * @author Justin
 * @brief Testing Suites to TL4 - Fall 2022
 * @date 2022-11-20
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

int malloc_use_pattern = 0;
int malloc_pattern_ind = 0;
int malloc_pattern[10] = {0};

// allow infinite mallocs by default
static void reset_malloc_pattern(void) {
    malloc_use_pattern = 0;
    malloc_pattern_ind = 0;
    memset(malloc_pattern, 0, sizeof(malloc_pattern));
}

static void reset(void) {
    reset_malloc_pattern();
    queue_head = NULL;
    queue_tail = NULL;
}



const char *names[7] = {"Harry", "Ron", "Hermione", "John", "Bo", "Dumbledore", "Leia"};

static void _create_normal_queue(void) {
    struct student_t student1 = _create_temp_student(names[0], TIMED_LAB_4);
    _queue_add(student1);
    struct student_t student2 = _create_temp_student(names[1], HOMEWORK_3);
    _queue_add(student2);
    struct student_t student3 = _create_temp_student(names[2], QUIZ_2);
    _queue_add(student3);
}

static void assert_node_data_equals(struct queue_node_t *node, const char *nodeLabel, const char *origName, enum assignment_t assignment) {
    ck_assert_msg(node != NULL, "expected %s to be non-null, instead was NULL", nodeLabel);
    ck_assert_msg(strcmp(node->data.name, origName) == 0, "expected %s->data.name to be %s, instead was %s", nodeLabel, origName, queue_tail->data.name);
    ck_assert_msg(node->data.name != origName, "expected %s->data.name to be deepcopied, instead was same as passed in name", nodeLabel);
    ck_assert_msg(node->data.assignment == assignment, "expected %s->data.assignment to be %d, instead was %d", nodeLabel, assignment, queue_tail->data.assignment);
}



/* queue_add tests */

START_TEST(test_queue_add_short_name) {
    _create_normal_queue();
    const char *name = names[3];
    enum assignment_t assignment = HOMEWORK_1;
    struct student_t student = _create_temp_student(name, assignment);
    struct queue_node_t *oldTail = queue_tail;
    int success = queue_add(student);

    ck_assert_msg(success == 0, "expected queue_add to return zero on success, instead was %d", success);
    assert_node_data_equals(queue_tail, "queue_tail", name, assignment);
    ck_assert_msg(oldTail->next == queue_tail, "expected oldTail->next to be queue_tail, instead was %p", oldTail->next);
    queue_tail->next = NULL;
    ck_assert_msg(queue_tail->next == NULL, "expected queue_tail->next to be NULL, instead was %p", queue_tail->next);

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_long_name) {
    _create_normal_queue();
    const char *name = names[5];
    enum assignment_t assignment = QUIZ_4;
    struct student_t student = _create_temp_student(name, assignment);
    struct queue_node_t *oldTail = queue_tail;
    int success = queue_add(student);

    ck_assert_msg(success == 0, "expected queue_add to return zero on success, instead was %d", success);
    assert_node_data_equals(queue_tail, "queue_tail", name, assignment);
    ck_assert_msg(oldTail->next == queue_tail, "expected oldTail->next to be queue_tail, instead was %p", oldTail->next);
    queue_tail->next = NULL;
    ck_assert_msg(queue_tail->next == NULL, "expected queue_tail->next to be NULL, instead was %p", queue_tail->next);

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_null_name) {
    _create_normal_queue();
    const char *name = NULL;
    enum assignment_t assignment = TIMED_LAB_1;
    struct student_t student = _create_temp_student(name, assignment);
    struct queue_node_t *oldTail = queue_tail;
    int success = queue_add(student);

    ck_assert_msg(success == 1, "expected queue_add to return 1 with null name, instead was %d", success);
    assert_node_data_equals(queue_head, "queue_head", names[0], TIMED_LAB_4);
    assert_node_data_equals(queue_head->next, "queue_head->next", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next->next, "queue_head->next->next", names[2], QUIZ_2);
    ck_assert_msg(queue_tail == oldTail, "expected queue_tail to remain the same on failure, instead queue_tail changed");
    ck_assert_msg(queue_head->next->next->next == NULL, "expected queue_head->next->next->next to be NULL on failure, instead was non-null");

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_empty_string_name) {
    _create_normal_queue();
    const char *name = "";
    enum assignment_t assignment = HOMEWORK_10;
    struct student_t student = _create_temp_student(name, assignment);
    struct queue_node_t *oldTail = queue_tail;
    int success = queue_add(student);

    ck_assert_msg(success == 1, "expected queue_add to return 1 with empty string name, instead was %d", success);
    assert_node_data_equals(queue_head, "queue_head", names[0], TIMED_LAB_4);
    assert_node_data_equals(queue_head->next, "queue_head->next", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next->next, "queue_head->next->next", names[2], QUIZ_2);
    ck_assert_msg(queue_tail == oldTail, "expected queue_tail to remain the same on failure, instead queue_tail changed");
    ck_assert_msg(queue_head->next->next->next == NULL, "expected queue_head->next->next->next to be NULL on failure, instead was non-null");

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_empty_list) {
    const char *name = names[6];
    enum assignment_t assignment = HOMEWORK_4;
    struct student_t student = _create_temp_student(name, assignment);
    int success = queue_add(student);

    ck_assert_msg(success == 0, "expected queue_add to return zero with empty list, instead was %d", success);
    ck_assert_msg(queue_tail != NULL, "expected queue_tail to be non-null, instead was NULL");
    ck_assert_msg(queue_head != NULL, "expected queue_head to be non-null, instead was NULL");
    ck_assert_msg(queue_head == queue_tail, "expected queue_head to equal queue_tail, instead was %p", queue_head);
    queue_tail->next = NULL;
    assert_node_data_equals(queue_tail, "queue_tail", name, assignment);

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_rest_of_list_unchanged) {
    _create_normal_queue();
    const char *name = names[4];
    enum assignment_t assignment = HOMEWORK_8;
    struct student_t student = _create_temp_student(name, assignment);
    queue_add(student);

    assert_node_data_equals(queue_head, "queue_head", names[0], TIMED_LAB_4);
    assert_node_data_equals(queue_head->next, "queue_head->next", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next->next, "queue_head->next->next", names[2], QUIZ_2);

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_0_mallocs_should_fail) {
    _create_normal_queue();
    const char *name = names[3];
    enum assignment_t assignment = HOMEWORK_10;
    struct student_t student = _create_temp_student(name, assignment);
    malloc_use_pattern = 1;
    struct queue_node_t *oldTail = queue_tail;
    int success = queue_add(student);

    ck_assert_msg(success == 1, "expected queue_add to return 1 when malloc fails, instead was %d", success);
    assert_node_data_equals(queue_head, "queue_head", names[0], TIMED_LAB_4);
    assert_node_data_equals(queue_head->next, "queue_head->next", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next->next, "queue_head->next->next", names[2], QUIZ_2);
    ck_assert_msg(queue_tail == oldTail, "expected queue_tail to remain the same on failure, instead queue_tail changed");
    ck_assert_msg(queue_head->next->next->next == NULL, "expected queue_head->next->next->next to be NULL on failure, instead was non-null");

    _delete_queue();
}
END_TEST

START_TEST(test_queue_add_1_mallocs_no_leaks) {
    _create_normal_queue();
    const char *name = names[3];
    enum assignment_t assignment = HOMEWORK_10;
    struct student_t student = _create_temp_student(name, assignment);
    malloc_use_pattern = 1;
    malloc_pattern[0] = 1;
    queue_add(student);

    malloc_use_pattern = 1;
    malloc_pattern_ind = 0;
    malloc_pattern[0] = 0;
    malloc_pattern[1] = 1;
    queue_add(student);

    _delete_queue();
}
END_TEST


/* queue_remove tests */


START_TEST(test_queue_remove_normal) {
    _create_normal_queue();
    struct queue_node_t *oldTail = queue_tail;

    struct student_t removedStudent;
    int success = queue_remove(&removedStudent);

    ck_assert_msg(success == 0, "expected queue_remove to return zero on success, instead was %d", success);
    ck_assert_msg(removedStudent.assignment == TIMED_LAB_4, "expected data->assignment to be %d, instead was %d", TIMED_LAB_4, removedStudent.assignment);
    ck_assert_msg(strcmp(removedStudent.name, names[0]) == 0, "expected data->name to be %s, instead was %s", names[0], removedStudent.name);
    assert_node_data_equals(queue_head, "queue_head", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next, "queue_head->next", names[2], QUIZ_2);
    ck_assert_msg(queue_head->next->next == NULL, "expected queue_head->next->next to be NULL, instead was %p", queue_head->next->next);
    ck_assert_msg(queue_tail == oldTail, "expected queue_tail to remain the same, instead was %p when it should be %p", queue_tail, oldTail);
    ck_assert_msg(queue_tail == queue_head->next, "expected queue_tail to be queue_head->next, instead was %p when it should be %p", queue_tail, queue_head->next);

    _free_student_name_safe(&removedStudent);
    _delete_queue();
}
END_TEST

START_TEST(test_queue_remove_length_1_list) {
    struct student_t student1 = _create_temp_student(names[0], TIMED_LAB_4);
    _queue_add(student1);

    struct student_t removedStudent;
    int success = queue_remove(&removedStudent);

    ck_assert_msg(success == 0, "expected queue_remove to return zero on success, instead was %d", success);
    ck_assert_msg(removedStudent.assignment == TIMED_LAB_4, "expected data->assignment to be %d, instead was %d", TIMED_LAB_4, removedStudent.assignment);
    ck_assert_msg(strcmp(removedStudent.name, names[0]) == 0, "expected data->name to be %s, instead was %s", names[0], removedStudent.name);
    ck_assert_msg(queue_head == NULL, "expected queue_head to be NULL, instead was %p", queue_head);
    ck_assert_msg(queue_tail == NULL, "expected queue_tail to be NULL, instead was %p", queue_tail);

    _free_student_name_safe(&removedStudent);
    _delete_queue();
}
END_TEST

START_TEST(test_queue_remove_empty_list) {
    struct student_t removedStudent;
    int success = queue_remove(&removedStudent);

    ck_assert_msg(success == 1, "expected queue_remove to return 1 with empty list, instead was %d", success);
    ck_assert_msg(queue_head == NULL, "expected queue_head to be NULL, instead was %p", queue_head);
    ck_assert_msg(queue_tail == NULL, "expected queue_tail to be NULL, instead was %p", queue_tail);
}
END_TEST

START_TEST(test_queue_remove_null_data) {
    _create_normal_queue();
    struct queue_node_t *oldTail = queue_tail;

    int success = queue_remove(NULL);

    ck_assert_msg(success == 1, "expected queue_remove to return 1 with NULL data, instead was %d", success);
    assert_node_data_equals(queue_head, "queue_head", names[0], TIMED_LAB_4);
    assert_node_data_equals(queue_head->next, "queue_head->next", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next->next, "queue_head->next->next", names[2], QUIZ_2);
    ck_assert_msg(queue_head->next->next->next == NULL, "expected queue_head->next->next->next to be NULL, instead was %p", queue_head->next->next);
    ck_assert_msg(queue_tail == oldTail, "expected queue_tail to remain the same, instead was %p when it should be %p", queue_tail, oldTail);
    ck_assert_msg(queue_tail == queue_head->next->next, "expected queue_tail to be queue_head->next->next, instead was %p when it should be %p", queue_tail, queue_head->next);

    _delete_queue();
}
END_TEST

START_TEST(test_encrypt_name1) {
    // int encryptName(int *cipherName, char *plainName, int xor_key)

    uint8_t studentEncrypt[1024];
    uint8_t solutionEncrypt[1024];
    int length = 21;
    char *test = "Wahi isn't a cool kid";
    
    int success = encryptName(studentEncrypt, test, '?');
    _encrypt_name(solutionEncrypt, test, '?');

    ck_assert_msg(success == 0, "expected encryptName to succeed, instead return code was %d", success);
    
    for (int i = 0; i < length; i++) {
        ck_assert_int_eq(studentEncrypt[i], solutionEncrypt[i]);
    }

}
END_TEST

START_TEST(test_encrypt_name_rand) {
    // int encryptName(int *cipherName, char *plainName, int xor_key)
    int random32 = rand() % 100;
    uint8_t random8 = (uint8_t) (random32 + 20);
    uint8_t studentEncrypt[1024];
    uint8_t solutionEncrypt[1024];
    int length = 49;
    char *test = "Never gonna give you up, never gonna let you down";
    
    int success = encryptName(studentEncrypt, test, random8);
    _encrypt_name(solutionEncrypt, test, random8);

    ck_assert_msg(success == 0, "expected encryptName to succeed, instead return code was %d", success);
    
    for (int i = 0; i < length; i++) {
        ck_assert_int_eq(studentEncrypt[i], solutionEncrypt[i]);
    }

}
END_TEST

START_TEST(test_encrypt_name_failure) {
    // int encryptName(int *cipherName, char *plainName, int xor_key)

    uint8_t studentEncrypt[1024];
    char *test = "Never gonna give you up, never gonna let you down";
    
    int failure1 = encryptName(studentEncrypt, NULL, '?');
    ck_assert_msg(failure1 == 1, "expected encryptName to fail, instead return code was %d", failure1);
    int failure2 = encryptName(NULL, test, '?');
    ck_assert_msg(failure2 == 1, "expected encryptName to fail, instead return code was %d", failure2);

}
END_TEST

START_TEST(test_decrypt_name1) {
    // int decryptName(char *plainName, uint8_t *cipherName, int plainNameLength, uint8_t xor_key)

    uint8_t solutionCipher[1024];
    char studentPlaintext[1024];
    int length = 44;
    uint8_t xor_key = '{';
    char *test = "never gonna run around and, desert you {o.o}";
    _encrypt_name(solutionCipher, test, xor_key);
    
    int success = decryptName(studentPlaintext, solutionCipher, length, xor_key);
    

    ck_assert_msg(success == 0, "expected decryptName to succeed, instead return code was %d", success);
    
    for (int i = 0; i < length; i++) {
        ck_assert_int_eq(studentPlaintext[i], test[i]);
    }

}
END_TEST

START_TEST(test_decrypt_rand) {
    // int decryptName(char *plainName, uint8_t *cipherName, int plainNameLength, uint8_t xor_key)

    int random32 = rand() % 100;
    uint8_t random8 = (uint8_t) (random32 + 20);
    uint8_t solutionCipher[1024];
    char studentPlaintext[1024];
    int length = 89;
    uint8_t xor_key = random8;
    char *test = "I think that Wendy's made a bad move when they got rid of the chicken sandwich biggie bag";
    _encrypt_name(solutionCipher, test, xor_key);
    
    int success = decryptName(studentPlaintext, solutionCipher, length, xor_key);
    

    ck_assert_msg(success == 0, "expected decryptName to succeed, instead return code was %d", success);
    
    for (int i = 0; i < length; i++) {
        ck_assert_int_eq(studentPlaintext[i], test[i]);
    }

}
END_TEST

START_TEST(test_decrypt_name_failure) {
    // int decryptName(char *plainName, uint8_t *cipherName, int plainNameLength, uint8_t xor_key)

    uint8_t tempArray[1024];
    int length = 19;
    char *test = "ur favoriate TAs <3";
    
    int failure1 = decryptName(test, NULL, length, 'X');
    int failure2 = decryptName(NULL, tempArray, length, 'X');
    ck_assert_msg(failure1 == 1, "expected decryptName to fail, instead return code was %d", failure1);
    ck_assert_msg(failure2 == 1, "expected decryptName to fail, instead return code was %d", failure2);

}
END_TEST

START_TEST(test_decrypt_and_encrypt_rand) {
    // int decryptName(char *plainName, uint8_t *cipherName, int plainNameLength, uint8_t xor_key)
    // int encryptName(int *cipherName, char *plainName, int xor_key)

    int random32 = rand() % 100;
    uint8_t random8 = (uint8_t) (random32 + 20);
    uint8_t solutionCipher[1024];
    char studentPlaintext[1024];
    int length = 48;
    uint8_t xor_key = random8;
    char *test = "time to REally see how welll you can decryyypytt";

    int success1 = encryptName(solutionCipher, test, xor_key);
    ck_assert_msg(success1 == 0, "expected encryptName to succeed, instead return code was %d", success1);

    int success2 = decryptName(studentPlaintext, solutionCipher, length, xor_key);
    ck_assert_msg(success2 == 0, "expected decryptName to succeed, instead return code was %d", success2);
    
    for (int i = 0; i < length; i++) {
        ck_assert_int_eq(studentPlaintext[i], test[i]);
    }

}
END_TEST

START_TEST(test_add_last_name_short_name) {
    // _create_normal_queue();
    const char *name = "Bob";
    enum assignment_t assignment = HOMEWORK_1;
    struct student_t student = _create_temp_student(name, assignment);
    
    
    _queue_add(student);

    const char *expectedName = "Bob Marley";
    int retVal = add_last_name(queue_head, "Marley");
    ck_assert_msg(retVal == 0, "expected add_last_name to return zero on success, instead was %d", retVal);
    ck_assert_msg(strcmp(queue_head->data.name, expectedName) == 0, "expected names to match, your name was %s", queue_head->data.name);


    _delete_queue();
}
END_TEST

START_TEST(test_add_last_name_0_mallocs_should_fail) {
    _create_normal_queue();
    const char *name = "Johnny";
    enum assignment_t assignment = HOMEWORK_10;
    struct student_t student = _create_temp_student(name, assignment);

    _queue_add(student);
    malloc_use_pattern = 1;
    int success = add_last_name(queue_tail, "Test");
    

    ck_assert_msg(success == 1, "expected add_last_name to return 1 when malloc fails, instead was %d", success);
    assert_node_data_equals(queue_head, "other nodes should be untouched: queue_head", names[0], TIMED_LAB_4);
    assert_node_data_equals(queue_head->next, "other nodes should be untouched: queue_head->next", names[1], HOMEWORK_3);
    assert_node_data_equals(queue_head->next->next, "other nodes should be untouched: queue_head->next->next", names[2], QUIZ_2);
    assert_node_data_equals(queue_head->next->next->next, "Node should keep old name upon failure: queue_head->next->next->next", "Johnny", HOMEWORK_10);

    _delete_queue();
}
END_TEST

START_TEST(test_add_last_name_failures) {
    // _create_normal_queue();
    const char *name = "John";
    enum assignment_t assignment = HOMEWORK_1;
    struct student_t student = _create_temp_student(name, assignment);
    
    
    _queue_add(student);

    int retVal1 = add_last_name(queue_head, NULL);
    ck_assert_msg(retVal1 == 1, "expected add_last_name to return 1 on failure, instead was %d", retVal1);
    ck_assert_msg(strcmp(queue_head->data.name, "John") == 0, "expected name unchanged on failure, your name was %s", queue_head->data.name);

    int retVal2 = add_last_name(queue_head, "");
    ck_assert_msg(retVal2 == 1, "expected add_last_name to return 1 on failure, instead was %d", retVal2);
    ck_assert_msg(strcmp(queue_head->data.name, "John") == 0, "expected name unchanged on failure, your name was %s", queue_head->data.name);

    _delete_queue();
}
END_TEST

START_TEST(test_add_last_name_two_names) {
    // _create_normal_queue();
    const char *name1 = "Adrien";
    const char *name2 = "Alice";
    enum assignment_t assignment = HOMEWORK_1;
    struct student_t student1 = _create_temp_student(name1, assignment);
    struct student_t student2 = _create_temp_student(name2, assignment);
    
    
    _queue_add(student1);
    _queue_add(student2);

    const char *expectedName1 = "Adrien Naren";
    const char *expectedName2 = "Alice Wonderland";
    int retVal1 = add_last_name(queue_head, "Naren");
    int retVal2 = add_last_name(queue_head->next, "Wonderland");
    ck_assert_msg(retVal1 == 0, "expected add_last_name to return zero on success, instead was %d", retVal1);
    ck_assert_msg(retVal2 == 0, "expected add_last_name to return zero on success, instead was %d", retVal2);
    ck_assert_msg(strcmp(queue_head->data.name, expectedName1) == 0, "expected names to match, your name was %s", queue_head->data.name);
    ck_assert_msg(strcmp(queue_head->next->data.name, expectedName2) == 0, "expected names to match, your name was %s", queue_head->next->data.name);


    _delete_queue();
}
END_TEST





Suite *tl4_suite(void)
{
    Suite *s = suite_create("tl4_suite");


    // add_last_name tests
    tcase_singleton(s, reset, NULL, test_add_last_name_short_name);
    tcase_singleton(s, reset, NULL, test_add_last_name_0_mallocs_should_fail);
    tcase_singleton(s, reset, NULL, test_add_last_name_failures);
    tcase_singleton(s, reset, NULL, test_add_last_name_two_names);
    

    // cryptography tests
    tcase_singleton(s, reset, NULL, test_encrypt_name1);
    tcase_singleton(s, reset, NULL, test_encrypt_name_failure);
    tcase_singleton(s, reset, NULL, test_encrypt_name_rand);
    tcase_singleton(s, reset, NULL, test_decrypt_name1);
    tcase_singleton(s, reset, NULL, test_decrypt_rand);
    tcase_singleton(s, reset, NULL, test_decrypt_name_failure);
    tcase_singleton(s, reset, NULL, test_decrypt_and_encrypt_rand);
    
    
    // queue_add tests
    tcase_singleton(s, reset, NULL, test_queue_add_short_name);
    tcase_singleton(s, reset, NULL, test_queue_add_long_name);
    tcase_singleton(s, reset, NULL, test_queue_add_null_name);
    tcase_singleton(s, reset, NULL, test_queue_add_empty_string_name);
    tcase_singleton(s, reset, NULL, test_queue_add_empty_list);
    tcase_singleton(s, reset, NULL, test_queue_add_rest_of_list_unchanged);
    tcase_singleton(s, reset, NULL, test_queue_add_0_mallocs_should_fail);
    tcase_singleton(s, reset, NULL, test_queue_add_1_mallocs_no_leaks);

    // queue_remove tests
    tcase_singleton(s, reset, NULL, test_queue_remove_normal);
    tcase_singleton(s, reset, NULL, test_queue_remove_length_1_list);
    tcase_singleton(s, reset, NULL, test_queue_remove_empty_list);
    tcase_singleton(s, reset, NULL, test_queue_remove_null_data);

    return s;
}
