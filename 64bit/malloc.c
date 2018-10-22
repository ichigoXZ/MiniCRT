// TODO: 改进搜索速度、扩展堆空间、多线程支持

#include "minicrt.h"

typedef struct _heap_header
{
	enum{
		HEAP_BLOCK_FREE = 0xABABABAB,  // magic number of free block
		HEAP_BLOCK_USED = 0xCDCDCDCD,  // magic number of used block
	} type;							// block type FREE/USED

	unsigned int size;					// block size including header
	struct _heap_header* next;
	struct _heap_header* prev;
} heaper_header;

#define ADDR_ADD(a, o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heaper_header))

static heaper_header* list_head = NULL;

void free(void* ptr)
{
	heaper_header* header = (heaper_header*)ADDR_ADD(ptr, -HEADER_SIZE);
	if (header->type != HEAP_BLOCK_USED)	// 释放的空间并未使用
		return;

	header->type = HEAP_BLOCK_FREE;
	if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE) {  // 向前合并
		// merge
		header->prev->next = header->next;
		if(header->next != NULL)
			header->next->prev = header->prev;
		header->prev->size += header->size;

		header = header->prev;
	}

	if(header->next != NULL && header->next->type == HEAP_BLOCK_FREE) {  // 向后合并
		// merge
		header->size += header->next->size;
		header->next = header->next->next;
	}
}

void* malloc(unsigned long size)
{
	heaper_header* header;

	if(size == 0)
		return NULL;

	header = list_head;
	while(header != 0) {
		if(header->type == HEAP_BLOCK_USED) {
			header = header->next;
			continue;
		}

		// 空闲块刚好够所申请空间加上块指针的大小
		if(header->size > size + HEADER_SIZE &&
			header->size <= size + HEADER_SIZE*2) {
			header->type = HEAP_BLOCK_USED;
			return ADDR_ADD(header, HEADER_SIZE);	// 这一行书里没有
		}
		// 空闲块可以容纳申请空间和两个块指针
		if(header->size > size + HEADER_SIZE*2){
			// split
			heaper_header* next = (heaper_header*) ADDR_ADD(header, size + 
									HEADER_SIZE);	// 指向分割后空闲区域的头地址
			next->prev = header;
			next->next = header->next;
			next->type = HEAP_BLOCK_FREE;
			next->size = header->size - (size + HEADER_SIZE);  // 书中为减
			header->next = next;
			header->size = size + HEADER_SIZE;
			header->type = HEAP_BLOCK_USED;
			return ADDR_ADD(header, HEADER_SIZE);	// 返回分配空间的头地址
		}

		header = header->next;
	}

	return NULL;
}

#ifndef WIN32
// Linux brk system call
static long brk(void* end_data_segment) {
	long ret = 0;
	// brk system call number: 45
	// in /usr/include/x86_64-linux-gnu/asm/unistd.h
	// #indef __i386__
	// #	include <asm/unistd_32.h>
	__asm__ volatile( "movq $45, %%rax	\n\t"
		 "movq %1, %%rbx	\n\t"
		 "int $0x80			\n\t"
		 "movq %%rax, %0	\n\t"
		 : "=r"(ret): "m"(end_data_segment));
}
#endif

#ifdef WIN32
#include <Windows.h>
#endif

long mini_crt_heap_init()
{
	void* base = NULL;
	heaper_header* header = NULL;
	// 32 MB heap size
	unsigned int heap_size = 1024 * 1024 * 32;

#ifdef WIN32
	base = VirtualAlloc(0, heap_size, MEM_COMMIT |
		MEM_RESERVE, PAGE_READWRITE);
	if(base == NULL)
		return 0;
#else
	base = (void*)brk(0);
	void* end = ADDR_ADD(base, heap_size);
	end = (void*)brk(end);
	if(!end)
		return 0;
#endif

	header = (heaper_header*)base;

	header->size = heap_size;
	header->type = HEAP_BLOCK_FREE;
	header->next = NULL;
	header->prev = NULL;

	list_head = header;
	return 1;
}
