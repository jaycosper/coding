#include <stdio.h>
// Functions to Print Elements of Array
void printArray(int A[], int size)
{
    for (int i=0; i < size; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// reference https://www.tutorialride.com/c-programming/sorting-in-c-programming.htm

// Bubble sort
//
//     This is one of the most simple algorithm.
//     The logic for this sort is that if the numbers are to be arranged in an ascending order then
//          the largest number will be pushed at the end of the list.
//     This process will be continued till all the numbers are placed in the proper order.
//     Every number will be scanned with the succeeding number and they are swapped if the top number
//          is larger than the succeeding number.
//     If the list is scanned once, it is called as a pass.
//     Even if the list is passed once only the largest number is pushed at the end the rest of the
//          numbers are still not placed.
//     For this, we may have to repeat this step many times to get the list sorted properly.
void bubbleSort(int a[], int n)
{
    int temp;
    // start at beginning of list, and iterate through N-1 items
    // i.e. for a list with 5 elements, this iteration loops 0..3 (4 items)
    for(int i=0; i<(n-1); i++)
    {
        // start at second item of list, and iterate through all remaining N-1 items
        // i.e. for a list with 5 elements, this iteration loops 1..4 (4 items)
        for(int j=i+1; j<n; j++)
        {
            // i is target, j is compare value
            // if i.item > j.item, swap positions in array
            // NOTE: for DESCENING list, reverse compare (<)
            if(a[i] > a[j])
            {
                // swap positions of i.item and j.item
                // need temporary variable for swap storage
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

// 2. Selection sort
//
//     This method of sorting is faster than the bubble sort as the movement of data is minimized.
//     Say we want to arrange data in ascending order, the largest number is selected and placed
//          at the end of the list.
//     When the next pass takes place the second largest number is selected and placed second last.
//     This process is repeated until all the elements are placed in the correct order.
//     With each pass the elements are reduced by 1 as one element is sorted and placed in a position.
void selectionSort (int x[], int n)
{
    int index, max_value;
    // i is placement position, starting at the end of the array
    for (int i=(n-1); i>=0; i--)
    {
        // default maximum values to first item
        max_value = x[0];
        // index is the position of the discovered maximum
        index = 0;
        // iterate over the list from second item (already selected first as default maximum),
        //  up to current placement position (which is decrementing after each i iteration)
        for(int j=1; j<=i; j++)
        {
            // check if this is a newly discovered maximum
            // NOTE: for DESCENING list, reverse compare (<)
            if(x[j] > max_value)
            {
                // discovered new maximum value; set value
                max_value = x[j];
                // save index of current position for later swapping
                index = j;
            }
        }
        // place old value at end of array in position of discovered maximum
        x[index] = x[i];
        // reassign new maximum to end of array
        x[i] = max_value;
    }
}

// 3. Insertion sort
// There are three types of insertion sort:
// a) Simple insertion sort
// b) List insertion sort
// c) Insertion sort using binary search.
//
//     It is more efficient than bubble sort.
//     The logic for this is that every element is picked up and inserted in
//          the proper place i.e. if we pick up one element for inserting, all
//          the other elements will be put in the proper order.
void insertionSort (int x[], int n)
{
#define INSERT_SORT
#ifdef INSERT_SORT
    int temp;
    // iterate over array starting at second element up to full length
    for(int i=1; i<n; i++)
    {
        int j;
        // select target value
        temp = x[i];
        // j iterator descends from current target to 0th item
        // set starting value at i iterator-1 (at least 0)
        j=i-1;
        // loop from i position down to 0th, swapping target as needed, until sorted position reached
        // NOTE: for DESCENING list, reverse compare (<)
        // NOTE: could be a FOR loop... see ALT implementation below
        while( (temp < x[j]) && (j >= 0) )
        {
            // target needs to be swapped, move compare value to lower position
            x[j+1] = x[j];
            // decrement compare position
            j-=1;
        }
        // place target value in new position
        x[j+1] = temp;
    }
#endif
#ifdef INSERT_SORT_ALT
    // Alternate implementation using only FOR loops. Same algorithmic approach
    int temp;
    for (int i=1 ; i<n; i++)
    {
        int j;
        temp = x[i];
        for(j=i-1; (j>=0) && (temp<x[j]); j--)
        {
            x[j+1] = x[j];
        }
        x[j+1] = temp;
    }
#endif
}

// reference https://www.edureka.co/blog/sorting-algorithms-in-c/

// Quick Sort
//
// QuickSort is a divide & conquer algorithm. QuickSort algorithm partitions the
//  complete array around the pivot element. Pivot element can be picked in mulitple ways:
//
//     First element as pivot
//     Last element as pivot
//     Median element as pivot
//     Random element as pivot
//
// In this blog we will be picking the last element as pivot element.
// partition() is the key process behind the QuickSort algorithm. In partitioning, the
//  pivot element plays an important role. Pivot is placed at its correct position in the
//  sorted array, all the elements smaller than pivot is placed before it, and all the
//  elements greater than pivot is placed after it. All this operation is completed in linear time.
// Then the array is divided in two parts from the pivot element (i.e. elements less than
//  pivot & elements greater than pivot) & both the arrays are recursively sorted using
//  Quicksort algorithm.
#include<stdio.h>
// Function to swap two elements
void swapElements(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Partition function
int partition (int arr[], int lowIndex, int highIndex)
{
    int pivotElement = arr[highIndex];
    int i = (lowIndex - 1);
    for (int j = lowIndex; j <= highIndex- 1; j++)
    {
        if (arr[j] <= pivotElement)
        {
            i++;
            swapElements(&arr[i], &arr[j]);
        }
    }
    swapElements(&arr[i + 1], &arr[highIndex]);
    return (i + 1);
}
// QuickSort Function
void quickSort(int arr[], int lowIndex, int highIndex)
{
    if (lowIndex < highIndex)
    {
        int pivot = partition(arr, lowIndex, highIndex);
        // Separately sort elements before & after partition
        quickSort(arr, lowIndex, pivot - 1);
        quickSort(arr, pivot + 1, highIndex);
    }
}

// Merge Sort
//
// Merge Sort is one of the best examples of Divide & Conquer algorithm. In Merge sort,
//  we divide the array recursively in two halves, until each sub-array contains a
//  single element, and then we merge the sub-array in a way that it results into a
//  sorted array. merge() function merges two sorted sub-arrays into one, wherein it
//  assumes that array[l .. n] and arr[n+1 .. r] are sorted.

#include<stdlib.h>
#include<stdio.h>
// Merge Function
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// Merge Sort Function in C
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// Main Function
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// Function to run selected sort algo
void runSortFunc(void (*func_ptr)(), int x[], int n)
{
    if (*func_ptr == NULL)
    {
        printf("NULL function pointer\n");
        return;
    }

    clock_t start, end;
    double cpu_time_used;

    printf("Given array: ");
    printArray(x, n);

    start = clock();

    // execute funcion pointer
    (*func_ptr)(x, n);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    printArray(x, n);
    printf("Time taken: %fs\n\n", cpu_time_used);
}

// Function to run selected sort algo
void runRecursiveSortFunc(void (*func_ptr)(), int x[], int lowerIdx, int upperIdx)
{
    if (*func_ptr == NULL)
    {
        printf("NULL function pointer\n");
        return;
    }

    clock_t start, end;
    double cpu_time_used;

    printf("Given array: ");
    printArray(x, upperIdx);

    start = clock();

    // execute funcion pointer
    (*func_ptr)(x, lowerIdx, upperIdx);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    printArray(x, upperIdx);
    printf("Time taken: %fs\n\n", cpu_time_used);
}

int main(void)
{
    //int arr[] = {-1, 85, 24, 63, 45, 17, 31, 96, -50, 5};
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    void (*func_ptr)(int*, int);
    void (*rfunc_ptr)(int*, int, int);
    int *working_array;
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int arr_size_bytes = arr_size*sizeof(int);
    working_array = malloc(arr_size_bytes);
    clock_t start, end;
    double cpu_time_used;

    printf("BUBBLE SORT\n");
    memcpy(working_array, arr, arr_size_bytes);
    func_ptr = &bubbleSort;
    runSortFunc(func_ptr, working_array, arr_size);

    printf("SELECTION SORT\n");
    memcpy(working_array, arr, arr_size_bytes);
    func_ptr = &selectionSort;
    runSortFunc(func_ptr, working_array, arr_size);

    printf("INSERTION SORT\n");
    memcpy(working_array, arr, arr_size_bytes);
    func_ptr = &insertionSort;
    runSortFunc(func_ptr, working_array, arr_size);

    printf("QUICK SORT\n");
    memcpy(working_array, arr, arr_size_bytes);
    rfunc_ptr = &quickSort;
    runRecursiveSortFunc(rfunc_ptr, working_array, 0, arr_size-1);

    printf("MERGE SORT\n");
    memcpy(working_array, arr, arr_size_bytes);
    rfunc_ptr = &mergeSort;
    runRecursiveSortFunc(rfunc_ptr, working_array, 0, arr_size-1);

    return 0;
}