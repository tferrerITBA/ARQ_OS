#include <stdlib.h>
#include "include/queue.h"
#include "include/videoMode.h"

Queue readyQueue = NULL;

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
    return queue->length == 0;
}

void enqueue(Queue queue, void * elem) {
    if(queue == NULL || elem == NULL) {
        return;
    }
    putString("Element enqueued: ");
    printHex(elem);
    put_char('\n');
    Element newElement = malloc(sizeof(queueElement));
    Element currentLast = queue->last;
    newElement->info = elem;
    putString("Element enqueued: ");
    printHex(newElement->info);
    put_char('\n');

    if(queue->length == 0) {
        queue->first = newElement;
    }
    newElement->previous = currentLast;
    if(currentLast != NULL) {
        currentLast->next = newElement;
    }
    queue->last = newElement;
    queue->length= queue->length+1;

    putString("First element: ");
    printHex(queue->first->info);
    put_char('\n');
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
    putString("Element dequeued: ");
    printHex(ret);
    put_char('\n');
    return ret;
}