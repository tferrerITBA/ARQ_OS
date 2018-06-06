#ifndef IDT_LOADER_H
#define IDT_LOADER_H

#include <stdint.h>
#include "defs.h"
#include "interrupts.h"
#include "videoMode.h"
#include "RTC.h"
#include "sem.h"
#include "defs.h"
#include "process.h"
#include "sem.h"
#include "pipe.h"
#include "FAT.h"

static void setup_IDT_entry (int index, uint64_t offset);
void load_idt();
extern void _cli();
extern void _sti();
extern void picMasterMask(uint8_t);
extern void picSlaveMask(uint8_t);
extern void printAll(PcbTable table);
char *read_(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char *write_(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char *time(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char *pixel(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char *colors(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * getPid(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * createProcess(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * ps(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * upInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * downInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * kill(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * mallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * freeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * initializeProdConsInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * reallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * callocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * initializeSemsAndMutexInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * sendInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * receiveInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * pipeRead(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * pipeWrite(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * createPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * openExistingPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * openInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * closeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * readInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * writeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * lsInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * cdInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * mkdirInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * touchInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * rmInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);
char * fileDetInt(uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t r8);

extern void _int80Handler();
extern void _exception6Handler();

#pragma pack(push)        /* Push de la alineación actual */
#pragma pack (1)        /* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
    uint16_t offset_l, selector;
    uint8_t cero, access;
    uint16_t offset_m;
    uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)        /* Reestablece la alinceación actual */

typedef char *(*sysCalls)(uint64_t, uint64_t, uint64_t, uint64_t);
sysCalls sc[] = {0, 0, 0, &read_, &write_, &pixel, &colors, &getPid,
                 &createProcess, &ps, &upInt, &downInt, &kill, &time,
                 &mallocInt, &freeInt, &initializeSemsAndMutexInt, &reallocInt,
                 &callocInt, &sendInt, &receiveInt, &pipeRead, &pipeWrite,
                 &createPipe, &openExistingPipe, &openInt, &closeInt,
                  &readInt, &writeInt, &lsInt, &cdInt, &mkdirInt, &touchInt, 
                  &rmInt, &fileDetInt};

DESCR_INT *idt = (DESCR_INT *) 0;    // IDT de 255 entradas

static void setup_IDT_entry(int index, uint64_t offset);

#endif
