/*
Написать программу на Си, которая принимает на стандартном входном потоке последовательность целых чисел.
Требуется отсортировать эти числа и распечатать в убывающем порядке эти числа и
частоты их встречаемости во входной последовательности.
Для хранения чисел использовать бинарное дерево.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    struct Node *left, *right;
    int val;
    unsigned count;
} Node;

Node* add_node(Node* tree, int val) {
    if (!tree) {
        tree = calloc(1, sizeof(*tree));
        tree->val = val;
        ++tree->count;
        return tree;
    }
    if (val < tree->val) {
        tree->left = add_node(tree->left, val);
    } else if (val > tree->val) {
        tree->right = add_node(tree->right, val);
    } else {
        ++tree->count;
    }
    return tree;
}

void print_tree(Node* tree) {
    if (!tree) {
        return;
    }
    print_tree(tree->right);
    printf("%d: %u\n", tree->val, tree->count);
    print_tree(tree->left);
}

int main() {
    Node* tree = NULL;
    int x;
    while (scanf("%d", &x) == 1) {
        tree = add_node(tree, x);
    }
    print_tree(tree);

    return 0;
}
