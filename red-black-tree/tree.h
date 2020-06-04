//
// Created by renorram on 20/11/2019.
//

#ifndef RED_BLACK_TREE_TREE_H
#define RED_BLACK_TREE_TREE_H

typedef struct tree Tree;
typedef struct node Node;

Tree *tree_create();

void tree_destroy(Tree *t);

void tree_clean(Tree *t);

void tree_insert(Tree *t, unsigned int i);

void tree_remove(Tree *t, unsigned int i);

void tree_print(Tree *t);

void tree_print_to_file(Tree *t, char *filepath);

int tree_contains_number(Tree *t, unsigned int i);

int tree_black_height(Tree *t);

int tree_is_red_black(Tree *t);

unsigned int tree_count_nodes(Tree *t);

size_t tree_get_size(Tree *t);

#endif //RED_BLACK_TREE_TREE_H
