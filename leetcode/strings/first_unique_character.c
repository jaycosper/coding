// Given a string, find the first non-repeating character in it and return its index.
// If it doesn't exist, return -1.
//
// Examples:
//
// s = "leetcode"
// return 0.
//
// s = "loveleetcode"
// return 2.
//
//
//
// Note: You may assume the string contains only lowercase English letters.
#include <stdlib.h> // NULL

#define MAX_LETTERS 26
int firstUniqChar(char * s)
{
    int hashmap[MAX_LETTERS];
        // position of letter,
        // -2 for not found
        // -1 for not unique
    for(int i=0; i<MAX_LETTERS; i++)
    {
        // initialize hashmap
        hashmap[i] = -2;
    }

    int position = -1;

    if (s != NULL)
    {
        int entry;
        for(int pos=0; *s; ++s, ++pos)
        {
            entry = (int)(*s)-0x61; // ASCII 'a' = 0x61;
            if (entry < 0 || entry > (0x61 + MAX_LETTERS))
            {
                // error case - out of bound ASCII character
                return -1;
            }
            if (hashmap[entry] == -2)
            {
                // never seen
                hashmap[entry] = pos;
            }
            else if (hashmap[entry] == -1)
            {
                // not unique
                hashmap[entry] = -1;
            }
            else
            {
                // not unique
                hashmap[entry] = -1;
            }
        }

        // discover first unique
        for(int i=0; i<MAX_LETTERS; i++)
        {
            if (hashmap[i] >=0)
            {
                if (hashmap[i]<position || position == -1)
                {
                    // found earlier unique
                    position = hashmap[i];
                }
            }
        }
    }
    return position;
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 7
#define MAX_NUM_VALUES 15
char testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    "leetcode",
    "loveleetcode",
    "aaaaccdeefffff",
    "helloeh",
    "hannah",
    "abcdeF",
    "aza"
};

int testanswers[NUM_TESTS] = {
    0,
    2,
    6,
    4,
    -1,
    -1,
    1,
};

int main(void)
{
    int status = 0;
    int retval = 0;

    for (int i=0; i<NUM_TESTS; i++)
    {
        retval = firstUniqChar(testcase[i]);
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
