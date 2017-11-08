#pragma pack(push)
#pragma pack(1)
typedef struct {
	uint64_t ip;
	uint64_t cs;
	uint64_t flags;
	uint64_t sp;
	uint64_t ss;
} trapframe;
#pragma pack(pop)

extern trapframe * get_rsp_address();
extern void reset_rip();