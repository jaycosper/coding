#if 0
// CPP program to find union and intersection
// using sets
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Prints union of arr1[0..n1-1] and arr2[0..n2-1]
void printUnion(int arr1[], int arr2[], int n1, int n2)
{
    set<int> hs;

    // Inhsert the elements of arr1[] to set hs
    for (int i = 0; i < n1; i++)
        hs.insert(arr1[i]);

    // Insert the elements of arr2[] to set hs
    for (int i = 0; i < n2; i++)
        hs.insert(arr2[i]);

    // Print the content of set hs
    for (auto it = hs.begin(); it != hs.end(); it++)
        cout << *it << " ";
    cout << endl;
}

// Prints intersection of arr1[0..n1-1] and
// arr2[0..n2-1]
void printIntersection(int arr1[], int arr2[], int n1,
                       int n2)
{
    set<int> hs;

    // Insert the elements of arr1[] to set S
    for (int i = 0; i < n1; i++)
        hs.insert(arr1[i]);

    for (int i = 0; i < n2; i++)

        // If element is present in set then
        // push it to vector V
        if (hs.find(arr2[i]) != hs.end())
            cout << arr2[i] << " ";
    cout << endl;
}

// Driver Program
int main()
{
    int arr1[] = { 7, 3, 1, 5, 2, 6};
    int arr2[] = { 3, 8, 6, 20, 7, 3 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    // Function call
    printUnion(arr1, arr2, n1, n2);
    printIntersection(arr1, arr2, n1, n2);

    return 0;
}
#endif

// C code to find intersection when
// elements may not be distinct
#include<bits/stdc++.h>

using namespace std;

// Function to find intersection
void intersection(int a[], int b[], int n, int m)
{
    int i = 0, j = 0;

    while (i < n && j < m)
    {

        if (a[i] > b[j])
        {
            j++;
        }

        else
        if (b[j] > a[i])
        {
            i++;
        }
        else
        {
            // when both are equal
            cout << a[i] << " ";
            i++;
            j++;
        }
    }
}

// Driver Code
int main()
{
    int a[] = {5, 2, 1, 3, 4, 5, 3, 6};
    int b[] = {3, 3, 5, 3};

    int n = sizeof(a)/sizeof(a[0]);
    int m = sizeof(b)/sizeof(b[0]);
    intersection(a, b, n, m);
}
