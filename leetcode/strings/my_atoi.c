// Implement atoi which converts a string to an integer.
//
// The function first discards as many whitespace characters as necessary until the
//  first non-whitespace character is found. Then, starting from this character takes
//  an optional initial plus or minus sign followed by as many numerical digits as
//  possible, and interprets them as a numerical value.
//
// The string can contain additional characters after those that form the integral
//  number, which are ignored and have no effect on the behavior of this function.
//
// If the first sequence of non-whitespace characters in str is not a valid integral
//  number, or if no such sequence exists because either str is empty or it contains
//  only whitespace characters, no conversion is performed.
//
// If no valid conversion could be performed, a zero value is returned.
//
// Note:
//
//     Only the space character ' ' is considered a whitespace character.
//     Assume we are dealing with an environment that could only store integers
//      within the 32-bit signed integer range: [−2^31,  2^31 − 1]. If the numerical
//      value is out of the range of representable values, 2^31 − 1 or −2^31 is returned.
//
//
//
// Example 1:
//
// Input: str = "42"
// Output: 42
//
// Example 2:
//
// Input: str = "   -42"
// Output: -42
// Explanation: The first non-whitespace character is '-', which is the minus sign. Then
//  take as many numerical digits as possible, which gets 42.
//
// Example 3:
//
// Input: str = "4193 with words"
// Output: 4193
// Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
//
// Example 4:
//
// Input: str = "words and 987"
// Output: 0
// Explanation: The first non-whitespace character is 'w', which is not a numerical digit or
//  a +/- sign. Therefore no valid conversion could be performed.
//
// Example 5:
//
// Input: str = "-91283472332"
// Output: -2147483648
// Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
//  Thefore INT_MIN (−2^31) is returned.
//
//
//
// Constraints:
//
//     0 <= s.length <= 200
//     s consists of English letters (lower-case and upper-case), digits, ' ', '+', '-' and '.'.
#include <stdlib.h>

#define MIN_INT -2147483648
#define MAX_INT 2147483647

int myAtoi(char * s)
{
    double retval = 0;
    // null check
    if (s == NULL)
    {
        return retval;
    }
    // ignore beginning whitespace.
    for (; *s == ' '; ++s);

    int sign = 1;
    if (*s == 0x2B)
    {
        // '+'
        // do nothing
        // advance pointer
        ++s;
    }
    else if (*s == 0x2D)
    {
        // '-'
        sign = -1;
        // advance pointer
        ++s;
    }

    double toi;
    for (int i=0; (*s >= 0x30 && *s <= 0x39); ++s, ++i)
    {
        if (i != 0)
        {
            // shift into next position
            retval *= 10;
        }
        // check int, and convert with shift
        // continue until end of string or non-numeric character
        toi = (int)(*s - 0x30);
        retval += toi;
    }
    retval *= sign;
    // check size limits
    if (retval < MIN_INT)
    {
        retval = MIN_INT;
    }
    if (retval > MAX_INT)
    {
        retval = MAX_INT;
    }

    return (int)retval;
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 12
#define MAX_NUM_VALUES 20
char testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    "42",
    "-42",
    " 4193 with words",
    "words and 987",
    "-91283472332",
    "+47",
    "2.03",
    "   4321   ",
    "  abc  def ",
    "",
    "      ",
};

int testanswers[NUM_TESTS] = {
    42,
    -42,
    4193,
    0,
    -2147483648,
    47,
    2,
    4321,
    0,
    0,
    0,
};

int main(void)
{
    int status = 0;
    int retval = 0;

    for (int i=0; i<NUM_TESTS; i++)
    {
        retval = myAtoi(testcase[i]);
        printf("Test #%d retval: %d", i, retval);
        if (retval != testanswers[i])
        {
            status = -1;
            printf(" Expecting %d", testanswers[i]);
        }
        else
        {
            printf(" Pass");
        }
        printf("\n");
    }

    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}
