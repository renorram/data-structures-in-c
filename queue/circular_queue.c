#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

#define MAX_ITEMS 11

struct queue {
    int itens[MAX_ITEMS];
    unsigned int start;
    unsigned int end;
};

Queue *queue_create()
{
	Queue *q = malloc(sizeof(Queue));
	q->start = 0;
	q->end = 0;

	return q;
}

void queue_destroy(Queue *q)
{
	if (q != NULL){
		free(q);
	}
}

void queue_enqueue(Queue *q, int value)
{
	if (queue_size(q) == MAX_ITEMS - 1) {
		printf("Not able to enqueue %d, The queue is full.\n", value);
		return;
	}

	q->itens[q->end] = value;
	q->end = (q->end + 1) % MAX_ITEMS;
}

int queue_dequeue(Queue *q)
{
	if (queue_size(q) == 0) {
		printf("Not able to dequeue, Queue is empty.\n");
		return false;
	}

	int current_value = q->itens[q->start];
	q->start = (q->start + 1) % MAX_ITEMS;

	return current_value;
}

int queue_size(Queue *q)
{
	return q->end >= q->start ? q->end - q->start : MAX_ITEMS - q->start + q->end;
}

int queue_search_value(Queue *q, int value)
{
	if (queue_size(q) == 0) {
		printf("Not able to search, Queue is empty.\n");
		return -1;
	}

	unsigned int i;
	for (i = q->start; i != q->end; i = (i + 1) % MAX_ITEMS)
	{
		if (q->itens[i] == value) {
			return i;
		}
	}

	return -1;
}

void queue_print(Queue *q)
{
	if (queue_size(q) == 0) {
		printf("Not able to print, Queue is empty.\n");
		return;
	}

	printf("\n[");
	unsigned int i;
	for (i = q->start; i != q->end; i = (i + 1) % MAX_ITEMS)
	{
		printf(" %d ", q->itens[i]);
	}

	printf("]\n");
}

void queue_invert(Queue *q)
{
	int size = queue_size(q);
	if (size == 0) {
		printf("Not able to invert, Queue is empty.\n");
		return;
	}

	int i, inversions = size / 2,
	aux, start = q->start, end = q->end - 1;

	for (i = 0; i < inversions; i++)
	{
		aux = q->itens[start];
		q->itens[start] = q->itens[end];
		q->itens[end] = aux;

		start = (start + 1) % MAX_ITEMS;
		end = (end - 1) % MAX_ITEMS;
	}
}
