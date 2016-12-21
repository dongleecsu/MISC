使用shared memory实现cpp和python的IPC
=====  
系统： Ubuntu14.04

### cpp client  
把cpp端看成client，接收来自于python server的数据。
```cpp
struct shared_use_st
{
    int x;
    unsigned char y;
    float z;
};
```
**注意：**由于内存的对齐机制（主要是为了快速的进行内存操作）使得变量在内存中是以_word_的形式存储的，而非_byte_，因此，可以打印出来`x,y,z`的地址来看：
```cpp
std::cout << "int: &x = " << &shared->x << "\n";
std::cout << "uchar: &y = " << static_cast<const void*>(&shared->y) << "\n";
std::cout << "float: &z = " << &shared->z << "\n";
// Result:
/**********************
int: &x = 0x7f7e54c92000
uchar: &y = 0x7f7e54c92004
float: &z = 0x7f7e54c92008
**********************/
```  
即使`sizeof(unsigned char) = 1`，它在内存中存储时也会占据4个bytes。这一点在python server写入数据时，尤其要注意_offset_。
### python server  
python server向共享内存中写入数据，在cpp client中读取相应地址的数据，检查是否一致。

**注意：**由于上边提到的内存对齐机制，即使写入size=1的字符串也要_offset=4_。
```python
a = 1
b = "s"
c = 5.4

a_ = pack("i", a)
c_ = pack("f", c)
memory.write(a_)
memory.write(b, offset = 4)
memory.write(c_, offset = 8)
```  
只要注意并使用上边的对齐方式，cpp和python传输的数据就是一致的。
