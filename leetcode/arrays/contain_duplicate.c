// Given an array of integers, find if the array contains any duplicates.
//
// Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.
//
// Example 1:
//
// Input: [1,2,3,1]
// Output: true
//
// Example 2:
//
// Input: [1,2,3,4]
// Output: false
//
// Example 3:
//
// Input: [1,1,1,3,3,4,3,2,4,2]
// Output: true

#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>
bool containsDuplicate(int* nums, int numsSize){

    bool dup = false;
    bool *hash;
    hash = malloc(numsSize);
    for (int i=0; i<numsSize; i++)
    {
        printf("%d\n",*nums);
        if (hash[*nums])
        {
            // duplicate
            return true;
        }
        // set flag for this integer
        hash[*nums]= true;
        // step to next index
        nums++;
    }
    return false;
}

#include <stdio.h>

#define NUM_TESTS 3
#define MAX_NUM_VALUES 10
int testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    {1,2,3,1},
    {1,2,3,4},
    {1,1,1,3,3,4,3,2,4,2},
};

int testnum[NUM_TESTS] = {
    4,
    4,
    10,
};

bool testanswers[NUM_TESTS] = {
    true,
    false,
    true,
};

int main(void)
{
    int status = 0;

    bool result;

    for (int i=0; i<NUM_TESTS; i++)
    {
        result = containsDuplicate(testcase[i], testnum[i]);
        printf("Test #%d array does %scontain duplicate(s)\n", i, (result)?"":"not ");
        if (result != testanswers[i])
        {
            status = -1;
            printf("Expecting %s\n", (testanswers[i] ? "true" : "false"));
        }
    }
    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}