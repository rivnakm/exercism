#ifndef ROMAN_NUMERALS_H
#define ROMAN_NUMERALS_H

typedef enum
{
    NUMERAL_I,
    NUMERAL_V,
    NUMERAL_X,
    NUMERAL_L,
    NUMERAL_C,
    NUMERAL_D,
    NUMERAL_M,
} roman_numeral_t;

char *to_roman_numeral(unsigned int number);

#endif
