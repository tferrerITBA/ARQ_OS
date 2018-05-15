#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <assert.h>
//#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include "lib.h"
#define PAGE_SIZE 8192
#define PAGE_QUANTITY ((HEAP_LIMIT - HEAP_BASE)/PAGE_SIZE)
#define BLOCK_SIZE sizeof(struct memBlock)
#define PB_SIZE sizeof(struct processBlock)
#define TRUE 1
#define FALSE 0
#define HEAP_BASE 0x600000
#define HEAP_LIMIT 0x799999

typedef struct processBlock * p_block;
struct processBlock {
    pid_t pid;
    int isStack;
    p_block next;
    size_t allocated;
    void * address;
};

typedef struct memBlock * m_block;
struct memBlock {
    int free;
    m_block next;
    size_t size;
};

void initializeMemoryManager();
void initializePages();
void * malloc(size_t size, pid_t pid);
m_block getDataBlock(size_t size, m_block mb);
p_block getProcessBlock(pid_t pid);
p_block addProcessBlock(pid_t pid,int isStack);
void free(void * ptr);
void * calloc(size_t size, pid_t pid);
void * realloc(void * ptr, size_t size, pid_t pid);
void joinDataBlocks(m_block m1, m_block m2);
void * popPage();
void * initializeProcessStack(pid_t pid);
void * reserveHeapSpace(pid_t pid);
void removeProcessMemory(pid_t pid);
void removeProcessStack(pid_t pid);
void removeProcessHeap(pid_t pid);
void clearBlocks(m_block mb);
void clearMemory(pid_t pid, int isStack);
void * shmget(pid_t id);
void shmfree(pid_t id);

#endif
