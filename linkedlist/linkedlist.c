/*
 * Linked List Library
 * Library for generic linked list implementation
 */

#include <stdio.h>
#include <stdint.h>

#include "linkedlist.h"

#define DATA_INIT_VALUE 0xdeadc0de

linkedlist_t        gList[LIST_LENGTH];
linkedlistCtrl_t    gListCtrl;

// TODO: Add linked list control structure accessor functions (setTail, getHead, getCount, etc...)

void printLL(void)
{
    int i;
    linkedlist_t *pLL = gList;

    printf("list array: %p\n", gList);
    printf("tail: %p\n", gListCtrl.pTail);

    for (i=0; i<LIST_LENGTH; i++)
    {  
        printf("item:%d:%p pNext: %p data: 0x%x\n", i, pLL, pLL->pNext, pLL->data);
        pLL++;
    }
}

int initList(void)
{
    int i;
    int status = 0;
    linkedlist_t *pLL = gList;

    for (i=0; i<LIST_LENGTH; i++)
    {
        pLL->pNext = NULL;
        pLL->data = DATA_INIT_VALUE;
        pLL++;
    }
    // reset the tail pointer
    gListCtrl.pTail = gList;

    return status;
}

linkedlist_t *ctrlGetTail(void)
{
    return gListCtrl.pTail;
}

int ctrlIncTail(void)
{
    gListCtrl.pTail++;
    return 0;
}

int isListFull(void)
{
    return ((gList+LIST_LENGTH-1)->pNext != NULL);
}

int addToList(linkedlist_t *pLL)
{
    int status = 0;
    linkedlist_t *pCtrlLL = gListCtrl.pTail;
    linkedlist_t *pTemp;

    if (isListFull())
    {
        // list full
        status = 1;
        return status;
    }

    pCtrlLL->data = pLL->data;
    if (pCtrlLL == gList+LIST_LENGTH-1)
    {
        pTemp = ctrlGetTail();
        pCtrlLL->pNext = (void *)pTemp;
    }
    else
    {
        status = ctrlIncTail();
        pTemp = ctrlGetTail();
        pCtrlLL->pNext = (void *)(++pTemp);
    }
    return status;
}

int removeFromList(void)
{
    int status = 0;

    if (NULL == gListCtrl.pTail->pNext)
    {
        // list empty
        status = 1;
        return status;
    }

    if (gList == gListCtrl.pTail)
    {
        // first element
        gListCtrl.pTail->data = DATA_INIT_VALUE;
        gListCtrl.pTail->pNext = NULL;
    }
    else 
    {
        gListCtrl.pTail->data = DATA_INIT_VALUE;
        gListCtrl.pTail->pNext = NULL;
        --gListCtrl.pTail;
    }

    return status;
}
