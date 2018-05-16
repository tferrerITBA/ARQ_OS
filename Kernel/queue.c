#include <stdlib.h>
#include "include/queue.h"
#include "include/videoMode.h"

Queue readyQueue = NULL;
Queue messageQueue = NULL;

Queue newQueue(size_t size) {
    Queue q = malloc(sizeof(queueStruct));
    q->length = 0;
    q->size = size;
    q->last = NULL;
    q->first = NULL;
    return q;
}

int getLength(Queue queue) {
    return queue->length;
}

int isEmpty(Queue queue) {
    if(queue == NULL) {
        return 1;
    }
    return getLength(queue) == 0;
}

void enqueue(Queue queue, void * elem) {
    if(queue == NULL || elem == NULL) {
        return;
    }

    Element newElement = malloc(sizeof(queueElement));
    Element currentLast = queue->last;
    newElement->info = elem;

    if(queue->length == 0) {
        queue->first = newElement;
    }
    newElement->previous = currentLast;
    if(currentLast != NULL) {
        currentLast->next = newElement;
    }
    queue->last = newElement;
    queue->length= queue->length+1;

}

void * dequeue(Queue queue) {
    if(isEmpty(queue)) {
        return NULL;
    }
    void * ret;
    Element firstElement = queue->first;
    ret = firstElement->info;
    queue->first = firstElement->next;
    queue->length = queue->length-1;
    free(firstElement);
    return ret;
}