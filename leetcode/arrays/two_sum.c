// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// You can return the answer in any order.
//
//
//
// Example 1:
//
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Output: Because nums[0] + nums[1] == 9, we return [0, 1].
//
// Example 2:
//
// Input: nums = [3,2,4], target = 6
// Output: [1,2]
//
// Example 3:
//
// Input: nums = [3,3], target = 6
// Output: [0,1]
//
// Constraints:
//
//     2 <= nums.length <= 103
//     -109 <= nums[i] <= 109
//     -109 <= target <= 109
//     Only one valid answer exists.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h> // for malloc

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    *returnSize = 0;
    if (numsSize > 1)
    {
        int *ret_array = malloc(sizeof(int)*2);
        for(int i=0; i<numsSize; i++)
        {
            for (int j=i+1; j<numsSize; j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    *returnSize = 2;
                    ret_array[0] = i;
                    ret_array[1] = j;
                    return ret_array;
                }
            }
        }
    }
    return NULL;
}

#include <stdio.h>

#define NUM_TESTS 4
#define MAX_NUM_VALUES 10
//
//
int testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    {2,7,11,15},
    {3,2,4},
    {3,3},
    {-4},
};

int testtarget[NUM_TESTS] = {
    9,
    6,
    6,
    7,
};

int testnums[NUM_TESTS] = {
    4,
    3,
    2,
    1,
};

int testanswers[NUM_TESTS][3] = { // 0:1 indices, 2 returnSize
    {0,1,2},
    {1,2,2},
    {0,1,2},
    {0,0,0},
};

int main(void)
{
    int status = 0;
    int returnSize = 0;

    int *result;

    for (int i=0; i<NUM_TESTS; i++)
    {
        result = twoSum(testcase[i], testnums[i], testtarget[i], &returnSize);
        printf("Test #%d returnSize: %d", i, returnSize);
        if (returnSize != testanswers[i][2])
        {
            status = -1;
            printf(" Expecting %d", testanswers[i][2]);
        }
        else
        {
            if (returnSize > 1)
            {
                if ((result[0] != testanswers[i][0]) && (result[1] != testanswers[i][1]))
                {
                    status = -1;
                    printf(" Expecting [%d,%d]", testanswers[i][0], testanswers[i][1]);
                }
                free(result);
            }
        }
        printf("\n");
    }

    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}