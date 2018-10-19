# MiniCRT  

运行库实现 —— 《程序员的自我修养——链接、装载与库》 
    
:worried:  
  
___2018-10-19___
### 使用：  
```shell
make clean
make test
gdb test
```
in gdb:
```shell
set args argv1 argv2
r
```
直接运行会出现段错误   

### 注意  
malloc.c中
```c
list_head = header;
```
会出现段错误，所以自行初始值
  
### report  
fclose后参数传递出错，即
```c
printf("Hey!\n");
-->
int printf(const char* format, ...)
```
format为错误字符串
  
可以正常打开文件并读**或**写
