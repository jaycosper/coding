// Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
//
// Follow up: Could you implement a solution with a linear runtime complexity and without using extra memory?
//
//
//
// Example 1:
//
// Input: nums = [2,2,1]
// Output: 1
//
// Example 2:
//
// Input: nums = [4,1,2,1,2]
// Output: 4
//
// Example 3:
//
// Input: nums = [1]
// Output: 1
//
//
//
// Constraints:
//
//     1 <= nums.length <= 3 * 10^4
//     -3 * 10^4 <= nums[i] <= 3 * 10^4
//     Each element in the array appears twice except for one element which appears only once.

#include <stdint.h>

int singleNumber(int* nums, int numsSize){
    #define MAX_RANGE 30000
    uint8_t hash[MAX_RANGE][2] = {0}; // 0 = positive, 1 = negative
    if (numsSize > 1)
    {
        for (int i=0; i<numsSize; i++)
        {
            int idx = nums[i];
            int negFlag = 0;
            if (nums[i]<0)
            {
                idx = -idx;
                negFlag = 1;
            }
            hash[idx][negFlag]++;
        }
        // iterate through loop to find single
        for (int i=0; i<MAX_RANGE; i++)
        {
            if (hash[i][0] == 1)
            {
                return i;
            }
            if (hash[i][1] == 1)
            {
                // negative
                return -i;
            }
        }
    }
    else
    {
        return *nums;
    }

    return 0;
}

#include <stdio.h>

#define NUM_TESTS 4
#define MAX_NUM_VALUES 10
int testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    {2,2,1},
    {4,1,2,1,2},
    {1},
    {-4,1,2,-1000,1,2,-4},
};

int testnums[NUM_TESTS] = {
    3,
    5,
    1,
    7,
};

int testanswers[NUM_TESTS] = {
    1,
    4,
    1,
    -1000,
};

int main(void)
{
    int status = 0;

    int result;

    for (int i=0; i<NUM_TESTS; i++)
    {
        result = singleNumber(testcase[i], testnums[i]);
        printf("Test #%d contains single: %d", i, result);
        if (result != testanswers[i])
        {
            status = -1;
            printf(" Expecting %d", testanswers[i]);
        }
        printf("\n");
    }
    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}