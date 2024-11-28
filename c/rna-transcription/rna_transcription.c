#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna)
{
    size_t len = strlen(dna);
    char *out = malloc(len + 1);

    out[len] = '\0';
    for (size_t i = 0; i < len; i++)
    {
        switch (dna[i])
        {
        case 'G':
            out[i] = 'C';
            break;
        case 'C':
            out[i] = 'G';
            break;
        case 'T':
            out[i] = 'A';
            break;
        case 'A':
            out[i] = 'U';
            break;
        default:
            out[i] = dna[i];
            break;
        }
    }

    return out;
}
