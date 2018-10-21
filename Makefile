# -fno-builtin: 关闭GCC的内置函数功能
# -nostdlib: 不使用任何来自Glibc、GCC的库文件和启动文件
# -fno-stack-protector: 关闭堆栈保护功能
# -m32: force 32-bit ABI
CFLAGS=-ggdb -fno-builtin -nostdlib -fno-stack-protector -m32
# -fno-rtti: 关闭RTTI即运行时类型识别
# -fno-exceptions: 关闭异常支持
CPPFLAGS=-ggdb -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fpermissive -m32
OBJS=entry.o malloc.o fprintf.o stdio.o
OBJSCPP=ctors.o crtbegin.o crtend.o new_delete.o sysdep.o String.o iostream.o


FLAGS=CPP
ifeq ($(FLAGS), CPP)
	OBJA=$(OBJS) atexit.o $(OBJSCPP)
else
	OBJA=$(OBJS) string.o
endif

minicrt.a: $(OBJA)
	ar -rs minicrt.a $(OBJA)

# minicrt.a: $(OBJS)
# 	ar -rs minicrt.a $(OBJS)

$(OBJS) string.o atexit.o: %.o:%.c 
	gcc -c $(CFLAGS) $<


$(OBJSCPP): %.o:%.cpp
	g++ -c $(CPPFLAGS) $<

test.o: test.c
	gcc -c $(CFLAGS) test.c

test: entry.o test.o minicrt.a
	ld -static -e mini_crt_entry -m elf_i386 $^ -o $@

test_cpp.o: test_cpp.cpp
	g++ -c $(CPPFLAGS) test_cpp.cpp

test_cpp: entry.o crtbegin.o test_cpp.o minicrt.a crtend.o
	ld -static -e mini_crt_entry $^ -o $@

clean:
	rm *.o minicrt.a test test.txt test_cpp