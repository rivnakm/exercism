#include "wordy.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    OPERATOR_NONE,
    OPERATOR_ADD,
    OPERATOR_SUB,
    OPERATOR_MUL,
    OPERATOR_DIV,
} operator_t;

bool try_parse_op(const char *token, operator_t *op);
bool is_number(const char *token);
int evaluate(int lhs, int rhs, operator_t op);

bool answer(const char *question, int *result)
{
    const char *question_prefix = "What is ";

    if (strncmp(question, question_prefix, strlen(question_prefix)) != 0)
    {
        return false;
    }

    size_t question_len = strlen(question);
    size_t prefix_len = strlen(question_prefix);
    size_t question_mark_len = 1;

    size_t question_copy_len = question_len - prefix_len - question_mark_len;

    char *question_copy = malloc(question_copy_len + 1);
    memset(question_copy, '\0', question_copy_len + 1);
    strncpy(question_copy, question + prefix_len, question_copy_len);

    // Get first term
    char *token = strtok(question_copy, " ");
    if (token == NULL)
    {
        // Invalid
        free(question_copy);
        return false;
    }
    if (is_number(token))
    {
        *result = atoi(token);
    }
    token = strtok(NULL, " ");

    operator_t op = OPERATOR_NONE;
    while (token != NULL)
    {
        if ((op == OPERATOR_DIV || op == OPERATOR_MUL) && strcmp(token, "by") == 0)
        {
            // no-op
        }
        else if (is_number(token))
        {
            // Parse and evaluate term
            if (op == OPERATOR_NONE)
            {
                // Invalid
                free(question_copy);
                return false;
            }

            int num = atoi(token);
            *result = evaluate(*result, num, op);
            op = OPERATOR_NONE;
        }
        else if (op != OPERATOR_NONE)
        {
            // Expected number after operator
            free(question_copy);
            return false;
        }
        else
        {
            if (!try_parse_op(token, &op))
            {
                // Invalid operator
                free(question_copy);
                return false;
            }
        }
        token = strtok(NULL, " ");
    }
    if (op != OPERATOR_NONE)
    {
        // Dangling operator
        free(question_copy);
        return false;
    }

    free(question_copy);
    return true;
}

bool try_parse_op(const char *token, operator_t *op)
{
    if (strcmp(token, "plus") == 0)
    {
        *op = OPERATOR_ADD;
        return true;
    }
    else if (strcmp(token, "minus") == 0)
    {
        *op = OPERATOR_SUB;
        return true;
    }
    else if (strcmp(token, "multiplied") == 0)
    {
        *op = OPERATOR_MUL;
        return true;
    }
    else if (strcmp(token, "divided") == 0)
    {
        *op = OPERATOR_DIV;
        return true;
    }
    return false;
}

bool is_number(const char *token)
{
    size_t len = strlen(token);
    if (len == 0)
    {
        return false;
    }

    for (size_t i = 0; i < len; i++)
    {
        char ch = token[i];
        if (!(isdigit(ch) || ch == '-'))
        {
            return false;
        }
    }

    return true;
}

int evaluate(int lhs, int rhs, operator_t op)
{
    switch (op)
    {
    case OPERATOR_ADD:
        return lhs + rhs;
    case OPERATOR_SUB:
        return lhs - rhs;
    case OPERATOR_MUL:
        return lhs * rhs;
    case OPERATOR_DIV:
        return lhs / rhs;
    case OPERATOR_NONE:
    default:
        return -1;
    }
}
