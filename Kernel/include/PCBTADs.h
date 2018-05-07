typedef struct pcbCDT{
    int pid;
    int state;
    void * stackPointer;
    void * stackBase;
    void * heapBase;
    //Agregar campos a medida que se vayan necesitando
} pcb;

typedef pcb * Pcb;

typedef struct tableNodeCDT{
    Pcb block;
    struct tableNodeCDT * next;
} tableNode;

typedef tableNode * TableNode;

typedef struct pcbTable{
    TableNode first;
    int size;
} pcbTable;

typedef pcbTable * PcbTable;
