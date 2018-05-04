#ifndef ARQ_OS_MEMORYMANAGER_H
#define ARQ_OS_MEMORYMANAGER_H

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define PAGE_SIZE 0x1000
#define HEAP_BASE 0x400000
#define HEAP_LIMIT 0x799999
#define PAGE_QUANTITY ((HEAP_END - HEAP_START)/PAGE_SIZE)
#define TRUE 1
#define FALSE 0



typedef struct processBlock * p_block;
struct processBlock {   //Bloque que inidica owner de dicha pagina
    pid_t owner_pid;
    p_block * next;
    size_t allocated;
    void * mem_address;
};

typedef struct memBlock * m_block;
struct memBlock {   //Bloque de memoria pedido por un proceso
    int free; // 0 used, 1 free
    m_block next;
    size_t size;
};

#endif //ARQ_OS_MEMORYMANAGER_H
