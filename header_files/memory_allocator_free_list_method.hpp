#ifndef MEMORY_ALLOCATOR_WITH_FREE_LIST
#define MEMORY_ALLOCATOR_WITH_FREE_LIST

#include <iostream>
#include <unistd.h>
#include <stdexcept>

using namespace std;

class MemoryBlock {
public:
  size_t size;
  MemoryBlock* next;

  MemoryBlock(size_t size) : size(size), next(nullptr) {}
};

class MemoryAllocator {
private:
  char* pStart;
  char* pEnd;
  char* freePointer;
  MemoryBlock* freeList;

public:
  MemoryAllocator(size_t size) {
    pStart = static_cast<char*>(sbrk(size));
    if (pStart == (void*)-1) {
      throw runtime_error("sbrk failed to allocate memory");
    }
    freePointer = pStart;
    freeList = nullptr;
    pEnd = pStart + size;
  }

  void* allocate(size_t size) {
    size_t block_size = (size + sizeof(MemoryBlock) - 1) & ~(sizeof(MemoryBlock) - 1);
    if (freePointer == nullptr) {
      throw runtime_error("Memory allocator is exhausted");
    }
    if (freePointer + block_size > pEnd) {
      throw bad_alloc();
    }
    if (freeList != nullptr) {
      MemoryBlock* block = freeList;
      freeList = freeList->next;
      return reinterpret_cast<void*>(block + 1);
    }
    MemoryBlock* block = new (freePointer) MemoryBlock(block_size);
    freePointer += block_size;
    return reinterpret_cast<void*>(block + 1);
  }

  void deallocate(void* pointer) {
    if (pointer == nullptr) return;
    MemoryBlock* block = reinterpret_cast<MemoryBlock*>(pointer) - 1;
    block->next = freeList;
    freeList = block;
  }

  ~MemoryAllocator() {}
};

#endif 
