#define MAX_ALLOC 16384
#define MAX_OFFSET 131072 //2^20

typedef struct meta {
	unsigned char allo : 1;		
	unsigned char left : 1;		
	unsigned char size : 6;		
} Meta;

void unpack(Meta * m, int pos);
void init_block();
int log2(int n);
int size_to_n(int reqSize);
int jump_next(int n, int pos);
int jump_back(int n, int pos);
int is_left(int n, int pos);
void merge(int pos, int pos2, int n);
void * malloc(int reqSize);
void free(void * ptr);
void * realloc(void * ptr, int size);
void * calloc(int size);