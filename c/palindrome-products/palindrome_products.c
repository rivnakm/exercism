#include "palindrome_products.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_palindrome(const int number);
void free_factor(factor_t *f);

product_t *get_palindrome_product(int from, int to)
{
    product_t *result = malloc(sizeof(product_t));
    result->smallest = INT_MAX;
    result->largest = INT_MIN;
    result->factors_lg = NULL;
    result->factors_sm = NULL;
    memset(result->error, '\0', MAXERR);

    if (from > to)
    {
        snprintf(result->error, MAXERR - 1, "invalid input: min is %d and max is %d", from, to);
        return result;
    }

    for (int i = from; i <= to; i++)
    {
        for (int j = from; j <= to; j++)
        {
            int product = i * j;
            if (!is_palindrome(product))
            {
                continue;
            }

            if (product < result->smallest)
            {
                free_factor(result->factors_sm);
                result->factors_sm = malloc(sizeof(factor_t));
                result->factors_sm->factor_a = i;
                result->factors_sm->factor_b = j;
                result->factors_sm->next = NULL;
                result->smallest = product;
            }
            else if (product == result->smallest)
            {
                factor_t *new = malloc(sizeof(factor_t));
                new->factor_a = i;
                new->factor_b = j;
                new->next = NULL;

                factor_t *tail = result->factors_sm;
                while (true)
                {
                    if (tail->next == NULL)
                    {
                        break;
                    }
                    tail = tail->next;
                }

                tail->next = new;
            }

            if (product > result->largest)
            {
                free_factor(result->factors_lg);
                result->factors_lg = malloc(sizeof(factor_t));
                result->factors_lg->factor_a = i;
                result->factors_lg->factor_b = j;
                result->factors_lg->next = NULL;
                result->largest = product;
            }
            else if (product == result->largest)
            {
                factor_t *new = malloc(sizeof(factor_t));
                new->factor_a = i;
                new->factor_b = j;
                new->next = NULL;

                factor_t *tail = result->factors_lg;
                while (true)
                {
                    if (tail->next == NULL)
                    {
                        break;
                    }
                    tail = tail->next;
                }

                tail->next = new;
            }
        }
    }

    if (result->factors_lg == NULL && result->factors_sm == NULL)
    {
        snprintf(result->error, MAXERR - 1, "no palindrome with factors in the range %d to %d", from, to);
    }

    return result;
}
void free_product(product_t *p)
{
    if (p == NULL)
    {
        return;
    }

    free_factor(p->factors_sm);
    free_factor(p->factors_lg);
    free(p);
}

void free_factor(factor_t *f)
{
    if (f == NULL)
    {
        return;
    }

    free_factor(f->next);
    free(f);
}

bool is_palindrome(const int number)
{
    int reverse = 0;
    int temp = number;

    while (temp != 0)
    {
        reverse = (reverse * 10) + (temp % 10);
        temp = temp / 10;
    }

    return reverse == number;
}
