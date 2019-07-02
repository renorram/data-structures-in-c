#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

// Terrible way to clean the console window, using only for the sake of simplicity
#ifdef _WIN32
	void clear_console() { system("cls"); }
#else
	void clear_console() { system("clear"); }
#endif

enum options {opt_exit, opt_enqueue, opt_dequeue, opt_search};

void print_error(const char * msg)
{
	printf("[ERROR] %s\n", msg);
}

int get_int_input(int * value)
{
	char line[256];

	if (fgets(line, sizeof(line), stdin)) {
	    return sscanf(line, "%d", value);
	}

	return false;
}

int get_menu_input(void)
{
	char str[] = {"Options Menu:\n[0] exit\n[1] enqueue\n[2] dequeue\n[3] search\n"};
	int option;

	printf("%s\n", str);
	printf("Insert an option:\n");
	
	if (1 == get_int_input(&option)) {
		return option;
	}
	

	return false;
}

void print_queue_status(Queue *q) {
	printf("Current queue status: ");
    queue_print(q);
}

void enqueue(Queue *q) {
	int value;
	printf("Insert a value to enqueue:\n");
	if (1 == get_int_input(&value)) {
		queue_enqueue(q, value);
	} else {
		print_error("Not able to enqueue, input invalid.");
	}
}

void dequeue(Queue *q) {
	int value = queue_dequeue(q);
	if (value == false) {
		print_error("Not able to dequeue, queue is empty.");
		return;
	}

	printf("Value dequeued: %d\n", value);
}

void search(Queue *q) {
	int value, position;

	printf("Insert a value to search:\n");
	if (1 == get_int_input(&value)) {
		position = queue_search_value(q, value);

		if (position != -1) {
			printf("Value is on position %d\n", position);
		} else {
			print_error("value not found.");
		}
	} else {
		print_error("Type a valid input to search.");
	}
}

int main(void)
{
	Queue *q = queue_create();

    while(true) {
    	clear_console();
    	print_queue_status(q);

    	int option = get_menu_input();
    	if (option < opt_exit || option > opt_search) {
    		printf("%d is an invalid option.\n", option);
    		continue;
    	}

    	switch (option) {
    		case opt_exit:
    			exit(0);
    		case opt_enqueue:
    			enqueue(q);
    			break;
    		case opt_dequeue:
    			dequeue(q);
    			break;
    		case opt_search:
    			search(q);
    			break;
    	}
    	printf("Press any key to continue to menu...");
    	getchar();
    }
}