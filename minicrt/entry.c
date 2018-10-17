#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char* argv[]);
void exit(int);

static void crt_fatal_error(const char* msg)
{
	// printf("fatal error: %s\n", msg);
	exit(-1);
}

void mini_crt_entry(void)
{
	int ret;

#ifdef WIN32
	int flag = 0;
	int argc = 0;
	char* argv[16];	//最多16个参数
	char* c1 = GetCommandLineA();

	//解析命令行
	argv[0] = c1;
	argc++;
	while(c1) {
		if(*c1 == '\"')	//引号内属于同一参数
			if(flag == 0)
				flag = 1;
			else
				flag = 0;
		else if(*c1 == ' ' && flag == 0) {
			if(*(c1+1)) {
				argv[argc] = c1 + 1; //把下一个字符串的地址赋给argv数组
				argc++;
			}
			*c1 = '\0'  //添加字符串结束标志
		}
		c1++;
	}

#else
	int argc;
	char** argv;

	char* ebp_reg=0;
	// ebp_reg = %ebp;
	asm("mov %%ebp, %0 \n" : "=r" (ebp_reg));  //'='指定ebp_reg输出操作数, r指定将ebp_reg存储在寄存器中

	argc = *(ini*)(ebp_reg + 4);
	argv = (char**)(ebp_reg + 8);

#endif

	if (!mini_crt_heap_init())
		crt_fatal_error("heap initialize failed");
	if (!mini_crt_io_init())
		crt_fatal_error("IO initialize failed");

	ret = main(argc, argv);
	exit(ret);
}

void exit(int exitCode)
{
	// mini_crt_call_exit_routine();
#ifdef
	ExitProcess(exitCode);
#else
	asm( "movl %0, %%ebx \n\t"
		 "movl $1, %%eax \n\t"
		 "hlt            \n\t"::"m"(exitCode));  //m：内存操作数约束
#endif
}