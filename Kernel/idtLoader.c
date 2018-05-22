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

void int80Dispatcher(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    sc[rax](rbx, rcx, rdx);
}

//En rcx se pone un char[] con al menos 9 espacios
char *time(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    timeToString((char *) rcx);
    return (char *) rcx;
}

//rbx es 1 para putnstring, 0 para clear; rcx es un char * y rdx es la longitud
char *write_(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
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
char *read_(uint64_t rbx, uint64_t rcx, uint64_t rdx) {

    if (rbx == 1) {
        return readBuffer(rbx, (char *) rcx, rdx);
    }
    return 0x0;
}

//rcx es xCoord, rdx es yCoord
char *pixel(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    putPixel(rcx, rdx);
    return 0x0;
}

//rbx == 1 --> char; rbx == 0 --> fondo; rcx array con colores B G R
char *colors(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    uint8_t *cols = (uint8_t *) rcx;
    if (rbx == 0)
        setBackgroundColors(cols[0], cols[1], cols[2]);
    else if (rbx == 1)
        setCharColors(cols[0], cols[1], cols[2]);
    return 0x0;
}


char * getPid(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    return (char*)getRunningProcessPid();
}

char * createProcess(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    initializeProcess((functionIP)rbx);
    return (char*)0x1;
}

char * ps(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    printAll();
    return (char*)0x1;
}

char * upInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
	return up(rbx);
}

char * downInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
	return down(rbx);
}

char * kill(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    terminateProcess((pid_t)rbx);
    return (char *)0x1;
}

char * mallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    return (char *)malloc(rbx,getRunningProcessPid());
}

char * freeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    free((void *)rbx);
    return (char *)0x1;
}

char * reallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    return (char *)realloc((void *)rbx,rcx,getRunningProcessPid());
}

char * callocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    return (char *)calloc(rbx,getRunningProcessPid());
}

char * initializeSemsAndMutexInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    initializeSemsAndMutex();
    return (char *)0x1;
}

char * sendInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    send((char *)rbx);
    return (char*)0x1;
}

char * receiveInt(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    char * deq = receive();
    return deq;
}

char * pipeRead(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    Pipe p = getPipe(allPipes,(int)rbx);
    putString("Get pipe gave:");
    printHex(p);
    return (char *)readFromPipe(p);
}

char * pipeWrite(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    Pipe p = getPipe(allPipes,rbx);
    putString("Get pipe gave:");
    printHex(p);
    put_char('\n');
    writeOnPipe(p,(char)rcx);
    return (char *)0x1;
}

char * createPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    Pipe p = newPipe();
    putString("New pipe id: ");
    put_char('0' + p->pipeID);
    put_char('\n');
    return (char *)p->pipeID;
}

char * openExistingPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
    openPipe(rbx,rcx);
    return  0x1;
}
