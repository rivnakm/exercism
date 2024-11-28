#include "nucleotide_count.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_NUCLEOTIDES (4)

typedef enum
{
    ADENINE = 'A',
    CYTOSINE = 'C',
    GUANINE = 'G',
    THYMINE = 'T',
} nucleotide_t;

typedef struct
{
    char key;
    size_t count;
} bucket_t;

bucket_t *get(bucket_t *buckets, const char key);

char *count(const char *dna_strand)
{
    const char nucleotides[] = {ADENINE, CYTOSINE, GUANINE, THYMINE};
    bucket_t *buckets = malloc(sizeof(bucket_t) * NUM_NUCLEOTIDES);

    for (size_t i = 0; i < NUM_NUCLEOTIDES; i++)
    {
        bucket_t bucket = {.key = nucleotides[i], .count = 0};
        buckets[i] = bucket;
    }

    size_t len = strlen(dna_strand);
    for (size_t i = 0; i < len; i++)
    {
        bucket_t *bucket = NULL;
        switch (dna_strand[i])
        {
        case ADENINE:
            bucket = get(buckets, ADENINE);
            bucket->count++;
            break;
        case CYTOSINE:
            bucket = get(buckets, CYTOSINE);
            bucket->count++;
            break;
        case GUANINE:
            bucket = get(buckets, GUANINE);
            bucket->count++;
            break;
        case THYMINE:
            bucket = get(buckets, THYMINE);
            bucket->count++;
            break;
        default:
            free(buckets);
            char *result = malloc(sizeof(char));
            result[0] = '\0';
            return result;
        }
    }

    size_t a_count = get(buckets, ADENINE)->count;
    size_t c_count = get(buckets, CYTOSINE)->count;
    size_t g_count = get(buckets, GUANINE)->count;
    size_t t_count = get(buckets, THYMINE)->count;
    free(buckets);

    // asprintf() is a GNU extension
    size_t buf_size = 16;
    size_t formatted_len = 0;
    char *result = malloc(buf_size);
    formatted_len = snprintf(result, buf_size, "A:%zu C:%zu G:%zu T:%zu", a_count, c_count, g_count, t_count);
    if (formatted_len > buf_size)
    {
        buf_size = formatted_len + 1;
        result = realloc(result, buf_size);
        formatted_len = snprintf(result, buf_size, "A:%zu C:%zu G:%zu T:%zu", a_count, c_count, g_count, t_count);
    }

    return result;
}

bucket_t *get(bucket_t *buckets, const char key)
{
    for (size_t i = 0; i < NUM_NUCLEOTIDES; i++)
    {
        if (buckets[i].key == key)
        {
            return &buckets[i];
        }
    }

    return NULL;
}
