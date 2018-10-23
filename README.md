# MiniCRT  

运行库实现 —— 《程序员的自我修养——链接、装载与库》 
&nbsp; :blush: 
    
  
## CRT - C runtime library    
### 使用：  
```shell
make clean
make test
test argv1 argv2
```  

  
  
## CRT++ - C++ runtime library  
### 使用：  
```shell
make clean
make test FLAGS=CPP
test
```


### report  
64位下C++的变长参数处理不正确，fprinf出错，ofstream类中用fputc和fpucs输出  
32位到62位的修改主要是寄存器由int变为long,所以需要修改一些定义和内联汇编指令，以及argc、argv的获取等  
64位的修改参考[MiniCRT](https://github.com/youzhonghui/MiniCRT)
  

