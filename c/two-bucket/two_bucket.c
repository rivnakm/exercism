#include "two_bucket.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct
{
    bucket_id_t id;
    bucket_liters_t size;
    bucket_liters_t level;
} bucket_t;

bucket_t bucket_create(bucket_id_t id, bucket_liters_t size);
bucket_liters_t bucket_available(const bucket_t *bucket);
bool bucket_is_full(const bucket_t *bucket);
bool bucket_is_empty(const bucket_t *bucket);
void bucket_fill(bucket_t *bucket);
void bucket_empty(bucket_t *bucket);
void bucket_pour_into(bucket_t *bucket, bucket_t *other);

bool check(bucket_liters_t goal_volume, const bucket_t *start, const bucket_t *other, int move_count,
           bucket_result_t *result);

bucket_result_t measure(bucket_liters_t bucket_1_size, bucket_liters_t bucket_2_size, bucket_liters_t goal_volume,
                        bucket_id_t start_bucket)
{
    bucket_t start;
    bucket_t other;
    switch (start_bucket)
    {
    case BUCKET_ID_1:
        start = bucket_create(BUCKET_ID_1, bucket_1_size);
        other = bucket_create(BUCKET_ID_2, bucket_2_size);
        break;
    case BUCKET_ID_2:
        start = bucket_create(BUCKET_ID_2, bucket_2_size);
        other = bucket_create(BUCKET_ID_1, bucket_1_size);
        break;
    }
    int move_count = 0;

    if (other.size == goal_volume)
    {
        return (bucket_result_t){
            .possible = true, .move_count = 2, .goal_bucket = other.id, .other_bucket_liters = start.size};
    }

    bucket_result_t result;
    while (!check(goal_volume, &start, &other, move_count, &result))
    {
        if (bucket_is_empty(&start))
        {
            bucket_fill(&start);
        }
        else if (bucket_is_full(&other))
        {
            bucket_empty(&other);
        }
        else
        {
            bucket_pour_into(&start, &other);
        }
        move_count++;

        if (bucket_is_full(&start) && bucket_is_full(&other))
        {
            return (bucket_result_t){.possible = false};
        }
    }

    return result;
}

bucket_t bucket_create(bucket_id_t id, bucket_liters_t size)
{
    return (bucket_t){.id = id, .size = size, .level = 0};
}

bucket_liters_t bucket_available(const bucket_t *bucket)
{
    return bucket->size - bucket->level;
}

bool bucket_is_full(const bucket_t *bucket)
{
    return bucket->size == bucket->level;
}

bool bucket_is_empty(const bucket_t *bucket)
{
    return bucket->level == 0;
}

void bucket_fill(bucket_t *bucket)
{
    bucket->level = bucket->size;
}

void bucket_empty(bucket_t *bucket)
{
    bucket->level = 0;
}

void bucket_pour_into(bucket_t *bucket, bucket_t *other)
{
    bucket_liters_t amount = fmin(bucket->level, bucket_available(other));
    bucket->level -= amount;
    other->level += amount;
}

bool check(bucket_liters_t goal_volume, const bucket_t *start, const bucket_t *other, int move_count,
           bucket_result_t *result)
{
    if (start->level == goal_volume)
    {
        result->possible = true;
        result->move_count = move_count;
        result->goal_bucket = start->id;
        result->other_bucket_liters = other->level;
        return true;
    }
    if (other->level == goal_volume)
    {
        result->possible = true;
        result->move_count = move_count;
        result->goal_bucket = other->id;
        result->other_bucket_liters = start->level;
        return true;
    }
    return false;
}
