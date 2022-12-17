/**
 * CS 2110 - Fall 2022 - Homework #9
 *
 * @author Shreshta Yadav 
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 1 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static User *create_user(char *name, UserType type, UserUnion data);
static int create_student(int num_classes, double *grades, Student *dataOut); //completed for you
static int create_instructor(double salary, Instructor *dataOut); //completed for you
static Node *create_node(char *name, UserType type, UserUnion data);
static int user_equal(const User *user1, const User *user2);

/** create_user
 *
 * Helper function that creates a User by allocating memory for it on the heap
 * and initializing with the passed in data. You MUST create a deep copy of
 * the data union. This means malloc'ing space for copies of each field in
 * UserUnion data.
 *
 * If malloc returns NULL, you should return NULL as well.
 *
 * If creating a student/instructor fails, you must free everything you've allocated
 * and return NULL
 *
 * You should call create_student() or create_instructor() in this function
 * to create a deep copy of the UserUnion depending on the UserType
 *
 * (hint: you cannot just assign UserUnion data to the data part of user)
 *
 * @param the fields of the User struct
 * @return a User, return NULL if malloc fails
 */
static User *create_user(char *name, UserType type, UserUnion data)
{
    struct user *newUser = (struct user*) malloc(sizeof(struct user));
    if (newUser == NULL) {
        free(newUser);
        return NULL;
    }
    if (name == NULL) {
        newUser->name = NULL;
    } else {  
        newUser->name = (char*) malloc(strlen(name)+1);
        if(!newUser->name) {
            free(newUser->name);
            free(newUser);
            return NULL;
        } else {
            strcpy(newUser->name, name);
        }
    }
    //need to free name and pointer from here onwards
    newUser->type = type;
    if (type == STUDENT) {
        if (create_student(data.student.num_classes, data.student.grades, &(newUser->data.student)) == 1) {
            free(newUser->data.student.grades);
            if (newUser->name == NULL) {
                free(newUser);
                return NULL;
            } else{
                free(newUser->name);
                free(newUser);
                return NULL;
            }
        } else {
            return newUser;
        }
    } else if (type == INSTRUCTOR) {
        create_instructor(data.instructor.salary, &(newUser->data.instructor));
        return newUser;
    } else {
        if (newUser->name == NULL) {
            free(newUser);
            return NULL;
        } else{
            free(newUser->name);
            free(newUser);
            return NULL;
        }
    }
    return NULL;
}

/** create_student
 *
 * Helper function that creates a Student and allocates memory for the grade array on the heap.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU  
 *
 * @param the fields of the Student struct, and an existing pointer to a student
 * @return 1 if malloc fails, 0 otherwise.
 */
static int create_student(int num_classes, double *grades, Student *dataOut)
{
    /***do not change anything in this function***/
    dataOut->num_classes = num_classes;
    dataOut->grades = NULL;
    if (grades != NULL) {
        if (!(dataOut->grades = (double *) malloc(sizeof(double)*num_classes))) return 1;
        memcpy(dataOut->grades, grades, sizeof(double)*num_classes);
    }
    return 0;
}

/** create_instructor
 *
 * Helper function that creates an Instructor.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the Instructor struct, and an existing pointer to an instructor
 * @return 1 if malloc fails, 0 otherwise. (this function should always return 0 since
 * you won't need to malloc anything)
 */
static int create_instructor(double salary, Instructor *dataOut)
{
    /***do not edit anything in this function***/
    dataOut->salary = salary; //yes that's all this function does
    return 0;
}

/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * Remember that you need to malloc both the node itself and the User
  * that's contained in the struct. You might want to call create_user instead of
  * malloc'ing again.
  *
  * If malloc returns NULL for either of them, you should return NULL to indicate failure.
  * In the case that you successfully malloc one of them but fail to malloc the other one,
  * you should free the one you successfully malloc'd.
  *
  * @param the fields of the User struct
  * @return a Node
  */
static Node* create_node(char *name, UserType type, UserUnion data)
{
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    if (newNode == NULL) {
        //free(newNode);
        return NULL;
    }
    newNode->data = create_user(name, type, data);  
    if (newNode->data == NULL) {
        //free(newNode->data);
        free(newNode);
        return NULL;
    }
    newNode->next = NULL;
    return newNode;
    
}

/** student_equal
 *
 * Helper function to compare two Student structs. You may find it ueful to call this helper
 * function from the user_equal function that you have to implement.
 *
 * @param the two Student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const Student *student1, const Student *student2)
{
    if (student1->num_classes != student2->num_classes) return 0;
    if (student1->grades != student2->grades)
    {
        if (student1->grades == NULL || student2->grades == NULL) return 0;
        if (memcmp(student1->grades, student2->grades,
                student1->num_classes * sizeof(double)))
        {
            return 0;
        }
    }
    return 1;
}

/** user_equal
 * Helper function to help you compare two user structs.
 *
 * If the name, type, and union fields are all equal, you should return 1.
 * Otherwise, return 0.
 *
 * NOTE: struct members that are pointers may be null!
 * If two users both have null for a certain pointer, the pointers are
 * considered equal.
 * However, if either of the input users is NULL, you should return 0.
 *
 * You may find it useful to call the student_equal function defined above.
 *
 * Make sure you're using the right function when comparing the name.
 * Remember that you are allowed to use functions from string.h
 *
 * This is meant to be used as a helper function in 'contains'; it is not tested
 * by the autograder.
 *
 * @param the two User structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int user_equal(const User *user1, const User *user2)
{
    if (user1 == NULL || user2 == NULL) {
        return 0;
    }
    if (user1->name == NULL && user2->name == NULL) {
        if (user1->type == STUDENT && user2->type == STUDENT) {
            return student_equal(&(user1->data.student), &(user2->data.student));
        } else if (user1->type == INSTRUCTOR && user2->type == INSTRUCTOR) {
            if (user1->data.instructor.salary == user2->data.instructor.salary) {
                return 1;
            }
        } else {
            return 0;
        }
    } else if (user1->name == NULL || user2->name == NULL) {
        return 0;
    } else if (strcmp(user1->name, user2->name) == 0) {
        if (user1->type == STUDENT && user2->type == STUDENT) {
            return student_equal(&(user1->data.student), &(user2->data.student));
        } else if (user1->type == INSTRUCTOR && user2->type == INSTRUCTOR) {
            if (user1->data.instructor.salary == user2->data.instructor.salary) {
                return 1;
            }
        } else {
            return 0;
        }
    }
    return 0;
}

/** create_list
 *
 * Creates a LinkedList by allocating memory for it on the heap.
 * Be sure to initialize size to zero and head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new struct list or NULL on failure
 */
LinkedList *create_list(void)
{
    struct linked_list *list = (struct linked_list*) malloc(sizeof(struct linked_list));
    if (list == NULL) {
        free(list);
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

/** push_front
 *
 * Adds the element at the front of the LinkedList.
 *
 * @param list a pointer to the LinkedList structure.
 * @param      the fields of the User struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_front(LinkedList *list, char *name, UserType type, UserUnion data)
{
    if (list == NULL) {
        return 1;
    }
    struct node *newNode = create_node(name, type, data);
    if (newNode == NULL) {
        //free(newNode);
        return 1;
    }
    if (list->size == 0) {
        //list = create_list();
        list->head = newNode;
        list->size++;
        return 0;
    } else {
        newNode->next = list->head;
        list->head = newNode;
        list->size++;
        //free(newNode);
        return 0;
    }
    return 0;
}

/** push_back
 *
 * Adds the element to the back of the LinkedList.
 *
 * @param list a pointer to the LinkedList structure.
 * @param      the fields of the User struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_back(LinkedList *list, char *name, UserType type, UserUnion data)
{
    if (list == NULL) {
        return 1;
    }
    struct node *newNode = create_node(name, type, data);
    if (newNode == NULL) {
        free(newNode);
        return 1;
    }
    if (list->size == 0) {
        //list = create_list();
        list->head = newNode;
        list->size++;
        //free(newNode);
        return 0;
    } else {
        struct node *tail = list->head;
        for (int i = 0; i < list->size - 1; i++) {
            tail = tail->next;
        }
        
        tail->next = newNode;
        list->size++;
        //free(tail);
        return 0;
    }
    return 1;
}

/** add_at_index
 *
 * Add the element at the specified index in the LinkedList. This index must lie in
 * the inclusive range [0,size].
 * For example, if you have no elements in the LinkedList,
 * you should be able to add to index 0 but no further.
 * If you have two elements in the LinkedList,
 * you should be able to add to index 2 but no further.
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size]
 * @param the fields of the User struct
 * @return 1 if the index is out of bounds or the LinkedList is NULL or malloc fails
 *         (do not add the data in this case)
 *         otherwise (on success) return 0
 */
int add_at_index(LinkedList *list, int index, char *name, UserType type, UserUnion data)
{
    if (list == NULL || index > list->size || index < 0) {
        return 1;
    }
    struct node *newNode = create_node(name, type, data);
    if (newNode == NULL) {
        free(newNode);
        return 1;
    }
    if (list->size == 0 || index == 0) {
        push_front(list, name, type, data);
        return 0;
    } else {
        struct node *temp = list->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        //free(temp);
        list->size++;
        return 0;
    }
    return 1;
}

/** get
 *
 * Gets the data at the specified index in the LinkedList
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the LinkedList or NULL on failure.
 * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
 *         the LinkedList is NULL, 0 (on success) otherwise
 */
int get(LinkedList *list, int index, User **dataOut)
{
    if (list == NULL || dataOut == NULL || index >= list->size || index < 0) {
        return 1;
    }
    struct node *temp = list->head;
    if (index == 0) {
        User *output = temp->data;
        *dataOut = output;
        return 0;
    }
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    User *output = temp->data;
    *dataOut = output;
    return 0;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We say the list contains some input if there exists some node with
  * equal data as the input.
  *
  * You should use 'user_equal' here to compare the data. Note that pointers are
  * allowed to be null!
  *
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.ghbbb 
  *
  *
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, User *data, User **dataOut)
{
    if (dataOut == NULL) {
        return 0;
    }
    if (list == NULL || data == NULL) {
        *dataOut = NULL;
        return 0;
    }
    struct node *temp = list->head;
    for (int i = 0; i < list->size; i++) {
        if (user_equal(temp->data, data) == 1) {
            User *output = temp->data;
            *dataOut = output;
            return 1;
        }
        temp = temp->next;
    }
    *dataOut = NULL;
    return 0;
}

/** pop_front
  *
  * Removes the Node at the front of the LinkedList, and returns its data to the program user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, User **dataOut)
{
    if (dataOut == NULL) {
        return 1;
    }
    if (list == NULL) { 
        return 1;
    }

    if (list->size == 0) {
        return 1;
    }

    struct node *temp = list->head;
    list->head = temp->next;
    temp->next = NULL;
    
    //User *output = temp->data;
    *dataOut = temp->data;
    //free(output->name);

    free(temp);
    list->size--;
    return 0;
}

/** pop_back
  *
  * Removes the Node at the back of the LinkedList, and returns its data to the program user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, User **dataOut)
{   
    if (dataOut == NULL) {
        return 1;
    }
    if (list == NULL) { 
        return 1;
    }

    if (list->size == 0) {
        return 1;
    }

    if (list->size == 1) {
        struct node *temp = list->head;
        //User *output = temp->data;
        *dataOut = temp->data;
        list->head = NULL;
        list->size--;
        free(temp);
        return 0;
    }
    struct node *tail = list->head;
    for (int i = 0; i < list->size - 2; i++) {
        tail = tail->next;
    }
    struct node *temp = tail->next;
    //User *output = temp->data;
    *dataOut = temp->data;
    //free(output->name);
    //free(output);
    tail->next = NULL;
    list->size--;
    free(temp);
    return 0;
}


/** remove_at_index
 *
 * Remove the element at the specified index in the LinkedList.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to a pointer used to return the data in the last
 *                Node or NULL if the LinkedList is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @return 1 if the index is out of bounds, the LinkedList is NULL or
 *         the dataOut is NULL
 *         otherwise return 0
 */
int remove_at_index(LinkedList *list, User **dataOut, int index)
{
    if (dataOut == NULL) {
        return 1;
    }
    if (list == NULL) { 
        return 1;
    }
    if (list->size == 0) {
        return 1;
    }

    if (index == 0) {
        pop_front(list, dataOut);
        return 0;
    }

    if(index == list->size-1) {
        pop_back(list, dataOut);
        return 0;
    }

    struct node *temp = list->head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
    }

    struct node *next = temp->next;
    *dataOut = next->data;
    //*dataOut = output;
    //free(output->name);
    temp->next = temp->next->next;
    free(next);
    list->size--;
    return 0;
}

/** empty_list
 *
 * Empties the LinkedList. After this is called, the LinkedList should be
 * empty. This does NOT free the LinkedList struct itself, just all nodes and
 * data within. Make sure to check that the list is not NULL before
 * using it.
 *
 * Once again, the things that need to be freed after this function are:
 * - the nodes
 * - the user structs within the nodes
 * - all pointers in the user struct (and the union within)
 *
 * However, if you're using other functions you've written (which you should be),
 * those functions might take care of some of the freeing for you.
 *
 * You may call free on a char pointer as well as a struct pointer.
 *
 * If 'list' is NULL, simply return.
 *
 * @param list a pointer to the LinkedList structure
 */
void empty_list(LinkedList *list)
{   
    if (list == NULL) { 
        return;
    }
    User *temp = NULL;
    User *output = temp;
    
    while (list->size > 0)
    {
        pop_front(list, &output);
        if (output->name != NULL) {
            free(output->name);
        } 
        if (output->type == STUDENT) {
            free(output->data.student.grades);
        }
        free(output);
        free(temp);
    }
    
}

/** num_passing_all_classes
 *
 * Traverses the LinkedList, counting the number of Students that are passing
 * all of their classes. We say a student is passing if their grade is greater
 * than or equal to 60.
 *
 * You should make sure your code only counts students, as instructors cannot be
 * passing or failing a class!
 *
 * If a student is not taking any classes, they are NOT considered to be passing
 * all their classes.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to int used to return the count of students passing all
 *                of their classes
 *                or -1 if the LinkedList is NULL or empty
 * @return 1 if the LinkedList is NULL or empty, else (on success) 0
 */
int num_passing_all_classes(LinkedList *list, int *dataOut)
{
    //int *total = 0;
    *dataOut = 0;
    if (list == NULL) { 
        //*total = -1;
        *dataOut = -1;
        return 1;
    }
    if (list->size == 0) {
        //*total = -1;
        *dataOut = -1;
        return 1;
    }
    int counter = 0;
    struct node *temp = list->head;
    for (int i = 0; i<list->size; i++) {
        if (temp->data->type == STUDENT) {
            if (temp->data->data.student.num_classes > 0) {
                for (int j = 0; j<temp->data->data.student.num_classes; j++) {
                    if (temp->data->data.student.grades[j] >= 60) {
                        counter++;
                    }
                }
                if (counter == temp->data->data.student.num_classes) {
                    *dataOut = *dataOut + 1;
                }
                counter = 0;
            }
        }
        temp = temp->next;
    }
    
    return 0;
}

/** get_average_salary
 *
 * Traverses the LinkedList, computing the average of all instructor salaries.
 *
 * You should make sure your code only looks at instructors, as students do not have salaries!
 *
 * If there are no instructors in the list, place a 0 at dataOut.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to double used to return the average salary of the instructors
 *                or -1 if the LinkedList is NULL or empty
 * @return 1 if the LinkedList is NULL or empty, else (on success) 0
 */
int get_average_salary(LinkedList *list, double *dataOut)
{
    *dataOut = 0;
    if (list == NULL) { 
        //*total = -1;
        *dataOut = -1;
        return 1;
    }
    if (list->size == 0) {
        //*total = -1;
        *dataOut = -1;
        return 1;
    }
    int counter = 0;
    int totalSalary = 0;
    struct node *temp = list->head;
    for (int i = 0; i<list->size; i++) {
        if (temp->data->type == INSTRUCTOR) {
            counter++;
            totalSalary += temp->data->data.instructor.salary;
        }
        temp = temp->next;
    }

    if (counter > 0) {
        *dataOut = totalSalary/counter;
    }
    
    return 0;
}
