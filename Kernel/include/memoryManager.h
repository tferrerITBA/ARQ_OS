#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#define PAGE_SIZE 8192
#define PAGE_QUANTITY ((HEAP_LIMIT - HEAP_BASE)/PAGE_SIZE)
#define BLOCK_SIZE sizeof(struct memBlock)
#define PB_SIZE sizeof(struct processBlock) 
#define TRUE 1
#define FALSE 0
#define HEAP_BASE 0x400000
#define HEAP_LIMIT 0x799999


typedef struct processBlock * p_block;
struct processBlock {   //Bloque que inidica owner de dicha pagina
    pid_t pid;
    int isStack;
    p_block next;
    size_t allocated;
    void * address;
};

typedef struct memBlock * m_block;
struct memBlock {   //Bloque de memoria pedido por un proceso
    int free; 
    m_block next;
    size_t size;
};

void initializeMemoryManager();
void initializePages();
void * malloc(size_t size);
void * kernelMalloc(size_t size);
m_block getDataBlock(size_t size, m_block mb);
p_block getProcessBlock(pid_t pid);
p_block addProcessBlock(pid_t pid,int isStack);
void free(void * ptr);
void * calloc(size_t size);
void * realloc(void * ptr, size_t size);
void joinDataBlocks(m_block m1, m_block m2);
void * popPage();
void * initializeProcessStack();
void * reserveHeapSpace(pid_t pid);
void removeProcessMemory();
void removeProcessStack(pid_t pid);
void removeProcessHeap(pid_t pid);
