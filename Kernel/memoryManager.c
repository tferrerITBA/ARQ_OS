#include "include/memoryManager.h"
#include "include/videoMode.h"

extern pid_t getRunningProcessPid();
extern void put_char(int c);

p_block PB_HEAD = NULL;
p_block LAST = NULL;
p_block BASE = (p_block)HEAP_BASE;

void * pageAddresses[PAGE_QUANTITY];
char pageFlag[PAGE_QUANTITY];

void initializeMemoryManager() {
    initializePages();
    PB_HEAD = BASE;
    PB_HEAD->pid = 0;
    PB_HEAD->isStack = FALSE;
    PB_HEAD->address = (void *)(HEAP_BASE + PB_SIZE);
    PB_HEAD->next = NULL;
    PB_HEAD->allocated = PB_SIZE;
    pageFlag[0] = TRUE;
}

void initializePages() {
    for (int i = 0 ; i < PAGE_QUANTITY ; i++) {
        pageFlag[i] = FALSE;
        pageAddresses[i] = (void *)(HEAP_BASE + i * PAGE_SIZE);
    }
}

void * malloc(size_t size, pid_t pid) {
    if (size >= (PAGE_SIZE - BLOCK_SIZE - PB_SIZE))
		return NULL;


    p_block pb = (p_block)getProcessBlock(pid);
    m_block mb;

	if (pb == NULL) {
        pb = (p_block)addProcessBlock(pid,FALSE);

        if (pb == NULL)
			return NULL;

        pb->allocated += size + BLOCK_SIZE;
        mb = (m_block)pb->address;
        mb->free = FALSE;
        mb->size = size;
        mb->next = NULL;

        return ((char *)mb) + BLOCK_SIZE;
    }

    else {
        if (((pb->allocated + size)  > (PAGE_SIZE - BLOCK_SIZE)))
			return NULL;

        mb = (m_block)pb->address;
        m_block dataBlock = (m_block)getDataBlock(size,mb);

		if (dataBlock == NULL)
			return NULL;

        pb->allocated += size + BLOCK_SIZE;

        return (void *)dataBlock;
    }
}

m_block getDataBlock(size_t size, m_block mb) {
    m_block aux = mb;
    m_block last = mb;
    while (aux != NULL && (aux->free = FALSE || aux->size < size)) {
        last = aux;
        aux = aux->next;
        if(aux != NULL && aux->free && last->free && ((aux->size + last->size + BLOCK_SIZE ) >= size)) {
            joinDataBlocks(last,aux);
            last->free = FALSE;
            return (m_block)((char *)last + BLOCK_SIZE);
        }
    }
    m_block newBlock;
    if (aux == NULL) {
        newBlock = (m_block)((char *)last + BLOCK_SIZE + last->size);
        newBlock->free = FALSE;
        newBlock->next = NULL;
        newBlock->size = size;
    } else {
        int prevSize = aux->size;
        newBlock = aux;
        newBlock->free=FALSE;
        if (prevSize > size + BLOCK_SIZE) { //Split Block
            m_block splitBlock = (m_block)((char *)newBlock + BLOCK_SIZE + size);
            splitBlock->free = TRUE;
            splitBlock->size = prevSize - size - BLOCK_SIZE;
            splitBlock->next = newBlock->next;
            newBlock->next = splitBlock;
            newBlock->size = size;
        }
    }

    return (m_block)((char *)newBlock + BLOCK_SIZE);
}

p_block getProcessBlock(pid_t pid) {
    if(PB_HEAD == NULL)
        return NULL;

    p_block aux = PB_HEAD;
    while(aux != NULL && (aux->pid != pid || aux->isStack )) {
        aux = aux->next;
    }
    return aux;
}

p_block addProcessBlock(pid_t pid, int isStack) {

    p_block newBlock = (p_block)popPage();
    if(newBlock == NULL) return NULL;
    p_block pb = LAST;
    pb->next = newBlock;
    newBlock->pid = pid;
    newBlock->allocated = PB_SIZE;
    newBlock->isStack = isStack;
    newBlock->address = (char*)newBlock + PB_SIZE;
    newBlock->next = NULL;
    return newBlock;
}

void free(void * ptr) {
    pid_t pid = getRunningProcessPid();
    p_block pb = getProcessBlock(pid);
    if(ptr == NULL || pb == NULL) return;

    m_block mblock = (m_block)ptr - 1;
    mblock->free = TRUE;
    pb->allocated -= mblock->size;
}

void * calloc(size_t size, pid_t pid) {
    int i;
    void * ptr = malloc(size, pid);
    if(ptr != NULL) {
        for (i = 0; i < size; i++) {
            *((char *)ptr + i) = 0;
        }
    }
    return ptr;
}

void * realloc(void * ptr, size_t size, pid_t pid) {

    if(ptr == NULL || size > (PAGE_SIZE - BLOCK_SIZE)) return NULL;

    void * ret = malloc(size, pid);
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
    for(i = 0; pageFlag[i] == TRUE  ; i++) {
        if (i == PAGE_QUANTITY) return NULL;
    }
    pageFlag[i] = TRUE;
    return (void*) pageAddresses[i];
}

void * initializeProcessStack(pid_t pid) {
    p_block stack = addProcessBlock(pid,TRUE);
    return (void *)stack + PB_SIZE;
}

void * reserveHeapSpace(pid_t pid) {
    p_block heap = addProcessBlock(pid,FALSE);
    return (void *)heap + PB_SIZE;
}

void removeProcessMemory(pid_t pid) {
    clearMemory(pid,TRUE); //stack
    clearMemory(pid,FALSE); //heap
}


void clearMemory(pid_t pid, int isStack) { 
    p_block pb = PB_HEAD;
    p_block prev = NULL;

    while(pb != NULL && (pb->pid != pid || pb->isStack != isStack)) {
        prev = pb;
        pb = pb->next;
    }
    if(pb != NULL) {
        int i;
        for(i=0 ; i < PAGE_QUANTITY ; i++) {
            if(pageAddresses[i] == (void *)pb) {
                pageFlag[i] = FALSE;
            }
        }
        if (pb == PB_HEAD) {
            PB_HEAD = pb->next;   
        }
        else {
            prev->next = pb->next; 
        }
        clearBlocks(pb->address);
        pb->allocated = PB_SIZE;
    }
}

void clearBlocks(m_block mb) {
    while(mb != NULL) {
        mb->free = TRUE;
        mb = mb->next;
    }
}

void * shmget(pid_t id) {

    p_block pb = getProcessBlock(id);
    if(pb == NULL) {
        pb = addProcessBlock(id,2);
    }
    return (void *)pb + PB_SIZE;
}

void shmfree(pid_t id) {
    p_block pb = getProcessBlock(id);
    clearMemory(id,2);
}

