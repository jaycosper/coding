/*
 * Linked List Library header
 * Library for generic linked list implementation
 */

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef int linkedlist_data_t;

typedef struct
{
    struct linkedlist_t *pNext;
    linkedlist_data_t   data;
} linkedlist_t;

typedef struct
{
    linkedlist_t *pHead;
    linkedlist_t *pTail;
    int count;
} linkedlistCtrl_t;

#define LIST_LENGTH 8

void printLL(void);
int initList(void);
int isListFull(void);
int addToList(linkedlist_t *pLL);
int removeFromList(void);

#endif // __LINKEDLIST_H__