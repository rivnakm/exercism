#include "sequence.h"
#include <stdlib.h>

void create_sequence(unsigned int *seq, const size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        seq[i] = i;
    }
}

void random_sequence(unsigned int *seq, const size_t len)
{
    create_sequence(seq, len);
    shuffle_sequence(seq, len);
}

void shuffle_sequence(unsigned int *seq, const size_t len)
{
    if (len > 1)
    {
        for (size_t i = len - 1; i > 0; i--)
        {
            size_t j = rand() % (i + 1);
            unsigned int temp = seq[i];
            seq[i] = seq[j];
            seq[j] = temp;
        }
    }
}

bool sequence_contains(const unsigned int *seq, const size_t len, const unsigned int value)
{
    for (size_t i = 0; i < len; i++)
    {
        if (seq[i] == value)
        {
            return true;
        }
    }
    return false;
}
