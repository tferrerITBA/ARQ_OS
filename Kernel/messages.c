
#include "include/messages.h"

void createMessageQueue() {
    messageQueue = newQueue(MESSAGE_SIZE);
}

void createBlockedQueue() {
    blockedQueue = newQueue(sizeof(void *));
}

void send(char * msg) {
    enqueue(messageQueue,msg);
    if(isEmpty(blockedQueue)) {
        return;
    }
    Pcb p = dequeue(blockedQueue);
    p->state = READY;
    while(1);
}

char * receive() {
    if(isEmpty(messageQueue)) {
        runningPcb->state = BLOCKED;
        while(runningPcb->state == BLOCKED);
    }
    return dequeue(messageQueue);
}
