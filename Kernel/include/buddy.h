#include <stdint.h>
#include <glob.h>
#include <wchar.h>

#define HEADER_SIZE 8
#define MIN_ALLOC_LOG2 4
#define MIN_ALLOC ((size_t)1 << MIN_ALLOC_LOG2)
#define MAX_ALLOC_LOG2 31
#define MAX_ALLOC ((size_t)1 << MAX_ALLOC_LOG2)
#define BUCKET_COUNT (MAX_ALLOC_LOG2 - MIN_ALLOC_LOG2 + 1)

typedef struct list_t {
  struct list_t *prev, *next;
} list_t;


int update_max_ptr(uint64_t *new_value);
void list_init(list_t *list);
void list_push(list_t *list, list_t *entry);
void list_remove(list_t *entry);
list_t *list_pop(list_t *list);
uint64_t *ptr_for_node(size_t index, size_t bucket);
size_t node_for_ptr(uint64_t *ptr, size_t bucket);
int parent_is_split(size_t index);
static void flip_parent_is_split(size_t index);
size_t bucket_for_request(size_t request);
int lower_bucket_limit(size_t bucket);
void *malloc(size_t request);
void free(void *ptr);
uint64_t * sbrk(size_t size);
void * realloc(void * ptr, size_t size);
void * calloc(size_t size);






