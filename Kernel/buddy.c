#define NULL 0
char * heapStart = 0x800000;
int breakPoint = 0;

void * malloc(int size) {

  void * ret = (void *)(heapStart + breakPoint);
  breakPoint += size;
  return ret;
}

void free(void * ptr) {
  ptr = NULL;
  return;
}

void * realloc(void * ptr) {
  return ptr;
}

void * calloc(void * ptr, int size) {
  return ptr;
}
