// Reverse Linked List
//
// Reverse a singly linked list.
//
// Example:
//
// Input: 1->2->3->4->5->NULL
// Output: 5->4->3->2->1->NULL
//
// Follow up:
//
// A linked list can be reversed either iteratively or recursively. Could you implement both?

#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head)
{
    // NULL check
    if (head == NULL)
    {
        return NULL;
    }

#ifdef ITERATIVE
    // walk list until end
    // temp store current node
    // set actual node to new values
    struct ListNode *pTemp = NULL;
    struct ListNode *pNext = NULL;
    struct ListNode *pPrev = NULL;
    int endOfList = 0;

    while (!endOfList)
    {
        if (head->next == NULL)
        {
            endOfList = 1;
        }
        // save this address
        pTemp = head;
        pNext = head->next;
        // assign back to previous node
        head->next = pPrev;
        pPrev = pTemp;
        // jump to next node (as long as not end!)
        if (pNext)
        {
            head = pNext;
        }
    }
    return head;
#else // RECURSIVE
    return NULL;
#endif
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 2
#define MAX_NUM_VALUES 5

struct ListNode testcase[MAX_NUM_VALUES];
struct ListNode results[MAX_NUM_VALUES];

int testcase_val[NUM_TESTS][MAX_NUM_VALUES] = {
    {1, 2, 3, 4, 5},
    {999,998,997},
};

int testcase_next[NUM_TESTS][MAX_NUM_VALUES] = {
    {1, 2, 3, 4, -1},
    {1, 2, -1},
};

int testcase_size[NUM_TESTS] = {
    5,
    3,
};

int testanswers[NUM_TESTS][MAX_NUM_VALUES] = {
    {5, 4, 3, 2, 1},
    {997,998,999},
};

void initLinkedList(int testcase_num)
{
    for (int i=0; i<testcase_size[testcase_num]; i++)
    {
        testcase[i].val = testcase_val[testcase_num][i];
        if (testcase_next[testcase_num][i] == -1)
        {
            testcase[i].next = NULL;
        }
        else
        {
            testcase[i].next = &testcase[testcase_next[testcase_num][i]];
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
        initLinkedList(i);

        printf("Test #%d\n", i);

        // call DUT
        pResults = reverseList(testcase);

        // check values against expected
        for (int n=0; n<testcase_size[i]; n++)
        {
            if (pResults->val != testanswers[i][n])
            {
                printf("\tnode %d Expecting %d\n", n, testanswers[i][n]);
                test_status = -1;
                status = -1;
            }
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
