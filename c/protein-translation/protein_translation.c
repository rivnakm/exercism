#include "protein_translation.h"

#include <stdlib.h>
#include <string.h>

typedef struct
{
    char value[4];
} codon_t;

size_t get_codons(const char *const rna, codon_t **codons);

proteins_t proteins(const char *const rna)
{
    codon_t *codons = NULL;
    size_t codons_count = get_codons(rna, &codons);

    proteins_t proteins = {.valid = true, .count = 0, .proteins = {0}};

    bool stop = false;
    for (size_t i = 0; i < codons_count; i++)
    {
        if (strcmp(codons[i].value, "AUG") == 0)
        {
            proteins.proteins[proteins.count++] = Methionine;
        }
        else if (strcmp(codons[i].value, "UUU") == 0 || strcmp(codons[i].value, "UUC") == 0)
        {
            proteins.proteins[proteins.count++] = Phenylalanine;
        }
        else if (strcmp(codons[i].value, "UUA") == 0 || strcmp(codons[i].value, "UUG") == 0)
        {
            proteins.proteins[proteins.count++] = Leucine;
        }
        else if (strcmp(codons[i].value, "UCU") == 0 || strcmp(codons[i].value, "UCC") == 0 ||
                 strcmp(codons[i].value, "UCA") == 0 || strcmp(codons[i].value, "UCG") == 0)
        {
            proteins.proteins[proteins.count++] = Serine;
        }
        else if (strcmp(codons[i].value, "UAU") == 0 || strcmp(codons[i].value, "UAC") == 0)
        {
            proteins.proteins[proteins.count++] = Tyrosine;
        }
        else if (strcmp(codons[i].value, "UGU") == 0 || strcmp(codons[i].value, "UGC") == 0)
        {
            proteins.proteins[proteins.count++] = Cysteine;
        }
        else if (strcmp(codons[i].value, "UGG") == 0)
        {
            proteins.proteins[proteins.count++] = Tryptophan;
        }
        else if (strcmp(codons[i].value, "UAA") == 0 || strcmp(codons[i].value, "UAG") == 0 ||
                 strcmp(codons[i].value, "UGA") == 0)
        {
            stop = true;
            break;
        }
        else
        {
            proteins.valid = false;
            proteins.count = 0;
            break;
        }
    }

    if (strlen(rna) % 3 != 0 && !stop)
    {
        proteins.valid = false;
        return proteins;
    }

    free(codons);
    return proteins;
}

size_t get_codons(const char *const rna, codon_t **codons)
{
    size_t codons_count = strlen(rna) / 3;
    *codons = malloc(codons_count * sizeof(codon_t));
    for (size_t i = 0; i < codons_count; i++)
    {
        strncpy((*codons)[i].value, rna + i * 3, 3);
        (*codons)[i].value[3] = '\0';
    }
    return codons_count;
}
