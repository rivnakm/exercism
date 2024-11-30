#include "grade_school.h"
#include <stdio.h>
#include <string.h>

void sort_roster(roster_t *roster);
int student_cmp(const student_t *s1, const student_t *s2);

void init_roster(roster_t *roster)
{
    roster->count = 0;
}

bool add_student(roster_t *roster, const char *name, uint8_t grade)
{
    for (size_t i = 0; i < roster->count; i++)
    {
        if (strcmp(roster->students[i].name, name) == 0)
        {
            return false;
        }
    }

    student_t new_student = {.grade = grade};
    strcpy(new_student.name, name);
    roster->students[roster->count++] = new_student;
    sort_roster(roster);

    return true;
}

roster_t get_grade(roster_t *all_students, uint8_t grade)
{
    roster_t result = {.count = 0};
    for (size_t i = 0; i < all_students->count; i++)
    {
        if (all_students->students[i].grade == grade)
        {
            result.students[result.count++] = all_students->students[i];
        }
    }

    return result;
}

void sort_roster(roster_t *roster)
{
    bool is_sorted = false;
    while (!is_sorted)
    {
        is_sorted = true;
        for (size_t i = 1; i < roster->count; i++)
        {
            int cmp = student_cmp(&roster->students[i - 1], &roster->students[i]);
            if (cmp > 0)
            {
                is_sorted = false;
                student_t temp = roster->students[i];
                roster->students[i] = roster->students[i - 1];
                roster->students[i - 1] = temp;
            }
        }
    }
}

int student_cmp(const student_t *s1, const student_t *s2)
{
    if (s1->grade < s2->grade)
    {
        return -1;
    }
    else if (s1->grade > s2->grade)
    {
        return 1;
    }
    else
    {
        return strcmp(s1->name, s2->name);
    }
}
