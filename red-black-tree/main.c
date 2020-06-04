#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

#ifdef _WIN32
void clear_screen(void) {
    system("cls");
}
#endif

#ifdef __linux__

void clear_screen(void) {
    system("clear");
}

#endif

char * get_file_path() {
	char * path = malloc(sizeof(char) * 256);

	printf("Insira o caminho completo do arquivo\n");
	fgets(path, 255, stdin);

	int i;
	for (i = 0; i < 255;i++) {
		if (path[i] == '\n') {
			path[i] = '\0';
		}
	}

	return path;
}

void action_insert_range(Tree *t) {
    unsigned int a, b;
    char buffer[100], *waste;

    printf("Insira valor inicial:\n");
    fgets(buffer, 100, stdin);
    a = (int) strtol(buffer, &waste, 10);

    printf("Insira valor final:\n");
    fgets(buffer, 100, stdin);
    b = (int) strtol(buffer, &waste, 10);

    b++;
    for (; a < b; a++) {
        tree_insert(t, a);
    }
}

void action_remove_range(Tree *t) {
    unsigned int a, b;
    char buffer[100], *waste;

    printf("Insira valor inicial:\n");
    fgets(buffer, 100, stdin);
    a = (int) strtol(buffer, &waste, 10);

    printf("Insira valor final:\n");
    fgets(buffer, 100, stdin);
    b = (int) strtol(buffer, &waste, 10);

    b++;
    for (; a < b; a++) {
        tree_remove(t, a);
    }
}

void action_print_nodes_number_memory(Tree *t) {
    printf("*** QTD. NOS E TAMANHO DA ÁRVORE ***\n");
    unsigned long int tree_size = tree_get_size(t);
    printf("A árvore contém %d nós.\n", tree_count_nodes(t));
    printf("Tamanho da árvore:\n%lu bytes\n%lu kbytes\n%lu mbytes\n", tree_size, tree_size / 1024,
           (tree_size / 1024) / 1024);
}

clock_t start_measure() {
    return clock();
}

double finish_measure(clock_t start_time) {
    return ((double) (clock() - start_time)) / CLOCKS_PER_SEC;
}

void print_menu() {
    char *str = "*** Menu ***\n"
                "1) Inserir faixa de inteiros\n"
                "2) Remover faixa de inteiros\n"
                "3) Exibir numero de nos e uso de memória\n"
                "4) Salvar conteudo da arvore em arquivo\n"
                "5) é rubro negra?\n"
                "6) Limpar arvore\n"
                "7) Imprimir a arvore\n"
                "8) Sair do programa\n"
                "Digite um opção:\n";
    clear_screen();
    printf("%s", str);
}

void loop_menu(Tree *tree) {
    int option;
    char buffer[100], *waste;
    clock_t start_t;

    do {
        print_menu();
        fgets(buffer, 100, stdin);
        option = (int) strtol(buffer, &waste, 10);

        if (option < 1 || option > 8) {
            printf("%d opção invalida!\n", option);
        } else {
            start_t = start_measure();
            switch (option) {
                case 1:
                    action_insert_range(tree);
                    break;
                case 2:
                    action_remove_range(tree);
                    break;
                case 3:
                    action_print_nodes_number_memory(tree);
                    break;
                case 4:
                    tree_print_to_file(tree, get_file_path());
                    break;
                case 5:
                    printf("%s\n", tree_is_red_black(tree) ? "SIM" : "NAO");
                    break;
                case 6:
                    tree_clean(tree);
                    break;
                case 7:
                    tree_print(tree);
                    break;
                default:
                    continue;
            }
            printf("Operação levou %f segundos para executar.\n", finish_measure(start_t));
            printf("Pressione enter para continuar....");
            while (getchar() != '\n') {}
        }
    } while (option != 8);
    printf("Tchau! ;)\n");
}

int main(void) {
    Tree *t = tree_create();
    loop_menu(t);
//    int x;
//    for (x = 0;x < 10;x++) {
//        tree_insert(t, x);
//    }

//    tree_remove(t, 0);
    tree_destroy(t);
    return 0;
}
