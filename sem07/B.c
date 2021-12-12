/*
<Продолжение задачи A.c>
Написать программу на Си, которая принимает на стандартном входном потоке несколько последовательностей целых чисел.
Каждая последовательность оканчивается значением 0, которое формально в эту последовательность не входит.

Для каждой последовательности требуется отсортировать ее числа и распечатать в убывающем порядке эти числа, а также
частоты их встречаемости в этой последовательности.
Для хранения чисел каждой последовательности использовать бинарное дерево.
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

Node* free_tree(Node* tree) {
    if (!tree) {
        return NULL;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
    return NULL;
}

int main() {
    Node* tree = NULL;
    int x;
    while (1) {
        int status;
        status = scanf("%d", &x);
        if (status == EOF) {
            break;
        }
        if (status == 0) {
            continue;
        }
        if (x == 0) {
            print_tree(tree);
            tree = free_tree(tree);
        } else {
            tree = add_node(tree, x);
        }
    }
    if (x) {
        print_tree(tree);
        tree = free_tree(tree);
    }
    return 0;
}
