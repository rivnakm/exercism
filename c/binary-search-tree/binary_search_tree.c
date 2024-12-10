#include "binary_search_tree.h"
#include <stdlib.h>

node_t *create_node(int value);
void add_node(node_t *root, int value);
void traverse_tree(node_t *node, int **data, size_t *length, size_t *capacity);
void append_int(int **data, size_t *length, size_t *capacity, const int value);

node_t *build_tree(int *tree_data, size_t tree_data_len)
{
    if (tree_data_len == 0)
    {
        return NULL;
    }

    node_t *root = create_node(tree_data[0]);

    for (size_t i = 1; i < tree_data_len; i++)
    {
        add_node(root, tree_data[i]);
    }

    return root;
}

void free_tree(node_t *tree)
{
    if (tree->left != NULL)
    {
        free_tree(tree->left);
    }
    if (tree->right != NULL)
    {
        free_tree(tree->right);
    }
    free(tree);
}

int *sorted_data(node_t *tree)
{
    size_t capacity = 20;
    size_t length = 0;
    int *data = malloc(sizeof(int) * capacity);

    traverse_tree(tree, &data, &length, &capacity);

    data = realloc(data, sizeof(int) * length);

    return data;
}

node_t *create_node(int value)
{
    node_t *node = malloc(sizeof(node_t));
    node->right = NULL;
    node->left = NULL;
    node->data = value;

    return node;
}

void add_node(node_t *root, int value)
{
    if (value <= root->data)
    {
        if (root->left == NULL)
        {
            root->left = create_node(value);
        }
        else
        {
            add_node(root->left, value);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = create_node(value);
        }
        else
        {
            add_node(root->right, value);
        }
    }
}

void traverse_tree(node_t *node, int **data, size_t *length, size_t *capacity)
{
    if (node->left != NULL)
    {
        traverse_tree(node->left, data, length, capacity);
    }

    append_int(data, length, capacity, node->data);

    if (node->right != NULL)
    {
        traverse_tree(node->right, data, length, capacity);
    }
}

void append_int(int **data, size_t *length, size_t *capacity, const int value)
{
    if (*length == *capacity)
    {
        *capacity *= 2;
        *data = realloc(*data, sizeof(int) * *capacity);
    }
    (*data)[(*length)++] = value;
}
