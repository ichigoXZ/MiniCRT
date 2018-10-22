# -fno-builtin: 关闭GCC的内置函数功能
# -nostdlib: 不使用任何来自Glibc、GCC的库文件和启动文件
# -fno-stack-protector: 关闭堆栈保护功能
CFLAGS=-ggdb -fno-builtin -nostdlib -fno-stack-protector 
# -fno-rtti: 关闭RTTI即运行时类型识别
# -fno-exceptions: 关闭异常支持
CPPFLAGS=-ggdb -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fpermissive
OBJS=entry.o malloc.o stdio.o string.o printf.o 
OBJSCPP=ctors.o crtbegin.o crtend.o new_delete.o sysdep.o iostream.o String.o

FLAGS=C

ifeq ($(FLAGS), CPP)
	OBJA=$(OBJS) atexit.o $(OBJSCPP)
	TARGET=entry.o crtbegin.o test_cpp.o minicrt.a crtend.o
else
	OBJA=$(OBJS)
	TARGET=entry.o test.o minicrt.a
endif


minicrt.a: $(OBJA)
	ar -rs minicrt.a $(OBJA)


$(OBJS) atexit.o: %.o:%.c 
	gcc -c $(CFLAGS) $<

$(OBJSCPP): %.o:%.cpp
	g++ -c $(CPPFLAGS) $<


test.o: test.c
	gcc -c $(CFLAGS) test.c

test_cpp.o: test_cpp.cpp
	g++ -c $(CPPFLAGS) test_cpp.cpp


test: $(TARGET)
	ld -static -e mini_crt_entry $^ -o $@


clean:
	if [ -f test.txt ] ; then rm test.txt ; fi 
	rm *.o minicrt.a test
