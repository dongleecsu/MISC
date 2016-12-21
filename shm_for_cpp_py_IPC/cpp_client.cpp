/******************************
g++ -o cpp_client cpp_client.cpp
*******************************/
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define len 5

struct shared_use_st
{
    int x;
    unsigned char y;
    float z;
};

int main(int argc, char const *argv[])
{
    int shmid;
    key_t key = 2345;
    void* shm = NULL;
    struct shared_use_st* shared = NULL;

    if ((shmid = shmget(key, 20, IPC_CREAT | 0666)) < 0)
   {
      printf("Error getting shared memory id");
      exit(1);
   }

   if ((shm = shmat(shmid, 0, 0)) == (void*) -1)
   {
      printf("Error attaching shared memory id");
      exit(1);
   }

   printf("*********** Startint*********\n");
   shared = (struct shared_use_st*) shm;
   std::cout << "int: &x = " << &shared->x << "\n";
   std::cout << "uchar: &y = " << static_cast<const void*>(&shared->y) << "\n";
   std::cout << "float: &z = " << &shared->z << "\n";

   // Initial value to check change.
   shared->x = 30;
   shared->y = 'l';
   shared->z = 8.7;
   // while (true){
   //      std::cout << "x = " << shared->x << "\n";
   //      std::cout << "y = " << shared->y << "\n";
   //      std::cout << "z = " << shared->z << "\n";
   // }

    return 0;
}
