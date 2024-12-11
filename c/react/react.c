#include "react.h"

#include <stdbool.h>
#include <stdlib.h>

enum compute_type
{
    COMPUTE_TYPE_SINGLE,
    COMPUTE_TYPE_DOUBLE,
};

struct compute_registry
{
    enum compute_type type;
    struct cell *input_cell_a;
    struct cell *input_cell_b;
    compute1 single_fn;
    compute2 double_fn;
    struct cell *output_cell;
    struct compute_registry *next;
};

struct callback_registry
{
    struct cell *cell;
    callback_id id;
    callback function;
    void *param;
    bool ready;
    bool previously_called;
    int last_value;
    struct callback_registry *next;
};

struct reactor
{
    struct cell *cells;
    struct compute_registry *compute_reg;
    struct callback_registry *callback_reg;
};

struct cell
{
    struct reactor *reactor;
    int value;
    struct cell *next;
};

void add_cell(struct reactor *reactor, struct cell *cell);
void propagate_compute(struct reactor *reactor, struct cell *cell);
void mark_callbacks(struct reactor *reactor, struct cell *cell);
void trigger_callbacks(struct reactor *reactor);

struct reactor *create_reactor(void)
{
    struct reactor *reactor = (struct reactor *)malloc(sizeof(struct reactor));

    reactor->cells = NULL;
    reactor->compute_reg = NULL;
    reactor->callback_reg = NULL;

    return reactor;
}

// destroy_reactor should free all cells created under that reactor.
void destroy_reactor(struct reactor *reactor)
{
    struct callback_registry *callback_reg = reactor->callback_reg;
    while (callback_reg != NULL)
    {
        struct callback_registry *next = callback_reg->next;
        free(callback_reg);

        callback_reg = next;
    }

    struct compute_registry *compute_reg = reactor->compute_reg;
    while (compute_reg != NULL)
    {
        struct compute_registry *next = compute_reg->next;
        free(compute_reg);

        compute_reg = next;
    }

    struct cell *cell = reactor->cells;
    while (cell != NULL)
    {
        struct cell *next = cell->next;
        free(cell);

        cell = next;
    }

    free(reactor);
}

struct cell *create_input_cell(struct reactor *reactor, int initial_value)
{
    struct cell *cell = (struct cell *)malloc(sizeof(struct cell));

    // Create input cell
    cell->reactor = reactor;
    cell->next = NULL;
    cell->value = initial_value;
    add_cell(reactor, cell);

    return cell;
}

struct cell *create_compute1_cell(struct reactor *reactor, struct cell *cell, compute1 compute)
{
    struct cell *compute_cell = (struct cell *)malloc(sizeof(struct cell));

    // Create compute cell
    compute_cell->reactor = reactor;
    compute_cell->value = compute(cell->value);
    compute_cell->next = NULL;
    add_cell(reactor, compute_cell);

    // Create new compute registry
    struct compute_registry *new_reg = (struct compute_registry *)malloc(sizeof(struct compute_registry));
    new_reg->type = COMPUTE_TYPE_SINGLE;
    new_reg->single_fn = compute;
    new_reg->input_cell_a = cell;
    new_reg->output_cell = compute_cell;
    new_reg->next = NULL;

    // Append compute registry to reactor
    if (reactor->compute_reg == NULL)
    {
        reactor->compute_reg = new_reg;
    }
    else
    {
        struct compute_registry *reg = reactor->compute_reg;
        while (reg->next != NULL)
        {
            reg = reg->next;
        }
        reg->next = new_reg;
    }

    return compute_cell;
}

struct cell *create_compute2_cell(struct reactor *reactor, struct cell *cell_a, struct cell *cell_b, compute2 compute)
{
    struct cell *compute_cell = (struct cell *)malloc(sizeof(struct cell));

    // Create compute cell
    compute_cell->reactor = reactor;
    compute_cell->value = compute(cell_a->value, cell_b->value);
    compute_cell->next = NULL;
    add_cell(reactor, compute_cell);

    // Create new compute registry
    struct compute_registry *new_reg = (struct compute_registry *)malloc(sizeof(struct compute_registry));
    new_reg->type = COMPUTE_TYPE_DOUBLE;
    new_reg->double_fn = compute;
    new_reg->input_cell_a = cell_a;
    new_reg->input_cell_b = cell_b;
    new_reg->output_cell = compute_cell;
    new_reg->next = NULL;

    // Append compute registry to reactor
    if (reactor->compute_reg == NULL)
    {
        reactor->compute_reg = new_reg;
    }
    else
    {
        struct compute_registry *reg = reactor->compute_reg;
        while (reg->next != NULL)
        {
            reg = reg->next;
        }
        reg->next = new_reg;
    }

    return compute_cell;
}

int get_cell_value(struct cell *cell)
{
    return cell->value;
}

void set_cell_value(struct cell *cell, int new_value)
{
    if (cell->value == new_value)
    {
        return;
    }

    cell->value = new_value;

    propagate_compute(cell->reactor, cell);
    trigger_callbacks(cell->reactor);
}

callback_id add_callback(struct cell *cell, void *obj, callback function)
{
    struct callback_registry *new_reg = (struct callback_registry *)malloc(sizeof(struct callback_registry));
    new_reg->cell = cell;
    new_reg->param = obj;
    new_reg->function = function;
    new_reg->ready = false;
    new_reg->last_value = cell->value;
    new_reg->next = NULL;

    struct reactor *reactor = cell->reactor;

    // Append callback registry to reactor
    if (reactor->callback_reg == NULL)
    {
        reactor->callback_reg = new_reg;
        new_reg->id = 0;
    }
    else
    {
        struct callback_registry *reg = reactor->callback_reg;
        while (reg->next != NULL)
        {
            reg = reg->next;
        }
        reg->next = new_reg;
        new_reg->id = reg->id + 1;
    }

    return new_reg->id;
}

void remove_callback(struct cell *cell, callback_id function_id)
{
    struct reactor *reactor = cell->reactor;

    struct callback_registry *reg = reactor->callback_reg;
    if (reg == NULL)
    {
        // no callbacks registered
        return;
    }

    // Callback is the first in the list
    if (reg->id == function_id)
    {
        reactor->callback_reg = reg->next;

        free(reg);
        return;
    }
    while (reg->next != NULL)
    {
        if (reg->next->id == function_id)
        {
            struct callback_registry *current = reg->next;
            reg->next = current->next;

            free(current);
        }
        reg = reg->next;
    }
}

void add_cell(struct reactor *reactor, struct cell *cell)
{
    // Append callback registry to reactor
    if (reactor->cells == NULL)
    {
        reactor->cells = cell;
    }
    else
    {
        struct cell *cells = reactor->cells;
        while (cells->next != NULL)
        {
            cells = cells->next;
        }
        cells->next = cell;
    }
}

void propagate_compute(struct reactor *reactor, struct cell *cell)
{
    int value = cell->value;
    mark_callbacks(reactor, cell);

    struct compute_registry *reg = reactor->compute_reg;
    while (reg != NULL)
    {
        int old_value = reg->output_cell->value;
        switch (reg->type)
        {
        case COMPUTE_TYPE_SINGLE:
            if (reg->input_cell_a == cell)
            {
                reg->output_cell->value = reg->single_fn(value);
                if (old_value != reg->output_cell->value)
                {
                    propagate_compute(reactor, reg->output_cell);
                }
            }
            break;
        case COMPUTE_TYPE_DOUBLE:
            if (reg->input_cell_a == cell)
            {
                reg->output_cell->value = reg->double_fn(value, reg->input_cell_b->value);
                if (old_value != reg->output_cell->value)
                {
                    propagate_compute(reactor, reg->output_cell);
                }
            }
            else if (reg->input_cell_b == cell)
            {
                reg->output_cell->value = reg->double_fn(reg->input_cell_a->value, value);
                if (old_value != reg->output_cell->value)
                {
                    propagate_compute(reactor, reg->output_cell);
                }
            }
            break;
        }
        reg = reg->next;
    }
}

void mark_callbacks(struct reactor *reactor, struct cell *cell)
{
    struct callback_registry *reg = reactor->callback_reg;
    while (reg != NULL)
    {
        if (reg->cell == cell)
        {
            reg->ready = true;
        }
        reg = reg->next;
    }
}

void trigger_callbacks(struct reactor *reactor)
{
    struct callback_registry *reg = reactor->callback_reg;
    while (reg != NULL)
    {
        if (reg->ready && reg->last_value != reg->cell->value)
        {
            reg->last_value = reg->cell->value;
            reg->function(reg->param, reg->cell->value);
            reg->ready = false;
        }
        reg = reg->next;
    }
}
