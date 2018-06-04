#include "include/buddy.h"
#include "include/lib.h"
#include <stdint.h>
#include <unistd.h>

char * heapStart = 0x600000;

void intializeBuddySystem() {
	init_block();
}

void init_block() {
	memset(heapStart,54, 1);
}

int log2(int n) {
	int r=0;
	while(n >>= 1){
		r++;
	}
	return r;
}

int size_to_n(int reqSize) {
	return log2(reqSize) + 1;
}

int jump_next(int n, int pos) {
	int bits = pos>>(n);
	bits+=1;
	int ret = bits<<(n);

	if (ret > (int)MAX_OFFSET) {
		return ret;
	} else {
		return ret;
	}
}

int jump_back(int n, int pos) {
	int bits = pos>>(n);
	bits-=1;
	return bits<<(n);
}

void unpack(Meta * m, int pos) {
	memset(m, *((char *)heapStart + pos), 1);
}

int is_left(int n, int pos) {

	int k = 1;
	k<<=(n);

	unsigned int p = (unsigned int)pos;
	p<<=(31-n);
	p>>=(31-n);

	if (k == p) {
		return 0;	
	} else {
		return 1;	
	}
}

void merge(int pos, int pos2, int n) {
	
	char newMeta = (n+1)<<2;

	if (is_left(n+1, pos)) {
		newMeta+=2;
	}

	*((char *)heapStart + pos) = newMeta;
	*((char *)heapStart + pos2) = 0;		
}

void * malloc(int reqSize) {

	if (reqSize > MAX_ALLOC) {
		return NULL;
	}

	int n = size_to_n(reqSize);
	int pos = 0;
	unsigned char c = 0;
	Meta * m = memset(&c, 0, 1);
	
	while (pos < MAX_OFFSET) {

		unpack(m, pos);

		if (m->size == 0) {
			return NULL;
		}

		if (n <= m->size) {
			if (m->allo == 1) {				
				pos = jump_next(n, pos);
				continue;
			} else if (m->size == n) {		
				*(heapStart + pos) += 1;
				pos+=1;
				return (void*)((char *)heapStart+pos);
			} else { 						

				int partner = jump_next((m->size)-1, pos);

				char meta_1 = 2;
				char meta_2 = 0;
				
				char s = ((m->size)-1)<<2;
				meta_1 = (meta_1 | s);
				meta_2 = (meta_2 | s);

				*(heapStart + pos) = meta_1;
				*(heapStart + partner) = meta_2;

				continue;
			}
		} else {
			pos = jump_next(n, pos);
			continue;
		}
	}
	return 0;
}

void free(void * ptr) {
	
	if (ptr <= (void *)heapStart || ptr > (void *)((char *)heapStart + MAX_OFFSET)) {
		return;
	}

	int pos = (int)(ptr - (void *)heapStart - 1);

	if (pos%2 == 1 || *(heapStart + pos) == 0) {
		return;
	}

	unsigned char c1 = 0;
	unsigned char c2 = 0;
	Meta * m1 = memset(&c1, 0, 1); 
	Meta * m2 = memset(&c2, 0, 1);
	unpack(m1,pos);

	*((char *)heapStart + pos) = *((char *)heapStart + pos) - 1;

	while (pos >= 0 && pos <= MAX_OFFSET){

		unpack(m1,pos);

		if (m1->left) {	

			int pos2 = jump_next(m1->size, pos);

			if (pos2 >= 0 && pos2 <= MAX_OFFSET - 2) {
				unpack(m2,pos2);
			} else {
				break;
			}

			if (m2->allo || m2->size != m1->size) {
				break;
			} else {
				merge(pos, pos2, m1->size);
			}

		} else {		

			int pos2 = jump_back(m2->size,pos);

			if (pos2 >= 0 && pos2 <= MAX_OFFSET - 2) {
				unpack(m2,pos2);
			} else {
				break;
			}

			if (m2->allo || m2->size != m1->size) {
				break;
			} else {
				merge(pos2, pos, m1->size); 
			}	
		}
	}
}


void * realloc(void * ptr, int size) {
  void * newMemory = malloc(size);
  memcpy(newMemory,ptr,size);
  free(ptr);
}

void * calloc(int size) {
  int i;
  void * ptr = malloc(size);
  if(ptr != NULL) {
    for (i = 0; i < size; i++) { 
        *((char *)ptr + i) = 0;
    }
  }
  
  return ptr;
}