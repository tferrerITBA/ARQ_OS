#include "include/memoryManager.h"

extern pid_t getRunningProcessPid();

//Main reference to process block Linked List
p_block PB_HEAD = NULL;
p_block LAST = NULL;
p_block BASE = (p_block)HEAP_BASE;

uint64_t pageAddresses[PAGE_QUANTITY];
char pageFlag[PAGE_QUANTITY];

//LLAMAR ESTA FUNCION CUANDO SE INICIALIZA EL PROGRAMA
void initializeMemoryManager() {

    initializePages();
    PB_HEAD = BASE;
    PB_HEAD->pid = 999;
    PB_HEAD->isStack = FALSE;
    PB_HEAD->address = (char *)HEAP_BASE + PB_SIZE;
    PB_HEAD->next = NULL;
    PB_HEAD->allocated = PB_SIZE;
    pageAddresses[0] = TRUE;

}


void initializePages() {
    int i;
    for(i = 0 ; i < PAGE_QUANTITY ; i++) {
        pageFlag[i] = FALSE;
        pageAddresses[i] = (uint64_t)(HEAP_BASE + i * PAGE_SIZE);
    }
}

void * malloc(size_t size) {

    if(size >= (PAGE_SIZE - BLOCK_SIZE - PB_SIZE)) return NULL;
    pid_t pid = getRunningProcessPid();
    p_block pb = (p_block)getProcessBlock(pid);
    m_block mb;
    if(pb == NULL) { //No process block associated with process asking for memory
        pb = (p_block)addProcessBlock(pid,FALSE);
        if(pb == NULL) return NULL;
        pb->allocated = size + BLOCK_SIZE;
        mb = (m_block)pb->address;
        mb->free = FALSE;
        mb->size = size;
        mb->next = NULL;
        return ((char *)mb) + BLOCK_SIZE;
    }

    else { //Process already mapped to a 8K page
        if(((pb->allocated + size)  > (PAGE_SIZE - BLOCK_SIZE - PB_SIZE))) return NULL;

        mb = (m_block)pb->address;
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
        newBlock = (m_block)((char *)last + BLOCK_SIZE + last->size);
        newBlock->free = FALSE;
        newBlock->next = NULL;
        newBlock->size = size;
    }
    else {
        int prevSize = aux->size;
        newBlock = aux;
        newBlock->free=FALSE;
        if(prevSize >= size + BLOCK_SIZE) { //Split Block
            m_block splitBlock = (m_block)((char *)newBlock + BLOCK_SIZE + size);
            splitBlock->free = TRUE;
            splitBlock->size = prevSize - size - BLOCK_SIZE;
            splitBlock->next = (m_block)newBlock->next;
            newBlock->next = (m_block)splitBlock;
            newBlock->size = size;
        }
    }
    return (m_block)((char *)newBlock + BLOCK_SIZE);
}

p_block getProcessBlock(pid_t pid) {
    if(PB_HEAD == NULL)
        return NULL;

    p_block aux = PB_HEAD;
    while(aux != NULL && aux->pid != pid && aux->isStack == FALSE) {
        aux = aux->next;
    }
    return aux;
}

p_block addProcessBlock(pid_t pid, int isStack) {

    if(PB_HEAD == NULL) {
        PB_HEAD = (p_block)BASE;
        PB_HEAD->pid = pid;
        PB_HEAD->allocated = PB_SIZE;
        PB_HEAD->next = NULL;
        PB_HEAD->isStack = isStack;
        PB_HEAD->address = (char*)popPage() + PB_SIZE;
        LAST = PB_HEAD;
        return PB_HEAD;
    }
    p_block newBlock = (p_block)popPage();
    p_block pb = LAST;
    if(newBlock == NULL) return NULL;
    pb->next = newBlock;
    newBlock->pid = pid;
    newBlock->allocated = PB_SIZE;
    newBlock->isStack = isStack;
    newBlock->address = (char*)newBlock + PB_SIZE;
    newBlock->isStack = FALSE;
    newBlock->next = NULL;
    return newBlock;
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

void joinDataBlocks(m_block m1, m_block m2) { 

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

void * initializeProcessStack() {//Reserva pagina de 8k para el STACK
    pid_t pid = getRunningProcessPid();
    p_block stack = addProcessBlock(pid,TRUE);
    if(stack == NULL) return NULL;
    return (char *)stack + PB_SIZE;
}

void * reserveHeapSpace(pid_t pid) { //Reserva pagina de 8k para el HEAP, can return NULL value if no page available
    return addProcessBlock(pid,FALSE);
}

void removeProcessMemory() {
    pid_t pid = getRunningProcessPid();
    removeProcessStack(pid);
    removeProcessHeap(pid);
}

void removeProcessStack(pid_t pid) {
    p_block pb = PB_HEAD;
    while(pb != NULL && (pb->pid != pid || !(pb->isStack))) {
        pb = pb->next;
    }
    if(pb != NULL) {
        for(int i=0 ; i < PAGE_QUANTITY ; i++) {
            if(pageAddresses[i] == (uint64_t)pb->address) {
                pageFlag[i] = 0;
            }
        }
        pb->pid = -1;
    }
}

void removeProcessHeap(pid_t pid) {
    p_block pb = PB_HEAD;
    while(pb != NULL && (pb->pid != pid || pb->isStack)) {
        pb = pb->next;
    }
    if(pb != NULL) {
        for(int i=0 ; i < PAGE_QUANTITY ; i++) {
            if (pageAddresses[i] == (uint64_t) pb->address) {
                pageFlag[i] = 0;
            }
        }
        pb->pid = -1;
        pb->allocated = 0;
    }
}

void * kernelMalloc(size_t size) {

    pid_t kernelPid = 999;

    p_block pb = getProcessBlock(pid);
    m_block mb = (m_block)pb->address;
    m_block newBlock = getDataBlock(size,mb);
    if(newBlock == NULL) return NULL;
    pb->allocated += size + BLOCK_SIZE;
    return (char *)dataBlock + BLOCK_SIZE;

    return NULL;
}
 









