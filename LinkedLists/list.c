/*
 * list.c
 */
#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(List *list)
{
    void *data;

    /* Remove each element */
    while (list_size(list) > 0)
    {
        if (list_rem_next(list, NULL, (void **)&data) == 0
            && list->destroy != NULL)
            {
                /* Call user-defined function for data destruction */
                list->destroy(data);
            }
    }

    /* Clear structure as precaution */
    memset(list, 0, sizeof(List));
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;

    /* Allocate storage for new element */
    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;

    /* Insert the element into the list */
    new_element->data = (void *)data;
    
    /* if inserting at head (i.e. element before insert point is NULL) */
    if (element == NULL)
    {
        /* if list is empty */
        if (list_size(list) == 0)
            list->tail = new_element;
        new_element->next = list->head;
        list->head = new_element;
    }
    /* if inserting somewhere other than head */
    else
    {
        if (element->next == NULL)
            list->tail = new_element;
        new_element->next = element->next;
        element->next = new_element;
    }

    /* Increase size (element count) */
    list->size++;

    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt *old_element;      /* pointer used to free allocated memory after removal */

    /* Cannot remove from an empty list */
    if(list_size(list) == 0)
        return -1;

    /* if removing from head */
    if (element == NULL)
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if(list_size(list) == 1)
            list->tail = NULL;
    }
    /* if removing from somewhere else */
    else
    {
        if (element->next == NULL)
            return -1;

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL)
            list->tail = element;
    }

    /* Free memory */
    free(old_element);

    /* Decrease size (element count) */
    list->size--;

    return 0;
}