#include "gigasecond.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void gigasecond(time_t input, char *output, size_t size)
{
    time_t after = input + pow(10, 9);
    struct tm *time = gmtime(&after);

    snprintf(output, size, "%04i-%02i-%02i %02i:%02i:%02i", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
             time->tm_hour, time->tm_min, time->tm_sec);
}
