/*
 * listDemo.c
 *
 * Program to demonstrate singly-linked list implementation by inserting random numbers at tail
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"

#define NUM_ELMTS 5

int main()
{
    List        listOfInts;
    ListElmt    *pElmt;
    int         *pInt;
    int         i;

    /* Seed random number generator */
    srand(time(NULL));

    /* Init list */
    list_init(&listOfInts, free);

    /* Output size of list, should be 0 */
    printf("Before inserts - list size: %d\n", list_size(&listOfInts));

    /* Insert elements at tail */
    for (i = 0; i < NUM_ELMTS; ++i)
    {
        /* Dynamically allocated int */
        if ((pInt = (int *)malloc(sizeof(int))) == 0)
            return -1;

        *pInt = random() % 100;

        /* Insert at tail */
        printf("Inserting %d into list\n", *pInt);
        if(list_ins_next(&listOfInts, list_tail(&listOfInts), pInt) != 0)
            return -1;
    }

    /* Output size of list, should be NUM_ELMTS */
    printf("After inserts - list size: %d\n", list_size(&listOfInts));

    /* Output data in the list */
    printf("Elements:");
    pElmt = list_head(&listOfInts);
    while (pElmt != NULL)
    {
        pInt = (int *)list_data(pElmt);
        printf( " %d,", *pInt);
        pElmt = pElmt->next;
    }
    printf("\n");

    /* Destroy the list */
    list_destroy(&listOfInts);

    /* Output size of list, should be 0 after destroy */
    printf("After destroy - list size: %d\n", list_size(&listOfInts));

    return EXIT_SUCCESS;
}