//
// Created by Felipe on 04/05/2018.
//

typedef struct stackNodeCDT * stackADT;

struct stackNodeCDT {

    struct stackNodeCDT * next;
    void * data;

};

stackADT push(stackADT stack, void * data) {

    stackADT node = malloc(sizeof(stackNodeCDT));
    node->data = data;
    node->next = stack;
    stack = node;

}

stackADT pop(stackADT stack) {

    if(stack == NULL) return;
    stackADT ret = stack;
    stack = stack->next;

    return temp;

}


