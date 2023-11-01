#include "binary_trees.h"

/**
 * heapify_down - Fix the Max Heap property by moving a node down
 * @node: Pointer to the node to be moved down
 */
void heapify_down(heap_t **node)
{
    heap_t *largest, *temp;

    largest = *node;

    if ((*node)->left && (*node)->left->n > largest->n)
        largest = (*node)->left;
    if ((*node)->right && (*node)->right->n > largest->n)
        largest = (*node)->right;

    if (largest != *node)
    {
        temp = *node;
        *node = largest;
        if (largest->left == largest)
            largest->left = temp;
        else
            largest->right = temp;
        heapify_down(&largest);
    }
}

/**
 * get_tree_height - Get the height of a binary tree
 * @tree: Pointer to the root node of the tree
 * Return: Height of the tree
 */
int get_tree_height(const heap_t *tree)
{
    if (!tree)
        return (0);
    return (1 + get_tree_height(tree->left));
}

/**
 * get_last_node - Get the last node in a binary tree at the last level
 * @tree: Pointer to the root node of the tree
 * @height: Height of the tree
 * @level: Current level
 * Return: Pointer to the last node, or NULL if not found
 */
heap_t *get_last_node(heap_t *tree, int height, int level)
{
    heap_t *left, *right;

    if (!tree)
        return (NULL);

    if (height == level)
        return (tree);

    left = get_last_node(tree->left, height, level + 1);
    right = get_last_node(tree->right, height, level + 1);

    if (right)
        return (right);
    return (left);
}

/**
 * heap_extract - Extract the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * Return: Value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
    heap_t *last_node, *temp;
    int value;

    if (!root || !*root)
        return (0);

    value = (*root)->n;

    last_node = get_last_node(*root, get_tree_height(*root), 0);

    if (*root == last_node)
    {
        free(*root);
        *root = NULL;
        return (value);
    }

    temp = *root;
    *root = last_node;
    if (temp->parent->left == temp)
        temp->parent->left = NULL;
    else
        temp->parent->right = NULL;

    heapify_down(root);

    free(temp);

    return (value);
}

