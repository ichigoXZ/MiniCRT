# -fno-builtin: 关闭GCC的内置函数功能
# -nostdlib: 不使用任何来自Glibc、GCC的库文件和启动文件
# -fno-stack-protector: 关闭堆栈保护功能
# -m32: force 32-bit ABI
CFLAGS=-fno-builtin -nostdlib -fno-stack-protector -m32
OBJS=entry.o malloc.o fprintf.o stdio.o string.o

minicrt.a: $(OBJS)
	ar -rs minicrt.a $(OBJS)

$(OBJS): %o:%c 
	gcc -c $(CFLAGS) $<

clean:
	rm *.o minicrt.a