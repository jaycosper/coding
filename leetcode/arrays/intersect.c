// Given two arrays, write a function to compute their intersection.
//
// Example 1:
//
// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2,2]
//
// Example 2:
//
// Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [4,9]
//
// Note:
//
//     Each element in the result should appear as many times as it shows in both arrays.
//     The result can be in any order.
//
// Follow up:
//
//     What if the given array is already sorted? How would you optimize your algorithm?
//     What if nums1's size is small compared to nums2's size? Which algorithm is better?
//     What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h> // for malloc

// simple in-place bubble sort
void bubbleSort(int *array, int arraySize)
{
    int temp;
    // Array Sorting - Ascending Order
    for (int i = 0; i < arraySize; ++i)
    {
        for (int j = i + 1; j < arraySize; ++j)
        {
            // if i value greater than j
            if (array[i] > array[j])
            {
                // swap positions using temp variable
                temp =  array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){

    // maximum return array size can only ever be the same size as the SMALLEST passed array
    int max_ret_size = ((nums2Size > nums1Size) ? nums1Size : nums2Size);

    // allocate memory for return
    int *ret_array = malloc(sizeof(int)*max_ret_size);

    // indices
    int i = 0, j = 0, n = 0;

    bubbleSort(nums1, nums1Size);
    bubbleSort(nums2, nums2Size);
    // this algorithm assumes sorted arrays
    while (i < nums1Size && j < nums2Size)
    {
        // interate through both arrays and compare
        if (nums1[i] > nums2[j])
        {
            j++;
        }

        else
        if (nums2[j] > nums1[i])
        {
            i++;
        }
        else
        {
            // when both are equal
            ret_array[n++] = nums1[i];
            i++;
            j++;
        }
    }
    *returnSize = n;
    return ret_array;
}

#include <stdio.h>

#define NUM_TESTS 3
#define MAX_NUM_VALUES 10

// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2,2]
// Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [4,9]
int testcase[NUM_TESTS*2][MAX_NUM_VALUES] = { // tc1-nums1, tc1-nums2, ...
    // TC1
    {1,2,2,1},
    {2,2},
    // TC2
    {4,9,5},
    {9,4,9,8,4},
    // TC3
    {1, 2, 3, 3, 4, 5, 5, 6},
    {3, 3, 5, 3},
};

int testcasesize[NUM_TESTS][2] = { // array1, array2
    {4,2},
    {3,5},
    {8,4},
};

int testanswersize[NUM_TESTS] = {
    2,
    2,
    3,
};

int testanswers[NUM_TESTS][MAX_NUM_VALUES] = {
    {2,2},
    {4,9,5},
    {3,3,5},
};

int main(void)
{
    int status = 0;
    int returnSize = 0;

    int nums1;
    int nums2;

    int *result;

    for (int i=0; i<NUM_TESTS*2; i+=2)
    {
        nums1 = testcasesize[i/2][0]; // sizeof(testcase[i])/sizeof(testcase[i][0]);
        nums2 = testcasesize[i/2][1]; // sizeof(testcase[i+1])/sizeof(testcase[i+1][0]);

        result = intersect(testcase[i], nums1, testcase[i+1], nums2, &returnSize);
        printf("Test #%d returnSize: %d", i/2, returnSize);
        if (returnSize != testanswersize[i/2])
        {
            status = -1;
            printf(" Expecting %d", testanswersize[i/2]);
        }
        else
        {
            if (returnSize)
            {
                for(int n=0; n<returnSize; n++)
                {
                    if (result[n] != testanswers[i/2][n])
                    {
                        status = -1;
                        printf(" result[%d]: %d", n, result[n]);
                        printf(" Expecting %d", testanswers[i/2][n]);
                    }

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
