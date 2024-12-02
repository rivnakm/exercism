#include "linked_list.h"

#include <stdbool.h>
#include <stdlib.h>

struct list_node
{
    struct list_node *prev, *next;
    ll_data_t data;
};

struct list
{
    struct list_node *first, *last;
};

// constructs a new (empty) list
struct list *list_create(void)
{
    struct list *result = malloc(sizeof(struct list));
    result->last = NULL;
    result->first = NULL;

    return result;
}

// counts the items on a list
size_t list_count(const struct list *list)
{
    size_t count = 0;
    struct list_node *head = list->first;
    while (head != NULL)
    {
        count++;

        head = head->next;
    }

    return count;
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data)
{
    if (list->first == NULL && list->last == NULL)
    {
        // Empty list
        struct list_node *node = malloc(sizeof(struct list_node));
        node->data = item_data;

        node->prev = NULL;
        node->next = NULL;

        list->first = node;
        list->last = node;
    }
    else
    {
        // Non-empty list
        struct list_node *head = list->last;

        struct list_node *tail = malloc(sizeof(struct list_node));
        tail->data = item_data;

        head->next = tail;
        tail->prev = head;
        tail->next = NULL;

        list->last = tail;
    }
}

// removes item from back of a list
ll_data_t list_pop(struct list *list)
{
    struct list_node *old_tail = list->last;
    ll_data_t data = old_tail->data;

    struct list_node *new_tail = old_tail->prev;

    if (new_tail == NULL)
    {
        // List only had one item, last was also first
        list->first = NULL;
    }
    else
    {
        new_tail->next = NULL;
    }

    list->last = new_tail;

    free(old_tail);

    return data;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *old_head = list->first;
    struct list_node *new_head = malloc(sizeof(struct list_node));
    new_head->data = item_data;

    new_head->next = old_head;
    new_head->prev = NULL;
    if (old_head != NULL)
    {
        // Existing items in list
        old_head->prev = new_head;
    }
    else
    {
        // List was empty, new first is also last
        list->last = new_head;
    }

    list->first = new_head;
}

// removes item from front of a list
ll_data_t list_shift(struct list *list)
{
    struct list_node *old_head = list->first;

    ll_data_t data = old_head->data;

    struct list_node *new_head = old_head->next;

    if (new_head == NULL)
    {
        // List only had one item
        list->last = NULL;
    }
    else
    {
        new_head->prev = NULL;
    }
    list->first = new_head;

    free(old_head);

    return data;
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *head = list->first;
    while (head != NULL)
    {
        if (head->data == data)
        {
            struct list_node *prev = head->prev;
            struct list_node *next = head->next;

            if (prev != NULL)
            {
                prev->next = next;
            }

            if (next != NULL)
            {
                next->prev = prev;
            }

            if (list->last == head)
            {
                list->last = prev;
            }
            if (list->first == head)
            {
                list->first = next;
            }

            free(head);

            return;
        }
        else
        {
            head = head->next;
        }
    }
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list)
{
    struct list_node *head = list->first;
    while (head != NULL)
    {
        struct list_node *next = head->next;

        free(head);

        head = next;
    }
    free(list);
}
