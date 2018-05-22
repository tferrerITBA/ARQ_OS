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
#include "messages.h"
#include "pipe.h"

static void setup_IDT_entry (int index, uint64_t offset);
void load_idt();
extern void _cli();
extern void _sti();
extern void picMasterMask(uint8_t);
extern void picSlaveMask(uint8_t);
extern void printAll();
char *read_(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char *write_(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char *time(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char *pixel(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char *colors(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * getPid(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * createProcess(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * ps(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * upInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * downInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * kill(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * mallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * freeInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * initializeProdConsInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * reallocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * callocInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * initializeSemsAndMutexInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * sendInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * receiveInt(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * pipeRead(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * pipeWrite(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * createPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx);
char * openExistingPipe(uint64_t rbx, uint64_t rcx, uint64_t rdx);
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

typedef char *(*sysCalls)(uint64_t, uint64_t, uint64_t);
sysCalls sc[] = {0, 0, 0, &read_, &write_, &pixel, &colors, &getPid,
                 &createProcess, &ps, &upInt, &downInt, &kill, &time,
                 &mallocInt, &freeInt, &initializeSemsAndMutexInt, &reallocInt,
                 &callocInt, &sendInt, &receiveInt, &pipeRead, &pipeWrite,
                 &createPipe, &openExistingPipe};

DESCR_INT *idt = (DESCR_INT *) 0;    // IDT de 255 entradas

static void setup_IDT_entry(int index, uint64_t offset);

#endif
