// Linked List Cycle
//
// Given head, the head of a linked list, determine if the linked list has a cycle in it.
//
// There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
//
// Return true if there is a cycle in the linked list. Otherwise, return false.
//
//
//
// Example 1:
//
// Input: head = [3,2,0,-4], pos = 1
// Output: true
// Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
//
// Example 2:
//
// Input: head = [1,2], pos = 0
// Output: true
// Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
//
// Example 3:
//
// Input: head = [1], pos = -1
// Output: false
// Explanation: There is no cycle in the linked list.
//
//
//
// Constraints:
//
//     The number of the nodes in the list is in the range [0, 10^4].
//     -10^5 <= Node.val <= 10^5
//     pos is -1 or a valid index in the linked-list.
//
//
//
// Follow up: Can you solve it using O(1) (i.e. constant) memory?

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

#include <stdbool.h>
#include <stdlib.h>

bool hasCycle(struct ListNode *head) {
    bool hashtable[10000] = {false};

    if(head == NULL)
    {
        return false;
    }

    // walk the list
    while(???)
    {
        head = head->next;
        if (head->next == NULL)
        {
            return false;
        }
    }

    return true;
}

#include <stdio.h>
#include <string.h>

#define NUM_TESTS 4
#define MAX_NUM_VALUES 5

struct ListNode testcase[MAX_NUM_VALUES];
struct ListNode results[MAX_NUM_VALUES];

int testcase_val[NUM_TESTS][MAX_NUM_VALUES] = {
    // list
    {3, 2, 0, -4},
    {1, 4, 5, 6},
    {1, 2, 4},
    {2},
};

int testcase_len[NUM_TESTS] = {
    // list length
    4,
    4,
    3,
    1,
};

int testcase_pos[NUM_TESTS] = {
    // loop position
    1,
    0,
    1,
    -1,
};

bool testcase_retval[NUM_TESTS] = {
    true,
    true,
    true,
    false,
};

void initLinkedLists(int testcase_num)
{
    struct ListNode *pLoopback = NULL;
    for (int i=0; i<testcase_len[testcase_num]; i++)
    {
        testcase[i].val = testcase_val[testcase_num][i];
        if (i == testcase_len[testcase_num]-1)
        {
            testcase[i].next = pLoopback;
        }
        else
        {
            testcase[i].next = &testcase[i+1];
        }
        if (i == testcase_pos[testcase_num])
        {
            // store off pos address for final linakage
            pLoopback = &testcase[i];
        }
    }
}

int main(void)
{
    bool results;
    int status = 0;

    for (int i=0; i<NUM_TESTS; i++)
    {
        int test_status = 0;

        // init linked list
        initLinkedLists(i);

        printf("Test #%d\n", i);

        // call DUT
        results = hasCycle(testcase);

        // check values against expected
        if (results != testcase_retval[i])
        {
            printf("\tTest case %d did not return expected value: retval = %s\n", i, (results ? "true" : "false"));
            status = -1;
        }
        printf("\n");
    }

    if (status == 0)
    {
        printf("All Test Cases passed!!\n");
    }
    else
    {
        printf("One or more test cases failed!!\n");
    }
    return status;
}
