''' IPC via shared memory
'''
import sysv_ipc
from struct import pack, unpack, calcsize

# Create shared memory object
memory = sysv_ipc.SharedMemory(2345)

while True:
    a = 1
    b = "s"
    c = 5.4

    a_ = pack("i", a)
    c_ = pack("f", c)
    memory.write(a_)
    memory.write(b, offset = 4)
    memory.write(c_, offset = 8)
        

