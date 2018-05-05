#include "memoryManager.h"
#define BLOCK_SIZE sizeof(struct memBlock)
#define PB_SIZE sizeof(struct processBlock)


//Main reference to process block Linked List
p_block PB_HEAD = NULL;
p_block BASE = HEAP_BASE;

u_int64_t pageAddresses[PAGE_QUANTITY];
char pageFlag[PAGE_QUANTITY];

//CUANDO SE TERMINA UN PROCESO HAY QUE ENCARGARSE DE PUSHEAR AL STACK LA PAGINA QUE SE ESTABA USANDO

void initializePages() {
    for(int i = 0 ; i < PAGE_QUANTITY ; i++) {
        pageFlag[i]=0;
        pageDirArray[i] = (u_int64_t)(HEAP_BASE + i * PAGE_SIZE);
    }
}

pid_t getpid() { //returns pid of current process
    return 0;
}

void * malloc(size_t size) { //CHECKED, LOOKS GOOD

    if(size >= (PAGESIZE - BLOCK_SIZE)) return NULL;
    pid_t pid = getpid(); //Get pid corresponding to process asking for memory

    p_block pb = getProcessBlock(pid);
    mem_block mb;
    if(pb == NULL) { //No process block associated with process asking for memory
        pb = addProcessBlock(pid);
        if(pb == NULL) return NULL;
        pb->allocated = size + BLOCK_SIZE;

        m_block mb = (mem_block)pb->address;
        mb->free = FALSE;
        mb->size = size;
        mb->next = NULL;
        return ((char *)mb) + BLOCK_SIZE;
    }

    else { //Process already mapped to a 4K page
        if(((pb->allocated + size)  > (PAGESIZE - BLOCK_SIZE))) return NULL;

        m_block mb = (m_block) pb->address; //start of page
        m_block dataBlock = getDataBlock(size,mb);
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
        newBlock = ((char *)((char *)last + BLOCK_SIZE + last->size));
        newBlock->free = FALSE;
        newBlock->next = NULL;
        newBlock->size = size;
    }
    else {
        int prevSize = aux->size;

        newBlock = aux;
        newBlock->free=FALSE;

        if(prevSize >= size + BLOCK_SIZE) { //Split Block
            mem_block splitBlock =((char *)((char *)newBlock + BLOCK_SIZE + size));
            splitBlock->free = TRUE;
            splitBlock->size = prevSize - size - BLOCK_SIZE;
            splitBlock->next = (mem_block)newBlock->next;
            newBlock->next = (mem_block)splitBlock;
            newBlock->size = size;
        }
    }

    return (char *)((char *)newBlock + BLOCK_SIZE);
}

p_block getProcessBlock(pid_t pid) { //CHECKED

    if(PB_HEAD == NULL) return NULL;

    p_block aux = PB_HEAD;
    while(aux != NULL && aux->pid != pid) {
        aux = aux->next;
    }
    return aux;
}

p_block addProcessBlock(pid_t pid) { //CHECKED, LOOKING GOOOD

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

    void * mem_ptr = malloc(size);
    if(mem_ptr != NULL) {
        for (int i = 0; i < size; i++) {
            *(ptr + i) = 0;
        }
    }
    return mem_ptr;
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

void popPage() {

    for(int i = 0; pageFlag[i]  ; i++) {
        if (i == PAGE_QUANTITY) return NULL;
    }
    pageFlag[i] = TRUE;
    return (void*) pageAddresses[i];
}









