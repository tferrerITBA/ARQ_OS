#include <glob.h>
#include <stddef.h>

typedef struct stackStruct {
    struct stackElement * first;
    struct stackElement * last;
    int length;
    size_t size;
} stackStruct;

typedef stackStruct * Stack;

typedef struct stackElement {
    void * info;
    struct stackElement * next;
    struct stackElement * previous;
} stackElement;

typedef struct stackElement * Element;

Stack newStack(size_t size);
int isEmpty(Stack stack);
int getSize(Stack stack);
void push(Stack stack, void * elem);
void * pop(Stack stack);