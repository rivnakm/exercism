#include "list_ops.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constructs a new list
list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *list = malloc(sizeof(list_t));
    list->length = length;
    list->elements = malloc(sizeof(list_element_t) * length);

    memcpy(list->elements, elements, sizeof(list_element_t) * length);

    return list;
}

// append entries to a list and return the new list
list_t *append_list(list_t *list1, list_t *list2)
{
    list_t *list = malloc(sizeof(list_t));
    list->length = list1->length + list2->length;
    list->elements = malloc(sizeof(list_element_t) * list->length);

    list_element_t *a_dest = list->elements;
    size_t a_bytes = sizeof(list_element_t) * list1->length;

    list_element_t *b_dest = list->elements + list1->length;
    size_t b_bytes = sizeof(list_element_t) * list2->length;

    memcpy(a_dest, list1->elements, a_bytes);
    memcpy(b_dest, list2->elements, b_bytes);

    return list;
}

// filter list returning only values that satisfy the filter function
list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{
    list_t *result = malloc(sizeof(list_t));
    result->length = 0;
    result->elements = malloc(sizeof(list_element_t) * list->length);

    for (size_t i = 0; i < list->length; i++)
    {
        if (filter(list->elements[i]))
        {
            result->elements[result->length++] = list->elements[i];
        }
    }

    result->elements = realloc(result->elements, sizeof(list_element_t) * result->length);

    return result;
}

// returns the length of the list
size_t length_list(list_t *list)
{
    return list->length;
}

// return a list of elements whose values equal the list value transformed by
// the mapping function
list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{
    list_t *result = malloc(sizeof(list_t));
    result->length = list->length;
    result->elements = malloc(sizeof(list_element_t) * list->length);

    for (size_t i = 0; i < list->length; i++)
    {
        result->elements[i] = map(list->elements[i]);
    }

    return result;
}

// folds (reduces) the given list from the left with a function
list_element_t foldl_list(list_t *list, list_element_t initial, list_element_t (*foldl)(list_element_t, list_element_t))
{
    list_element_t result = initial;
    for (size_t i = 0; i < list->length; i++)
    {
        result = foldl(result, list->elements[i]);
    }

    return result;
}

// folds (reduces) the given list from the right with a function
list_element_t foldr_list(list_t *list, list_element_t initial, list_element_t (*foldr)(list_element_t, list_element_t))
{
    if (list->length == 0)
    {
        return initial;
    }

    list_element_t result = initial;
    for (size_t i = list->length - 1;; i--)
    {
        result = foldr(list->elements[i], result);

        if (i == 0)
        {
            break;
        }
    }

    return result;
}

// reverse the elements of the list
list_t *reverse_list(list_t *list)
{
    list_t *result = malloc(sizeof(list_t));
    result->length = list->length;
    result->elements = malloc(sizeof(list_element_t) * list->length);

    for (size_t i = 0; i < list->length; i++)
    {
        result->elements[i] = list->elements[list->length - 1 - i];
    }

    return result;
}

// destroy the entire list
// list will be a dangling pointer after calling this method on it
void delete_list(list_t *list)
{
    free(list->elements);
    free(list);
}
