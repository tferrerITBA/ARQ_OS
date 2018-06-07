/*
#include "include/newbuddy.h"

char * heapStart = (char *) 0x800000;


int ceil_log2(unsigned long long x)	{
  
  static const unsigned long long t[6] = {
    0xFFFFFFFF00000000ull,
    0x00000000FFFF0000ull,
    0x000000000000FF00ull,
    0x00000000000000F0ull,
    0x000000000000000Cull,
    0x0000000000000002ull
  };

  int y = (((x & (x - 1)) == 0) ? 0 : 1);
  int j = 32;
  int i;

  for (i = 0; i < 6; i++) {
    int k = (((x & t[i]) == 0) ? 0 : j);
    y += k;
    x >>= k;
    j >>= 1;
  }

  return y;
}

void initializeBuddySystem() {
	b_data block;
	block = (b_data)heapStart;
	block->allocated = 0;
	block->left_b = 0;
	block->order = MAX_ORDER;
}

int calculateOrder(size_t reqSize) {
	reqSize+=1;
	return ceil_log2(size);
}

int goRight(int n, int pos) {
	int aux = pos>>(n);
	aux+=sizeof(struct blockData);
	int ret = aux<<(n);
	return ret;
}

int goLeft(int n, int pos) {
	int bits = pos>>(n);
	bits-=sizeof(struct blockData);
	return bits<<(n);
}

int leftBuddy(int n, int p) {

	int aux = 1;
	aux<<=n;
	
	p<<=(31-n);
	p>>=(31-n);

	if (aux == p) {
		return FALSE;
	} else {
		return TRUE;
	}
}

void mergeBlocks(int pos1, int pos2, int n) {

	b_data block;
	if (is_left(n+1, pos1)) 
	
	*(heapStart + pos1 ) = ;
	*(heapStart + pos2) = 0; 		
}

void * buddyMalloc(size_t size) {

	if (size > MAX_ALLOC) {
		return NULL;
	}

	int n = calculateOrder(size);
	int pos = heapStart;
	b_data dataBlock;

	while (pos < (heapStart + (1<<MAX_ORDER))) {

		dataBlock = (b_data)(heapStart + pos);
		if (dataBlock->order  == 0) {
			return NULL;
		}
		if (n <= dataBlock->order) {
			if (m->allocated == TRUE) {				
				pos = goRight(n, pos);
			} 
			else if (m->order == n) {		
				b_data block = (b_data)(heapStart + pos);
				block->allocated = TRUE;
				return (void*)((heapStart + pos + sizeof(struct blockData)));
			} 
		} 
		else {
			pos = goRight(n, pos);
		}
	}

	return 0;
}

void buddyFree(void * ptr) {
	
	if (ptr <= (void *)heapStart || ptr > (void *)(heapStart + MAX_ORDER)) {
		return;
	}

	int pos = (int) (ptr - sizeof(struct blockData));

	if (pos%2 == 1 || *(heapStart + pos) == 0) {
		return;
	}

	b_data block = (b_data) (ptr - sizeof(struct blockData));
	b_data block2;
	block->allocated = FALSE;
	int pos2;

	while (pos >= 0 && pos <= (heapStart + (1 << MAX_ORDER))){

		b_data block = (b_data)pos;
		if (block->left_b) {	
			pos2 = goRight(block->order, pos);
			b_data block2 = (b_data) pos2;
			if (block2->allocated || block2->order != block->order) {
				break;
			} else {
				mergeBlocks(pos, pos2, block->order);
			}

		} 
		else {		

			pos2 = goLeft(block->order,pos);
			b_data block2 = (b_data) pos2;

			if (block2->allocated || block2->order != block->order) {
				break;
			} else {
				merge(pos2, pos, block->order); 
			}	
		}
	}
}
*/
