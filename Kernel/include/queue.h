#include <stddef.h>
typedef struct queueStruct {
    struct queueElement * first;
    struct queueElement * last;
    int length;
    size_t size;
} queueStruct;


typedef queueStruct * Queue;

typedef struct queueElement {
    void * info;
    struct queueElement * next;
    struct queueElement * previous;
} queueElement;

typedef struct queueElement * Element;

extern Queue readyQueue;

Queue newQueue(size_t size);
int isEmpty(Queue queue);
int getLength(Queue queue);
void enqueue(Queue queue, void * elem);
void * dequeue(Queue queue);

