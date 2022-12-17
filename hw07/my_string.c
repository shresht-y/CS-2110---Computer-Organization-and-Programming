/**
 * @file my_string.c
 * @author Shreshta Yadav
 * @collaborators my two brain cells
 * @brief Your implementation of these famous string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2022-10-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "my_string.h"

/**
 * @brief Calculate the length of a string. See PDF for more detailed instructions
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
    int size_t = 0;
    int index = 0;
    char character = *(s + index); //gets the value at the specified index of the string
    while (character != '\0') {
      index++;
      size_t++;
      character = *(s + index);
    }
  return size_t;
}

/**
 * @brief Compare two strings. See PDF for more detailed instructions
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  int differences = 0;
  char string1char = *(s1);
  char string2char = *(s2);

  size_t i = 0;
  while (i <= n) {
    string1char = *(s1 + i);
    string2char = *(s2 + i);
    if (string1char == string2char) {
      if ((string1char == '\0' && string2char == '\0') || i == n) {
        return 0;
      } else {
        i++;
      }
    } else if (string1char - string2char >0) {
      return 1;
    } else if (string1char -string2char < 0) {
      return -1;
    }
  }

  return differences;
}

/**
 * @brief Copy a string. See PDF for more detailed instructions
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
   size_t i = 0;

    while (i < n) {
      if (*(src + i) == '\0') {
        while (i<n) {
          *(dest + i) = '\0';
          i++;
        }
        return dest;
      } else {
        *(dest + i) = *(src + i);
      }
      i++;
    }
  

  return dest;
}

/**
 * @brief Concatenates two strings and stores the result
 * in the destination string. See PDF for more detailed 
 * instructions.
 *
 * @param dest The destination string
 * @param src The source string
 * @param n The maximum number of bytes from src to concatenate
 * @return char* a pointer same as dest
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  size_t i = 0;
  size_t j = 0;

  while (*(dest + i) != '\0') {
    i++;
  }
  while (j < n) {
    if (*(src + j) == '\0') {
      *(dest + i) = '\0';
      return dest;
    }
    *(dest + i + j) = *(src + j);
    j++;
    
  }
  *(dest + i + j) = '\0';


  return dest;
}

/**
 * @brief Copies the character c into the first n
 * bytes of memory starting at *str
 *
 * @param str The pointer to the block of memory to fill
 * @param c The character to fill in memory
 * @param n The number of bytes of memory to fill
 * @return char* a pointer same as str
 */
void *my_memset(void *str, int c, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */


  for (size_t i = 0; i < n; i++) {
    *((char*)str + i) = c;
  }
  return str;
}

