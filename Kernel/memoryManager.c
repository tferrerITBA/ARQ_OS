#include "memoryManager.h"

//Stack containing page addresses
stackADT stack = NULL;
//Main reference to process block Linked List
p_block PB_HEAD = NULL;

p_block BASE = HEAP_BASE;

//CUANDO SE TERMINA UN PROCESO HAY QUE ENCARGARSE DE PUSHEAR AL STACK LA PAGINA QUE SE ESTABA USANDO

void initializePageStack() {
    int i;
    for(i = 0 ; i < PAGE_QUANTITY ; i++) {
        void * page_address = baseAddress + i * PAGE_SIZE;
        stack = push(stack,page);
    }
}

pid_t getpid() { //returns pid of current process
    return 0;
}

void * malloc(size_t size) {

    if(size >= (PAGESIZE - sizeof(struct memBlock))) return NULL;
    pid_t pid = getpid(); //Get pid corresponding to process asking for memory

    p_block pb = getProcessBlock(pid);
    if(pb == NULL) { //No process block associated with process asking for memory
        pb = addProcessBlock(pid);
        pb->allocated = size;
        m_block mem_block = pb->address;
        mem_block->free = FALSE;
        mem_block->size = size;
        mem_block->next = NULL;

    }

    else { //Process already mapped to a 4K page

        if(PAGE_SIZE < (pb->allocated + size) ) return NULL;

        m_block mb = (m_block) pb->address;
        m_block dataBlock = getDataBlock(size,mb);
        if(dataBlock != NULL) pb->allocated += size;
        return (void *)(dataBlock + sizeof(struct memBlock));

    }

}

m_block getDataBlock(size_t size, m_block mb) {

    //get a Data Block that has size available space

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
        PB_HEAD->mem_address = pop(stack);

        return PB_HEAD;
    }

    else  {
        p_block auxPb = PB_HEAD;
        p_block temp = NULL;
        while(auxPb != NULL) {
            temp = auxPb;
            auxPb = auxPb->next;
        }
        p_block newblock = temp + sizeof(struct memBlock);
        temp->next = newblock;
        newblock->pid = pid;
        newblock->allocated = 0;
        newblock->next = NULL;
        newblock->mem_address = pop(stack);

        return newblock;

    }

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

    //TODO

    return NULL;
}

void joinDataBlocks() { //Join two contiguous memory blocks to form a bigger one

    //TODO

    return;
}









