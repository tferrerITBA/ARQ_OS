#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>
#include "videoMode.h"

extern char * read(uint64_t rbx, uint64_t rcx, uint64_t rdx);
extern char * write(uint64_t rbx, uint64_t rcx, uint64_t rdx);
extern char * time(uint64_t rbx, uint64_t rcx, uint64_t rdx);
extern void _int80Handler();

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */

typedef char * (*sysCalls)(uint64_t, uint64_t, uint64_t);
sysCalls sc[] = {0, 0, 0, &read, &write, 0, 0, 0, 0, 0, 0, 0, 0, &time};

DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setup_IDT_entry (int index, uint64_t offset);

void load_idt() {

  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler);
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler);
  setup_IDT_entry (0x21, (uint64_t)&_irq01Handler);
  setup_IDT_entry (0x80, (uint64_t)&_int80Handler);

	//Solo interrupcion timer tick  y teclado habilitadas
	picMasterMask(0xFC); // 1111 1100
	picSlaveMask(0xFF);
        
	_sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
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

//No necesito ningún argumento
char * time(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
  return timeToString();
}

//rbx es 1 para putnstring, 0 para clear; rcx es un char * y rdx es la longitud
char * write(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
  if(rbx == 1) {
    putnString(rcx, rdx);
    return 0x1;
  }
  else if(rbx == 0) {
    clearScreen();
    return 0x2;
  }
  return 0x0;
}

//rbx es 1 para stdin, rcx es el char * destino y rdx la longitud a leer
char * read(uint64_t rbx, uint64_t rcx, uint64_t rdx) {
  if(rbx == 1) {
    char * status = readBuffer(rbx, (char *)rcx, rdx);
    return status;
  }
  return 0x0;
}