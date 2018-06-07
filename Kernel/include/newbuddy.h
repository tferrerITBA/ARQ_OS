/*
#include <stdint.h>
#include <stddef.h>

#define MAX_ORDER 20
#define TRUE 1
#define FALSE 0

typedef blockData * b_data;

typedef struct blockData {
	char allocated;		
	char left_b;		
	int order;		
} blockData;


void initializeBuddySystem();
int calculateOrder(size_t reqSize);
int goRight(int n, int pos);
int goLeft(int n, int pos);
int leftBuddy(int n, int p);
void mergeBlocks(int pos1, int pos2, int n);
void * buddyMalloc(size_t size);
void buddyFree(void * ptr);
*/