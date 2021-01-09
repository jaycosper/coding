// Implement strStr().
//
// Return the index of the first occurrence of needle in haystack, or -1 if needle
//  is not part of haystack.
//
// Clarification:
//
// What should we return when needle is an empty string? This is a great question
//  to ask during an interview.
//
// For the purpose of this problem, we will return 0 when needle is an empty string.
//  This is consistent to C's strstr() and Java's indexOf().
//
// Example 1:
//
// Input: haystack = "hello", needle = "ll"
// Output: 2
//
// Example 2:
//
// Input: haystack = "aaaaa", needle = "bba"
// Output: -1
//
// Example 3:
//
// Input: haystack = "", needle = ""
// Output: 0
//
//
//
// Constraints:
//
//     0 <= haystack.length, needle.length <= 5 * 10^4
//     haystack and needle consist of only lower-case English characters.
#include <stdlib.h>
#include <stdbool.h>

int strStr(char * haystack, char * needle)
{
    if (haystack == NULL || needle == NULL)
    {
        return 0;
    }
    if (*haystack == 0)
    {
        if(*needle != 0)
        {
            return -1;
        }
    }
    if(*needle == 0)
    {
        return 0;
    }

    int match_idx = -1;
    int retval = -1;
    bool match = false;

#define OPTION_1
#ifdef OPTION_1
    char *temp_needle = needle;
    char *match_haystack = NULL;
    char *start_haystack = haystack;
    for (int idx=0;*haystack; ++haystack, ++idx)
    {
        // compare values
        if (*haystack == *temp_needle)
        {
            // they match
            if (!match)
            {
                // first match index, save index
                match_idx = idx;
                match_haystack = haystack;
            }
            // set match flag
            match = true;
            // increment needle pointer
            ++temp_needle;
            if (*temp_needle == '\0')
            {
                // end of needle; matched needle
                retval = match_idx;
                break;
            }
        }
        else
        {
            if (*temp_needle == '\0')
            {
                // end of needle; matched needle
                retval = match_idx;
                break;
            }
            else
            {
                // clear match flag
                match = false;
                // clear match index
                match_idx = -1;
                // reset needle pointer
                temp_needle = needle;
                if (match_haystack != NULL)
                {
                    idx = (int)(match_haystack - start_haystack);
                    haystack = match_haystack;
                }
                match_haystack = NULL;
            }
        }
    }
#else // "convolution" method -- exceeded time limit
    // step through haystack
    for (int idx=0;*haystack; ++haystack, ++idx)
    {
        // find needle for each starting point in haystack
        char *curr_haystack = haystack;
        char *curr_needle = needle;
        match = false;
        match_idx = -1;
        for (;*curr_haystack != '\0' && *curr_needle != '\0'; ++curr_haystack, ++curr_needle)
        {
            if (*curr_haystack == *curr_needle)
            {
                if (!match)
                {
                    match_idx = idx;
                }
                match = true;
            }
            else
            {
                break;
            }
        }
        if (*curr_needle == '\0' && match == true)
        {
            // found it! store index
            retval = match_idx;
            break;
        }
    }
#endif

    return retval;
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 11
#define MAX_NUM_VALUES 20

char testcase_haystack[NUM_TESTS][MAX_NUM_VALUES] = {
    "abc",
    "hello",
    "aaaaa",
    "",
    "",
    "a",
    "heol",
    "a",
    "mississippi",
    "aaa",
    "mississippi",
};
char testcase_needle[NUM_TESTS][MAX_NUM_VALUES] = {
    "b",
    "ll",
    "bba",
    "",
    "aa",
    "",
    "ll",
    "a",
    "issip",
    "a",
    "pi",
};

int testanswers[NUM_TESTS] = {
    1,
    2,
    -1,
    0,
    -1,
    0,
    -1,
    0,
    4,
    0,
    9,
};

int main(void)
{
    int status = 0;
    int retval = 0;

    for (int i=0; i<NUM_TESTS; i++)
    {
        retval = strStr(testcase_haystack[i], testcase_needle[i]);
        printf("Test #%d retval: %d", i, retval);
        if (retval != testanswers[i])
        {
            status = -1;
            printf(" Fail Expecting %d", testanswers[i]);
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
