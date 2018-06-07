#include "include/idtLoader.h"


void load_idt() {

    setup_IDT_entry(0x20, (uint64_t) &_irq00Handler);
    setup_IDT_entry(0x00, (uint64_t) &_exception0Handler);
    setup_IDT_entry(0x06, (uint64_t) &_exception6Handler);
    setup_IDT_entry(0x21, (uint64_t) &_irq01Handler);
    setup_IDT_entry(0x80, (uint64_t) &_int80Handler);

    //Solo interrupcion timer tick  y teclado habilitadas
    picMasterMask(0xFC); // 1111 1100
    picSlaveMask(0xFF);

    _sti();
}

static void setup_IDT_entry(int index, uint64_t offset) {
    idt[index].selector = 0x08;
    idt[index].offset_l = offset & 0xFFFF;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
    idt[index].access = ACS_INT;
    idt[index].cero = 0;
    idt[index].other_cero = (uint64_t) 0;
}

void int80Dispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    sc[rax](rbx, rcx, rdx, r8);
}

//En rcx se pone un char[] con al menos 9 espacios
char *time(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    timeToString((char *) rcx);
    return (char *) rcx;
}

//rbx es 1 para putnstring, 0 para clear; rcx es un char * y rdx es la longitud
char *write_(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    if (rbx == 1) {
        putnString((char *) rcx, rdx);
        return (char *) 0x1;
    }
    if (rbx == 0) {
        clearScreen();
        return (char *) 0x2;
    }
    return (char *) 0x0;
}

//rbx es 1 para stdin, rcx es el char * destino y rdx la longitud a leer
char *read_(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {

    if (rbx == 1) {
        return readBuffer(rbx, (char *) rcx, rdx);
    }
    return 0x0;
}

//rcx es xCoord, rdx es yCoord
char *pixel(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    putPixel(rcx, rdx);
    return 0x0;
}

//rbx == 1 --> char; rbx == 0 --> fondo; rcx array con colores B G R
char *colors(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    uint8_t *cols = (uint8_t *) rcx;
    if (rbx == 0)
        setBackgroundColors(cols[0], cols[1], cols[2]);
    else if (rbx == 1)
        setCharColors(cols[0], cols[1], cols[2]);
    return 0x0;
}


char * getPid(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char*)getRunningProcessPid();
}

char * createProcess(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    initializeProcess((functionIP)rbx);
    return (char*)0x1;
}

char * ps(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    printAll(allProcesses);
    return (char*)0x1;
}

char * upInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
	return up(rbx);
}

char * downInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
	return down(rbx);
}

char * kill(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    terminateProcess((pid_t)rbx);
    return (char *)0x1;
}

char * mallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)malloc(rbx);
}

char * freeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    free((void *)rbx);
    return (char *)0x1;
}

char * reallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)realloc((void *)rbx,rcx);
}

char * callocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)calloc(rbx);
}

char * initializeSemsAndMutexInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    initializeSemsAndMutex();
    return (char *)0x1;
}

char * sendInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    send((char *)rbx);
    return (char*)0x1;
}

char * receiveInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    char * deq = receive();
    return deq;
}

char * pipeRead(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    Pipe p = getPipe(allPipes,rbx);
    return (char *)readFromPipe(p);
}

char * pipeWrite(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    Pipe p = getPipe(allPipes,rbx);
    writeOnPipe(p,(char)rcx);
    return (char *)0x1;
}

char * createPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    Pipe p = newPipe();
    return (char *)p->pipeID;
}

char * openExistingPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    openPipe(rbx,rcx);
    return  0x1;
}

char * pipeClose(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    closePipe(rbx);
    return 0x1;
}

char * openInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)open(rbx, rcx);
}

char * closeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)close(rbx);
}

char * readInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)read(rbx, rcx, rdx, r8);
}

char * writeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)write(rbx, rcx, rdx, r8);
}

char * lsInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    ls();
    return "OK";
}

char * cdInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)cd(rbx);
}

char * mkdirInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)mkdir(rbx);
}

char * touchInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)touch(rbx);
}

char * rmInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)rm(rbx, rcx);
}

char * fileDetInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8) {
    return (char *)getFileDetails(rbx);
}
