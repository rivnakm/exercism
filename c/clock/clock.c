#include "clock.h"
#include <stdio.h>
#include <string.h>

clock_t clock_create(int hour, int minute)
{
    while (minute < 0)
    {
        minute += 60;
        hour--;
    }
    while (minute >= 60)
    {
        minute -= 60;
        hour++;
    }
    while (hour < 0)
    {
        hour += 24;
    }

    hour = hour % 24;
    clock_t clock = {.text = {0}};
    snprintf(clock.text, sizeof(clock.text), "%02d:%02d", hour, minute);

    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int hour = 0;
    int minute = 0;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    minute += minute_add;

    return clock_create(hour, minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int hour = 0;
    int minute = 0;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    minute -= minute_subtract;

    return clock_create(hour, minute);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return strcmp(a.text, b.text) == 0;
}
