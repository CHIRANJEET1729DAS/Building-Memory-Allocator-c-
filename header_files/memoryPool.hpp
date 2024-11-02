#ifndef MEMORYPOOL
#define MEMORYPOOL

#include <iostream>
#include <unistd.h> 
#include <stdexcept>

using namespace std;

class MemoryPool{
 private:
  char* poolStart;
  int poolSize;
  char* freePointer;
  char* poolEnd;
 public:
  MemoryPool(size_t size) {
   poolStart = static_cast<char*>(sbrk(size));
   if (poolStart == (void*)-1){
    throw runtime_error("sbrk failed to allocate memory");
   }
   poolEnd = poolStart + size;
   freePointer = poolStart;
  }
  void* allocate(size_t size){
   if (freePointer+size>poolEnd){
    throw bad_alloc();
   }
   void* allocateMemory = freePointer;
   freePointer += size;
   return allocateMemory;
  }
  ~MemoryPool(){}

};


#endif
