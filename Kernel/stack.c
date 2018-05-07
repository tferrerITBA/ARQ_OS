#include "include/stack.h"

Stack newStack(size_t size) {
    Stack q = malloc(sizeof(stackStruct));
    q->length = 0;
    q->size = size;
    q->last = NULL;
    return q;
}

int getLength(Stack stack) {
    return stack->length;
}

int isEmpty(Stack stack) {
    return stack->length == 0;
}

void push(Stack stack, void * elem) {
    size_t assignedMemory = (stack->size);
    Element newElement = malloc(sizeof(stackElement));
    Element currentLast = stack->last;
    newElement->info = malloc(assignedMemory);
    memcpy(newElement->info, elem, assignedMemory);
    if(stack->length == 0) {
        stack->first = newElement;
    }
    newElement->previous = currentLast;
    if(currentLast != NULL) {
        currentLast->next = newElement;
    }
    stack->last = newElement;
    stack->length++;
}

void * pop(Stack stack) {
    if(isEmpty(stack)) {
        return NULL;
    }
    void * ret;
    Element lastInserted = stack->last;
    ret = lastInserted->info;
    stack->last = lastInserted->previous;
    stack->length--;
    free(lastInserted);
    return ret;
}