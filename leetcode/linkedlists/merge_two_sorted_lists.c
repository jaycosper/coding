// Merge Two Sorted Lists
//
// Merge two sorted linked lists and return it as a sorted list. The list
// should be made by splicing together the nodes of the first two lists.
//
// Example 1:
//
// Input: l1 = [1,2,4], l2 = [1,3,4]
// Output: [1,1,2,3,4,4]
//
// Example 2:
//
// Input: l1 = [], l2 = []
// Output: []
//
// Example 3:
//
// Input: l1 = [], l2 = [0]
// Output: [0]
//
// Constraints:
//
//     The number of nodes in both lists is in the range [0, 50].
//     -100 <= Node.val <= 100
//     Both l1 and l2 are sorted in non-decreasing order.

#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* insertNodeBetween(struct ListNode* l1, struct ListNode* l2, struct ListNode* insertedNode)
{
    return NULL;
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    // NULL Checks
    if (l1 == NULL && l2 == NULL) { return NULL; }
    if (l1 == NULL && l2 != NULL) { return l2; }
    if (l1 != NULL && l2 == NULL) { return l1; }

    struct ListNode* l1_prev = l1;
    struct ListNode* l2_prev = l2;
    struct ListNode* pHead = NULL;
    int l1_curr_val, l2_curr_val;

    // select starting list
    if (l1->val <= l2->val)
    {
        pHead = l1;
    }
    else
    {
        pHead = l2;
    }
    // neither list is NULL, start processing
    while (l1 && l2)
    {
        l1_curr_val = l1->val;
        l2_curr_val = l2->val;

        // scan list l1
        while(l1_curr_val <= l2_curr_val)
        {
            l1_prev = l1;
            l1 = l1->next;
            if (l1)
            {
                l1_curr_val = l1->val;
            }
            else
            {
                // l1->next is NULL
                break;
            }
        }
        // insert l2 into l1 chain
        if (l2)
        {
            l1_prev->next = l2;
        }

        // scan list l2
        while(l2_curr_val <= l1_curr_val)
        {
            l2_prev = l2;
            l2 = l2->next;
            if (l2)
            {
                l2_curr_val = l2->val;
            }
            else
            {
                // l2->next is NULL
                break;
            }
        }

        // insert l1 into l2 chain
        if (l1)
        {
            l2_prev->next = l1;
        }
    }

    return pHead;
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 4
#define MAX_NUM_VALUES 5

struct ListNode testcase[2][MAX_NUM_VALUES];
struct ListNode results[MAX_NUM_VALUES];

int testcase_val[NUM_TESTS][2][MAX_NUM_VALUES] = {
    // l1, l2
    {{1, 3, 5},     {2, 4, 6}},
    {{1, 4, 5, 6},  {2, 7, 8}},
    {{1, 2, 4},     {1,3,4}},
    {{2},           {1}},
};

int testcase_size[NUM_TESTS][2] = {
    {3, 3},
    {4, 3},
    {3, 3},
    {1, 1},
};

void initLinkedLists(int testcase_num)
{
    for (int k=0; k<2; k++)
    {
        for (int i=0; i<testcase_size[testcase_num][k]; i++)
        {
            testcase[k][i].val = testcase_val[testcase_num][k][i];
            if (i == testcase_size[testcase_num][k]-1)
            {
                testcase[k][i].next = NULL;
            }
            else
            {
                testcase[k][i].next = &testcase[k][i+1];
            }
        }
    }
}

int main(void)
{
    struct ListNode *pResults = NULL;
    int status = 0;
    int retval = 0;


    for (int i=0; i<NUM_TESTS; i++)
    {
        int test_status = 0;

        // init linked list
        initLinkedLists(i);

        printf("Test #%d\n", i);

        // call DUT
        pResults = mergeTwoLists(testcase[0], testcase[1]);

        // check values against expected
        int prev_val = -1000;
        for (int n=0; n<(testcase_size[i][0]+testcase_size[i][1]); n++)
        {
            if (pResults == NULL)
            {
                printf("\tnode %d NULL\n", n);
                test_status = -1;
                status = -1;
                continue;
            }
            if (pResults->val < prev_val)
            {
                printf("\tnode %d list not sorted %d < %d\n", n, pResults->val, prev_val);
                test_status = -1;
                status = -1;
            }
            prev_val = pResults->val;
            pResults = pResults->next;
        }
        if (test_status)
        {
            printf("\tTestcase Failed");
        }
        else
        {
            printf("\tTestcase Passed");
        }
        printf("\n");
    }

    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    return status;
}
