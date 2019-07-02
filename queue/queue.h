#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue Queue;

Queue *queue_create();

void queue_destroy(Queue *q);

void queue_enqueue(Queue *q, int value);

int queue_dequeue(Queue *q);

int queue_size(Queue *q);

int queue_search_value(Queue *q, int value);

void queue_print(Queue *q);

void queue_invert(Queue *q);

#endif //QUEUE_H