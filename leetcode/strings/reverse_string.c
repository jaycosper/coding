// Write a function that reverses a string. The input string is given as an array of characters char[].
//
// Do not allocate extra space for another array, you must do this by modifying the input array in-place
//  with O(1) extra memory.
//
// You may assume all the characters consist of printable ascii characters.
//
// Example 1:
//
// Input: ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]
//
// Example 2:
//
// Input: ["H","a","n","n","a","h"]
// Output: ["h","a","n","n","a","H"]
//
//    Show Hint #1
// The entire logic for reversing a string is based on using the opposite directional two-pointer approach!

void reverseString(char* s, int sSize)
{
    char temp;
    char* high;
    high = s+(sSize-1);

    for (int i=0; i<sSize/2; i++, s++, high--)
    {
        // swap positions using a temp
        temp = *s;
        *s = *high;
        *high = temp;
    }
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 4
#define MAX_NUM_VALUES 10
char testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    "abcdef",
    "AbCdE",
    "hello",
    "Hannah",
};

int testcasesize[NUM_TESTS] = {
    6,
    5,
    5,
    6,
};

char testanswers[NUM_TESTS][MAX_NUM_VALUES] = {
    "fedcba",
    "EdCbA",
    "olleh",
    "hannaH",
};

int main(void)
{
    int status = 0;
    int returnSize = 0;

    int nums;

    for (int i=0; i<NUM_TESTS; i++)
    {
        nums = testcasesize[i];

        reverseString(testcase[i], nums);
        printf("Test #%d return: %s", i, testcase[i]);
        if (strcmp(testcase[i], testanswers[i]))
        {
            status = -1;
            printf(" Expecting %s", testanswers[i]);
        }
        printf("\n");
    }

    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}
