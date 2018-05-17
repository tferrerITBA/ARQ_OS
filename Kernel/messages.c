
#include "include/messages.h"
#include "include/queue.h"
#include "include/pcb.h"
#include "include/process.h"
#include "include/videoMode.h"

void createMessageQueue() {
    messageQueue = newQueue(MESSAGE_SIZE);
}

void createBlockedQueue() {
    blockedQueue = newQueue(sizeof(void *));
}

void send(char * msg) {
    putString("Encolando mensaje\n");
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
        putString("Me bloquie\n");
        while(runningPcb->state == BLOCKED){
            putString("Me bloquie\n");
            putString("Me hola\n");
        }
        putString("Me dbloquie\n");
    }
    return dequeue(messageQueue);
}
