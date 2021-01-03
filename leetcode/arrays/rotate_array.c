// Given an array, rotate the array to the right by k steps, where k is non-negative.
//
// Follow up:
//
//     Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
//     Could you do it in-place with O(1) extra space?
//
//
//
// Example 1:
//
// Input: nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
// Explanation:
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]
//
// Example 2:
//
// Input: nums = [-1,-100,3,99], k = 2
// Output: [3,99,-1,-100]
// Explanation:
// rotate 1 steps to the right: [99,-1,-100,3]
// rotate 2 steps to the right: [3,99,-1,-100]
//
//
//
// Constraints:
//
//     1 <= nums.length <= 2 * 104
//     -231 <= nums[i] <= 231 - 1
//     0 <= k <= 105
#define TYPE_1

#ifdef TYPE_0
#include <stdlib.h>
#include <string.h>
void rotate(int* nums, int numsSize, int k){
    // memcopy data to temp location
    // 0:k -> temp
    // numsSize-1;k+1 -> in-place
    // temp -> (k+1-numsSize-1:numsSize-1)
    if (numsSize > 1)
    {
        int *temp;
        int kp = k;
        if (k > numsSize)
        {
            kp = k % numsSize;
        }

        int tempSize = numsSize - kp;
        temp = malloc(tempSize * sizeof(int)); // k=3, tempSize = 4 ints 0:3

        memcpy(temp, nums, sizeof(int) * tempSize); // 1,2,3,4 to temp
        int *temp2 = nums + tempSize;
        memcpy(nums, temp2, sizeof(int) * (numsSize-tempSize)); // num[4:6] to [0:2]
        temp2 = nums + kp;
        memcpy(temp2, temp, sizeof(int) * tempSize); // temp[0:3] to num[3:6]
        free(temp);
    }
}
#endif // TYPE_0

#ifdef TYPE_1
void rotate(int* nums, int numsSize, int k)
{
    // idk
}
#endif // TYPE_1

#include <stdio.h>

#define NUM_TESTS 8
#define MAX_NUM_VALUES 10
int testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    {1,2,3,4,5,6,7},
    {-1,-100,3,99},
    {-1,0,1,2},
    {9,8,7,6,5},
    {0,1,2,3,4},
    {-1},
    {7,8},
    {1,2,3},
};

int testnum[NUM_TESTS] = {
    7,
    4,
    4,
    5,
    5,
    1,
    2,
    3,
};

int testk[NUM_TESTS] = {
    3,
    2,
    4,
    4,
    0,
    2,
    3,
    2,
};

int testanswers[NUM_TESTS][MAX_NUM_VALUES] = {
    {5,6,7,1,2,3,4},
    {3,99,-1,-100},
    {-1,0,1,2},
    {8,7,6,5,9},
    {0,1,2,3,4},
    {-1},
    {8,7},
    {2,3,1},
};

int main(void)
{
    int status = 0;

    for (int i=0; i<NUM_TESTS; i++)
    {
        rotate(testcase[i], testnum[i], testk[i]);
        printf("Test #%d rotate %d\n{", i, testk[i]);
        for (int j=0; j<testnum[i]; j++)
        {
            printf("%d,", testcase[i][j]);
            if (testcase[i][j] != testanswers[i][j])
            {
                status = -1;
                printf("Expecting %d\n", testanswers[i][j]);
            }
        }
        printf("}\n");
    }
    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}