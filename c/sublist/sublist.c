#include "sublist.h"

#include <stdbool.h>

bool has_sublist(int *list_to_compare, int *base_list, size_t list_to_compare_element_count,
                 size_t base_list_element_count);

comparison_result_t check_lists(int *list_to_compare, int *base_list, size_t list_to_compare_element_count,
                                size_t base_list_element_count)
{
    if (list_to_compare_element_count == base_list_element_count)
    {
        for (size_t i = 0; i < base_list_element_count; i++)
        {
            if (list_to_compare[i] != base_list[i])
            {
                return UNEQUAL;
            }
        }
        return EQUAL;
    }
    else
    {
        if (list_to_compare_element_count > base_list_element_count &&
            has_sublist(base_list, list_to_compare, base_list_element_count, list_to_compare_element_count))
        {
            return SUPERLIST;
        }
        if (base_list_element_count > list_to_compare_element_count &&
            has_sublist(list_to_compare, base_list, list_to_compare_element_count, base_list_element_count))
        {
            return SUBLIST;
        }
        return UNEQUAL;
    }
}

bool has_sublist(int *list_to_compare, int *base_list, size_t list_to_compare_element_count,
                 size_t base_list_element_count)
{
    if (list_to_compare_element_count == 0)
    {
        return true;
    }
    for (size_t i = 0; i < base_list_element_count; i++)
    {
        for (size_t j = 0; j < list_to_compare_element_count; j++)
        {
            if (i + j >= base_list_element_count)
            {
                break;
            }

            if (base_list[i + j] != list_to_compare[j])
            {
                break;
            }

            if (j == list_to_compare_element_count - 1)
            {
                return true;
            }
        }
    }
    return false;
}
