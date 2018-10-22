#include "minicrt.h"

// _cxa_atexit所接受的函数指针必须有一个void*作为参数，并且调用_cxa_atexit
// 时，这个参数(void* arg)也要随着记录下来，等到要执行的时候再传递进去

typedef struct _func_node
{
	atexit_func_t func;
	void* arg;
	int is_cxa;	// 不为零，则表示这个节点是由__cxa_atexit()注册的回调函数
	struct _func_node* next;
} func_node;

static func_node* atexit_list = 0;

int register_atexit(atexit_func_t func, void* arg, int is_cxa)
{
	func_node* node;
	if(!func)
		return -1;

	node = (func_node*)malloc(sizeof(func_node));

	if(node==0)
		return -1;

	node->func = func;
	node->arg = arg;
	node->is_cxa = is_cxa;
	node->next = atexit_list;
	atexit_list = node;
	return 0;
}

#ifndef WIN32
typedef void (*cxa_func_t)(void*);
int __cxa_atexit(cxa_func_t func, void* arg, void* unused)
{
	return register_atexit((atexit_func_t)func, arg, 1);
}

#endif

int ateixt(atexit_func_t func)
{
	return register_atexit(func, 0, 0);
}

void mini_crt_call_exit_routine()
{
	func_node* p = atexit_list;
	for(; p != 0; p=p->next)
	{
		#ifdef WIN32
			p->func();
		#else
		if (p->is_cxa)
			((cxa_func_t)p->func)(p->arg);
		else
			p->func();
		#endif
		free(p);
	}
	atexit_list = 0;
}