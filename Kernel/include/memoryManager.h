#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define PAGE_SIZE 0x1000
#define PAGE_QUANTITY ((HEAP_LIMIT - HEAP_BASE)/PAGE_SIZE)
#define TRUE 1
#define FALSE 0

void * HEAP_BASE = (void *)0x400000;
void * HEAP_LIMIT = (void *)0x799999;


void initializePages();
void * malloc(size_t size);
pid_t getpid();
void * malloc(size_t size);
m_block getDataBlock(size_t size, m_block mb);
p_block getProcessBlock(pid_t pid);
p_block addProcessBlock(pid_t pid);
void free(void * ptr);
void * calloc(size_t size);
void * realloc(void * ptr, size_t size);
void joinDataBlocks(m_block m1, m_block m2);
void popPage();

typedef struct processBlock * p_block;
struct processBlock {   //Bloque que inidica owner de dicha pagina
    pid_t pid;
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

