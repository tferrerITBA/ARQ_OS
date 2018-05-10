#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include "queue.h"
#include "processStates.h"
#include "PCBTADs.h"
#include "processTADs.h"
#include <stdint.h>

#define QUEUE_SIZE 10
#define TRUE 1
#define FALSE 0

#pragma pack(push)
#pragma pack(1)
typedef struct {
    uint64_t ip;
    uint64_t cs;
    uint64_t flags;
    uint64_t sp;
    uint64_t ss;
    uint64_t ip2;
    uint64_t cs2;
    uint64_t flags2;
    uint64_t sp2;
    uint64_t ss2;
    uint64_t ip3;
    uint64_t cs3;
    uint64_t flags3;
    uint64_t sp3;
    uint64_t ss3;
    uint64_t ip4;
    uint64_t cs4;
    uint64_t flags4;
    uint64_t sp4;
    uint64_t ss4;
} trapframe;
#pragma pack(pop)

void * schedule(void * rsp);
int terminateProcess(Process p);
void enqueueProcess(Pcb pcb);
void createReadyQueue();
void printStack(trapframe * tf);