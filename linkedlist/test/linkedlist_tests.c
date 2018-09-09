/*
 * Main test function for Linked List library
 *
 */

#include <stdio.h>
#include <stdint.h>

#include "linkedlist.h"
#include "CuTest.h"

void testLinkedList(CuTest* tc)
{
    int status = 0;
    int i;
    linkedlist_t item;
    linkedlist_t *pItem = &item;

    status = initList();
    CuAssertIntEquals_Msg(tc, "Init error", status, 0);

    status = isListFull();
    CuAssertIntEquals_Msg(tc, "Empty list flagged as full", status, 0);

    printLL();

    printf("Adding to list\n");
    for (i=0; i<LIST_LENGTH; i++)
    {
        pItem->data = i;
        status = addToList(pItem);
        CuAssertIntEquals_Msg(tc, "Error adding to list", status, 0);
        printLL();
    }

    // add to full list
    status = isListFull();
    CuAssertIntEquals_Msg(tc, "Full list not flagged as full", status, 1);
    pItem->data = 0x1d107;
    status = addToList(pItem);
    CuAssertIntEquals_Msg(tc, "Added element to full list", status, 1);

    printf("Removing from list\n");
    for (i=0; i<LIST_LENGTH; i++)
    {
        status = removeFromList();
        CuAssertIntEquals_Msg(tc, "Error removing from list", status, 0);
        printLL();
    }

    status = isListFull();
    CuAssertIntEquals_Msg(tc, "Empty list flagged as full", status, 0);

    // remove from empty list
    status = removeFromList();
    CuAssertIntEquals_Msg(tc, "Removed element from empty list", status, 1);
}

CuSuite* CuGetSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testLinkedList);

    return suite;
}
