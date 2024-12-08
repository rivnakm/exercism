#include "meetup.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    DAY_OF_WEEK_SUNDAY = 0,
    DAY_OF_WEEK_MONDAY,
    DAY_OF_WEEK_TUESDAY,
    DAY_OF_WEEK_WEDNESDAY,
    DAY_OF_WEEK_THURSDAY,
    DAY_OF_WEEK_FRIDAY,
    DAY_OF_WEEK_SATURDAY,
} day_of_week_t;

typedef enum
{
    WEEK_INDEX_FIRST,
    WEEK_INDEX_SECOND,
    WEEK_INDEX_THIRD,
    WEEK_INDEX_FOURTH,
    WEEK_INDEX_LAST,
    WEEK_INDEX_TEENTH,
} week_index_t;

const unsigned int EPOCH_YEAR = 1970;
const unsigned int EPOCH_MONTH = 1;
const unsigned int EPOCH_DAY = 1;
const day_of_week_t EPOCH_DAY_OF_WEEK = DAY_OF_WEEK_THURSDAY;

day_of_week_t parse_day_of_week(const char *day_of_week);
week_index_t parse_week_index(const char *week_index);

bool is_leap_year(unsigned int year);

unsigned int days_in_year(unsigned int year);
unsigned int days_in_month(unsigned int month, unsigned int year);

day_of_week_t first_day_of_year(unsigned int year);
day_of_week_t first_day_of_month(unsigned int month, unsigned int year);
day_of_week_t add_days(day_of_week_t day, int days);

int days_between_years(unsigned int start_year, unsigned int end_year);
int days_between_months(unsigned int start_month, unsigned int end_month, unsigned int year);

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week, const char *day_of_week)
{
    day_of_week_t day = parse_day_of_week(day_of_week);
    week_index_t week_index = parse_week_index(week);

    day_of_week_t first_of_month = first_day_of_month(month, year);
    unsigned int days_in_mon = days_in_month(month, year);
    switch (week_index)
    {
    case WEEK_INDEX_TEENTH:
        for (unsigned int day_num = 13; day_num < 20; day_num++)
        {
            if (add_days(first_of_month, day_num - 1) == day)
            {
                return day_num;
            }
        }
        break;
    case WEEK_INDEX_FIRST:
        for (unsigned int day_num = 1; day_num < 8; day_num++)
        {
            if (add_days(first_of_month, day_num - 1) == day)
            {
                return day_num;
            }
        }
        break;
    case WEEK_INDEX_SECOND:
        for (unsigned int day_num = 8; day_num < 15; day_num++)
        {
            if (add_days(first_of_month, day_num - 1) == day)
            {
                return day_num;
            }
        }
        break;
    case WEEK_INDEX_THIRD:
        for (unsigned int day_num = 15; day_num < 22; day_num++)
        {
            if (add_days(first_of_month, day_num - 1) == day)
            {
                return day_num;
            }
        }
        break;
    case WEEK_INDEX_FOURTH:
        for (unsigned int day_num = 22; day_num < days_in_mon; day_num++)
        {
            if (add_days(first_of_month, day_num - 1) == day)
            {
                return day_num;
            }
        }
        break;
    case WEEK_INDEX_LAST:
        for (unsigned int day_num = days_in_mon; day_num > days_in_mon - 7; day_num--)
        {
            if (add_days(first_of_month, day_num - 1) == day)
            {
                return day_num;
            }
        }
        break;
    }

    fprintf(stderr, "unimplemented week %s\n", week);
    exit(-1);
}

day_of_week_t parse_day_of_week(const char *day_of_week)
{
    if (strcmp(day_of_week, "Sunday") == 0)
    {
        return DAY_OF_WEEK_SUNDAY;
    }
    else if (strcmp(day_of_week, "Monday") == 0)
    {
        return DAY_OF_WEEK_MONDAY;
    }
    else if (strcmp(day_of_week, "Tuesday") == 0)
    {
        return DAY_OF_WEEK_TUESDAY;
    }
    else if (strcmp(day_of_week, "Wednesday") == 0)
    {
        return DAY_OF_WEEK_WEDNESDAY;
    }
    else if (strcmp(day_of_week, "Thursday") == 0)
    {
        return DAY_OF_WEEK_THURSDAY;
    }
    else if (strcmp(day_of_week, "Friday") == 0)
    {
        return DAY_OF_WEEK_FRIDAY;
    }
    else if (strcmp(day_of_week, "Saturday") == 0)
    {
        return DAY_OF_WEEK_SATURDAY;
    }

    fprintf(stderr, "unrecognized day %s\n", day_of_week);
    exit(-1);
}

week_index_t parse_week_index(const char *week_index)
{
    if (strcmp(week_index, "first") == 0)
    {
        return WEEK_INDEX_FIRST;
    }
    else if (strcmp(week_index, "second") == 0)
    {
        return WEEK_INDEX_SECOND;
    }
    else if (strcmp(week_index, "third") == 0)
    {
        return WEEK_INDEX_THIRD;
    }
    else if (strcmp(week_index, "fourth") == 0)
    {
        return WEEK_INDEX_FOURTH;
    }
    else if (strcmp(week_index, "last") == 0)
    {
        return WEEK_INDEX_LAST;
    }
    else if (strcmp(week_index, "teenth") == 0)
    {
        return WEEK_INDEX_TEENTH;
    }

    fprintf(stderr, "unrecognized week %s\n", week_index);
    exit(-1);
}

bool is_leap_year(unsigned int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

unsigned int days_in_year(unsigned int year)
{
    return is_leap_year(year) ? 366 : 365;
}

unsigned int days_in_month(unsigned int month, unsigned int year)
{
    switch (month)
    {
    case 1:
        /* fall through */
    case 3:
        /* fall through */
    case 5:
        /* fall through */
    case 7:
        /* fall through */
    case 8:
        /* fall through */
    case 10:
        /* fall through */
    case 12:
        return 31;
    case 4:
        /* fall through */
    case 6:
        /* fall through */
    case 9:
        /* fall through */
    case 11:
        return 30;
    case 2:
        return is_leap_year(year) ? 29 : 28;
    default:
        fprintf(stderr, "unsupported month %d\n", month);
        exit(-1);
    }
}

day_of_week_t first_day_of_year(unsigned int year)
{
    int days_from_epoch = days_between_years(EPOCH_YEAR, year);
    return add_days(EPOCH_DAY_OF_WEEK, days_from_epoch);
}

day_of_week_t first_day_of_month(unsigned int month, unsigned int year)
{
    int nth_day_of_year = days_between_months(1, month, year);

    return add_days(first_day_of_year(year), nth_day_of_year);
}

day_of_week_t add_days(day_of_week_t day, int days)
{
    return (day_of_week_t)((day + days) % 7);
}

int days_between_years(unsigned int start_year, unsigned int end_year)
{
    int total = 0;
    if (start_year < end_year)
    {
        for (unsigned int year = start_year; year < end_year; year++)
        {
            total += days_in_year(year);
        }
    }
    else if (start_year > end_year)
    {
        for (unsigned int year = end_year; year < start_year; year++)
        {
            total -= days_in_year(year);
        }
    }
    return total;
}

int days_between_months(unsigned int start_month, unsigned int end_month, unsigned int year)
{
    int total = 0;
    if (start_month < end_month)
    {
        for (unsigned int month = start_month; month < end_month; month++)
        {
            total += days_in_month(month, year);
        }
    }
    else if (start_month > end_month)
    {
        for (unsigned int month = end_month; month < start_month; month++)
        {
            total -= days_in_month(month, year);
        }
    }
    return total;
}
