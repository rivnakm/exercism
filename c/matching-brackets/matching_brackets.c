#include "matching_brackets.h"

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef char stack_value_t;
typedef struct
{
    stack_value_t *items;
    size_t head;
    size_t capacity;
} stack_t;

stack_t *stack_new(size_t capacity);
void stack_destroy(stack_t *stack);
int stack_pop(stack_t *stack, stack_value_t *value);
int stack_peek(const stack_t *stack, stack_value_t *value);
void stack_push(stack_t *stack, stack_value_t value);
size_t stack_length(const stack_t *stack);

bool match_stack(stack_t *stack, stack_value_t match);

bool is_paired(const char *input)
{
    size_t len = strlen(input);
    stack_t *stack = stack_new(10);

    bool failed = false;
    for (size_t i = 0; i < len; i++)
    {
        char ch = input[i];
        switch (ch)
        {
        case '[':
        case '(':
        case '{':
            stack_push(stack, ch);
            break;
        case ']':
            failed |= !match_stack(stack, '[');
            break;
        case ')':
            failed |= !match_stack(stack, '(');
            break;
        case '}':
            failed |= !match_stack(stack, '{');
            break;
        default:
            break;
        }

        if (failed)
        {
            break;
        }
    }
    if (stack_length(stack) > 0)
    {
        failed = true;
    }

    stack_destroy(stack);

    return !failed;
}

stack_t *stack_new(size_t capacity)
{
    stack_t *stack = malloc(sizeof(stack_t));
    stack->capacity = capacity;
    stack->head = 0;
    stack->items = malloc(sizeof(stack_value_t) * capacity);

    return stack;
}

void stack_destroy(stack_t *stack)
{
    free(stack->items);
    free(stack);
}

int stack_pop(stack_t *stack, stack_value_t *value)
{
    if (stack->head == 0)
    {
        errno = ENODATA;
        return EXIT_FAILURE;
    }

    *value = stack->items[--stack->head];

    return EXIT_SUCCESS;
}

int stack_peek(const stack_t *stack, stack_value_t *value)
{
    if (stack->head == 0)
    {
        errno = ENODATA;
        return EXIT_FAILURE;
    }

    *value = stack->items[stack->head - 1];

    return EXIT_SUCCESS;
}

void stack_push(stack_t *stack, stack_value_t value)
{
    if (stack->head == stack->capacity)
    {
        stack->capacity *= 2;
        stack->items = realloc(stack->items, stack->capacity);
    }

    stack->items[stack->head++] = value;
}

size_t stack_length(const stack_t *stack)
{
    return stack->head;
}

bool match_stack(stack_t *stack, stack_value_t match)
{
    stack_value_t head;
    if (stack_peek(stack, &head) == EXIT_FAILURE)
    {
        return false;
    }

    if (head == match)
    {
        stack_pop(stack, &head);
        return true;
    }

    return false;
}
