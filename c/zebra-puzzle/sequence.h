#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdbool.h>
#include <stddef.h>

void create_sequence(unsigned int *seq, const size_t len);
void random_sequence(unsigned int *seq, const size_t len);
void shuffle_sequence(unsigned int *seq, const size_t len);
bool sequence_contains(const unsigned int *seq, const size_t len, const unsigned int value);

#endif
