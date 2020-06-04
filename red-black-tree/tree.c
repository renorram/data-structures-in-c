//
// Created by renorram on 20/11/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include "tree.h"

#define RED 1
#define BLACK 2

struct tree {
    Node *root;
    Node *null;
    unsigned int node_number;
};

struct node {
    Node *father;
    Node *left;
    Node *right;
    uint8_t color;
    unsigned int info;
};

Node *tree_create_node(unsigned int i, Node *null) {
    Node *n = malloc(sizeof(Node));
    n->father = null;
    n->left = null;
    n->right = null;
    n->info = i;
    n->color = RED;

    return n;
}

Tree *tree_create() {
    Tree *t = malloc(sizeof(Tree));
    Node *null = malloc(sizeof(Node));
    null->father = null;
    null->left = null;
    null->right = null;
    null->info = -1;
    null->color = BLACK;

    t->null = null;
    t->root = null;
    t->node_number = 0;

    return t;
}

void tree_destroy_recursive(Node *root, Node *null) {
    if (root != null) {
        tree_destroy_recursive(root->right, null);
        tree_destroy_recursive(root->left, null);
        free(root);
    }
}

void tree_destroy(Tree *t) {
    tree_destroy_recursive(t->root, t->null);
    free(t->null);
    free(t);
}

void tree_clean(Tree *t) {
    tree_destroy_recursive(t->root, t->null);
    t->node_number = 0;
    t->root = t->null;
}

void tree_rotate_left(Tree *t, Node *node) {
    Node *aux = node->right, *null = t->null;
    // resolve node right
    node->right = aux->left;
    // fix father of aux left subtree
    if (aux->left != null) {
        aux->left->father = node;
    }

    // new aux father is node father
    aux->father = node->father;
    // if father is null then aux is the new root
    if (node->father == null) {
        t->root = aux;
    } else if (node == node->father->left) { // fix the father pointing in case father is not null
        node->father->left = aux;
    } else {
        node->father->right = aux;
    }

    // fix aux and node pointing
    aux->left = node;
    node->father = aux;
}

void tree_rotate_right(Tree *t, Node *node) {
    Node *aux = node->left, *null = t->null;
    // resolve node left
    node->left = aux->right;
    // fix father of aux right subtree
    if (aux->right != null) {
        aux->right->father = node;
    }

    // new aux father is node father
    aux->father = node->father;
    // if father is null then aux is the new root
    if (node->father == null) {
        t->root = aux;
    } else if (node == node->father->left) { // fix the father pointing in case father is not null
        node->father->left = aux;
    } else {
        node->father->right = aux;
    }

    // fix aux and node pointing
    aux->right = node;
    node->father = aux;
}

void tree_insert(Tree *t, unsigned int i) {
    Node *null = t->null, *root = t->root, *father = null;

    while (root != null) {
        // ignore repeated values
        if (root->info == i)
            return;

        father = root;
        root = i > root->info ? root->right : root->left;
    }

    root = tree_create_node(i, null);
    root->father = father;

    if (father == null) {
        t->root = root;
    } else {
        if (root->info > father->info) {
            father->right = root;
        } else {
            father->left = root;
        }
    }

    // increase the node count
    t->node_number++;

    Node *grandpa;
    while (root->father->color == RED) {
        grandpa = root->father->father;
        // if the father is a son on the left
        if (root->father == grandpa->left) {
            // if uncle is red, invert colors, because father and uncle are red
            if (grandpa->right->color == RED) {
                root->father->color = BLACK;
                grandpa->right->color = BLACK;
                grandpa->color = RED;
                root = grandpa;
            } else {
                // if root is right, first rotate to left
                if (root == root->father->right) {
                    root = root->father;
                    tree_rotate_left(t, root);
                }

                root->father->color = BLACK;
                root->father->father->color = RED;
                tree_rotate_right(t, root->father->father);
            }
        } else {
            // if uncle is red, invert colors, because father and uncle are red
            if (grandpa->left->color == RED) {
                root->father->color = BLACK;
                grandpa->left->color = BLACK;
                grandpa->color = RED;
                root = grandpa;
            } else {
                // if root is left, first rotate to right
                if (root == root->father->left) {
                    root = root->father;
                    tree_rotate_right(t, root);
                }

                root->father->color = BLACK;
                root->father->father->color = RED;
                tree_rotate_left(t, root->father->father);
            }
        }

        root = root->father;
    }

    // fix property 2
    t->root->color = BLACK;
}

Node *tree_minimum(Node *node, Node *null) {
    while (node->left != null) {
        node = node->left;
    }

    return node;
}

void tree_transplant(Tree *t, Node *old, Node *new) {
    if (old->father == NULL) {
        old->father = t->null;
    }

    Node *father = old->father;
    if (old->father == t->null) {
        t->root = new;
    } else if (father->left == old) {
        father->left = new;
    } else {
        father->right = new;
    }

    new->father = old->father;
}

void tree_remove_fixup(Tree *t, Node *node) {
    Node *null = t->null, *father, *brother;

    while (node != null && node->color == BLACK) {
        // node is son on the left
        father = node->father;
        if (node == father->left) {
            brother = father->right;
            // brother is red, case 1
            if (brother->color == RED) {
                brother->color = BLACK;
                father->color = RED;
                tree_rotate_left(t, father);

                brother = father->right;
            }

            // brother is black and child's are black
            if (brother->left->color == BLACK && brother->right->color == BLACK) {
                brother->color = RED;
                node = node->father;
            } else if (brother->right->color == BLACK) {
                brother->left->color = BLACK;
                brother->color = RED;
                tree_rotate_right(t, brother);
                brother = father->right;
            }

            brother->color = node->father->color;
            node->father->color = BLACK;
            brother->right->color = BLACK;
            tree_rotate_left(t, node->father);
            node = t->root;
        } else {
            brother = father->left;
            // brother is red, case 1
            if (brother->color == RED) {
                brother->color = BLACK;
                father->color = RED;
                tree_rotate_right(t, father);

                brother = father->left;
            }
            // brother is black and child's are black
            if (brother->left->color == BLACK && brother->right->color == BLACK) {
                brother->color = RED;
                node = node->father;
            } else if (brother->left->color == BLACK) {
                brother->right->color = BLACK;
                brother->color = RED;
                tree_rotate_left(t, brother);
                brother = father->left;
            }

            brother->color = node->father->color;
            node->father->color = BLACK;
            brother->left->color = BLACK;
            tree_rotate_right(t, node->father);
            node = t->root;
        }
    }

    node->color = BLACK;
}

void tree_remove(Tree *t, unsigned int i) {
    Node *root = t->root, *aux, *aux2, *null = t->null;
    unsigned int aux_original_color;

    while (root != null && root->info != i) {
        root = i > root->info ? root->right : root->left;
    }

    if (root == null) {
        printf("valor nao encontrado! %d\n", i);
        return;
    } else {
        // AUX2 will be used to analyze and fix
        aux = root;
        aux_original_color = aux->color;
        if (root->left == null) {
            aux2 = root->right;
            // transplant the right tree to the father
            tree_transplant(t, root, root->right);
        } else if (root->right == null) {
            aux2 = root->left;
            // transplant the left tree to the father
            tree_transplant(t, root, root->left);
        } else {
            aux = tree_minimum(root->right, t->null);
            aux_original_color = aux->color;
            aux2 = aux->right;

            if (aux->father == root) {
                aux2->father = aux;
            } else {
                tree_transplant(t, aux, aux->right);
                aux->right = root->right;
                aux->right->father = aux;
            }

            tree_transplant(t, root, aux);
            aux->left = root->left;
            aux->left->father = aux;
            aux->color = root->color;
        }

        if (aux_original_color == BLACK) {
            tree_remove_fixup(t, aux2);
        }

        free(aux);
    }
}

void tree_print_recursive(Node *root, Tree *t) {
    if (root != t->null) {
        tree_print_recursive(root->left, t);
        printf("\t%d, %s\n", root->info, root->color == BLACK ? "black" : "red");
        tree_print_recursive(root->right, t);
    }
}

void tree_print(Tree *t) {
    printf("******\tImprimindo\t******\n");
    tree_print_recursive(t->root, t);
    printf("**************************\n");
}

void tree_print_to_file_recursive(Node *root, Node *null, FILE *file) {
    if (root != null) {
        tree_print_to_file_recursive(root->left, null, file);
        fprintf(file, "%d\n", root->info);
        tree_print_to_file_recursive(root->right, null, file);
    }
}

void tree_print_to_file(Tree *t, char *filepath) {
    FILE *file = fopen(filepath, "w+");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", strerror(errno));
        exit(errno);
    }

    tree_print_to_file_recursive(t->root, t->null, file);
    fclose(file);
   free(filepath); 
}

int tree_contains_number(Tree *t, unsigned int i) {
    Node *root = t->root, *null = t->null;
    while (root != null && root->info != i) {
        root = i > root->info ? root->right : root->left;
    }

    return root != null ? 1 : 0;
}

int tree_black_height_recursive(Node *root, Node *null) {
    if (root != null) {
        int left = tree_black_height_recursive(root->left, null);
        int right = tree_black_height_recursive(root->right, null);

        return (root->color == BLACK ? 1 : 0) + (left > right ? left : right);
    }

    return 1;
}

int tree_black_height(Tree *t) {
    // - 1 because root must be always black and start count from zero
    return tree_black_height_recursive(t->root, t->null) - 1;
}

int tree_is_red_black_recursive(Node *root, Node *null) {
    if (root != null) {
        if (root->color == RED && root->father->color == RED) {
            return 0;
        }

        if (tree_black_height_recursive(root->left, null) != tree_black_height_recursive(root->right, null)) {
            return 0;
        }


        int right_is_rb = tree_is_red_black_recursive(root->right, null);
        int left_is_rb = tree_is_red_black_recursive(root->left, null);

        return right_is_rb && left_is_rb;
    }

    return 1;
}

int tree_is_red_black(Tree *t) {
    if (t->root == t->null) {
        return 0;
    }

    if (t->root->color == RED) {
        return 0;
    }

    return tree_is_red_black_recursive(t->root, t->null);
}

unsigned int tree_count_nodes(Tree *t) {
    return t->node_number;
}

size_t tree_get_size(Tree *t) {
    // counting plus one because there is a sentinel for null values.
    return sizeof(Tree) + (sizeof(Node) * (t->node_number + 1));
}
