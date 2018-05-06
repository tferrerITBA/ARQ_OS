#include "memoryManager.h"
#define BLOCK_SIZE sizeof(struct memBlock)
#define PB_SIZE sizeof(struct processBlock)

//Main reference to process block Linked List
p_block PB_HEAD = NULL;
p_block BASE = HEAP_BASE;

u_int64_t pageAddresses[PAGE_QUANTITY];
char pageFlag[PAGE_QUANTITY];

void initializeMemoryManager() {

    initializePages();
    p_block firstBlock = (p_block) HEAP_BASE;
    firstBlock->pid = 0;
    firstBlock->mem_address = popPage();
    firstBlock->next = NULL;
    firstBlock->allocated = PB_SIZE;

    PB_HEAD = firstBlock;
}

void initializePages() {
    int i;
    for(i = 0 ; i < PAGE_QUANTITY ; i++) {
        pageFlag[i]=0;
        pageAddresses[i] = (u_int64_t)(HEAP_BASE + i * PAGE_SIZE);
    }
}

pid_t getpid() { //returns pid of current process
    return 0;
}

void * malloc(size_t size) {

    if(size >= (PAGESIZE - BLOCK_SIZE)) return NULL;
    pid_t pid = getpid(); //Get pid corresponding to process asking for memory

    p_block pb = (p_block)getProcessBlock(pid);
    m_block mb;
    if(pb == NULL) { //No process block associated with process asking for memory
        pb = (p_block)addProcessBlock(pid);
        if(pb == NULL) return NULL;
        pb->allocated = size + BLOCK_SIZE;

        mb = (mem_block)pb->address;
        mb->free = FALSE;
        mb->size = size;
        mb->next = NULL;
        return ((char *)mb) + BLOCK_SIZE;
    }

    else { //Process already mapped to a 4K page
        if(((pb->allocated + size)  > (PAGESIZE - BLOCK_SIZE))) return NULL;

        mb = (m_block)pb->mem_address;
        m_block dataBlock =(m_block)getDataBlock(size,mb);
        if(dataBlock == NULL) return NULL;
        pb->allocated += size + BLOCK_SIZE;
        return (((char *)dataBlock) + BLOCK_SIZE);
    }
}

m_block getDataBlock(size_t size, m_block mb) {

    m_block aux = mb;
    m_block last = mb;
    while(aux != NULL && (aux->free = FALSE || aux->size < size)) {

        last = aux;
        aux = aux->next;
        if(aux != NULL && aux->free && last->free && ((aux->size + last->size + BLOCK_SIZE ) >= size)) {
            joinDataBlocks(last,aux);
            last->free = FALSE;
            return (m_block)((char *)last + BLOCK_SIZE);
        }
    }
    m_block newBlock;

    if(aux == NULL) {
        newBlock = ((char *)last + BLOCK_SIZE + last->size);
        newBlock->free = FALSE;
        newBlock->next = NULL;
        newBlock->size = size;
    }
    else {
        int prevSize = aux->size;

        newBlock = aux;
        newBlock->free=FALSE;

        if(prevSize >= size + BLOCK_SIZE) { //Split Block
            m_block splitBlock = ((char *)newBlock + BLOCK_SIZE + size);
            splitBlock->free = TRUE;
            splitBlock->size = prevSize - size - BLOCK_SIZE;
            splitBlock->next = (mem_block)newBlock->next;
            newBlock->next = (mem_block)splitBlock;
            newBlock->size = size;
        }
    }

    return ((char *)newBlock + BLOCK_SIZE);
}

p_block getProcessBlock(pid_t pid) {

    if(PB_HEAD == NULL) return NULL;

    p_block aux = PB_HEAD;
    while(aux != NULL && aux->pid != pid) {
        aux = aux->next;
    }
    return aux;
}

p_block addProcessBlock(pid_t pid) {

    if(PB_HEAD == NULL) {
        PB_HEAD = (p_block) BASE;
        PB_HEAD->pid = pid;
        PB_HEAD->allocated = 0;
        PB_HEAD->next = NULL;
        PB_HEAD->mem_address = popPage();

        return PB_HEAD;
    }

    else  {
        p_block auxPb = PB_HEAD;
        p_block temp = NULL;
        while(auxPb != NULL) {
            temp = auxPb;
            auxPb = auxPb->next;
        }
        p_block newblock = (p_block)(((char*)temp + PB_SIZE));
        temp->next = newblock;
        newblock->pid = pid;
        newblock->allocated = 0;
        newblock->next = NULL;
        newblock->mem_address = popPage();

        return newblock;
    }
}

void free(void * ptr) {

    pid_t pid = getpid();
    p_block pb = getProcessBlock(pid);
    if(ptr == NULL || pb == NULL) return;

    m_block mblock = (m_block)ptr - 1;
    mblock->free = TRUE;
    pb->allocated -= mblock->size;

}

void * calloc(size_t size) {

    void * ptr = malloc(size);
    if(ptr != NULL) {
        for (int i = 0; i < size; i++) {
            *((char *)ptr + i) = 0;
        }
    }
    return ptr;
}

void * realloc(void * ptr, size_t size) {

    if(ptr == NULL || size > (PAGE_SIZE - BLOCK_SIZE)) return NULL;

    void * ret = malloc(size);
    if(ret == NULL) return NULL;
    m_block memBlock = (m_block) ptr - 1;

    memcpy(ret,ptr,memBlock->size);

    return ret;
}

void joinDataBlocks(m_block m1, m_block m2) { //Join two contiguous memory blocks to form a bigger one

    m1->size += m2->size + BLOCK_SIZE;
    m1->next = m2->next;
    return;
}

void * popPage() {
    int i;
    for(i = 0; pageFlag[i]  ; i++) {
        if (i == PAGE_QUANTITY) return NULL;
    }
    pageFlag[i] = TRUE;
    return (void*) pageAddresses[i];
}
/*
void removeProcessBlock(pid_t pid) {

    if(pid < 0) return;
    p_block pb = PB_HEAD;
    p_block last = null;

    while(pb != NULL && pb->pid != pid) {
        last = pb;
        pb = pb->next;
    }
    if(pb == NULL) return;





    p_block

}
 */









