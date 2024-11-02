#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class BuddyBlock {
public:
  size_t size;
  BuddyBlock* next;
  bool isFree;
  void* startAddress;

  BuddyBlock(size_t size, void* address) : size(size), startAddress(address), next(nullptr), isFree(true) {}
};

class BuddyAllocator {
private:
  void* pool;
  size_t totalSize;
  BuddyBlock* freeList;

  size_t roundUpToPowerOfTwo(size_t size) {
    if (size == 0) return 1;
    return pow(2, ceil(log2(size)));
  }

  BuddyBlock* findFreeBlock(size_t size) {
    BuddyBlock* current = freeList;
    while (current) {
      if (current->isFree && current->size >= size) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  BuddyBlock* splitBlock(BuddyBlock* block, size_t size) {
    size_t halfSize = block->size / 2;
    void* buddyAddress = static_cast<char*>(block->startAddress) + halfSize;
    BuddyBlock* buddyBlock = new BuddyBlock(halfSize, buddyAddress);
    buddyBlock->next = freeList;
    freeList = buddyBlock;
    block->size = halfSize;
    return block;
  }

public:
  BuddyAllocator(size_t size) : totalSize(size), freeList(nullptr) {
    pool = sbrk(size);
    if (pool == (void*)-1) throw runtime_error("sbrk failed");
    freeList = new BuddyBlock(size, pool);
  }

  void* allocate(size_t size) {
    size = roundUpToPowerOfTwo(size);
    BuddyBlock* block = findFreeBlock(size);
    if (!block) throw runtime_error("Out of memory");
    while (block->size > size) {
      block = splitBlock(block, size);
    }
    block->isFree = false;
    return block->startAddress;
  }

  void deallocate(void* pointer) {
    BuddyBlock* block = freeList;
    while (block) {
      if (block->startAddress == pointer) {
        block->isFree = true;
        size_t buddyAddress = reinterpret_cast<size_t>(pointer) ^ block->size;
        BuddyBlock* buddy = freeList;
        while (buddy) {
          if (reinterpret_cast<size_t>(buddy->startAddress) == buddyAddress && buddy->size == block->size && buddy->isFree) {
            block->size *= 2;
            buddy->isFree = false;
            return;
          }
          buddy = buddy->next;
        }
        return;
      }
      block = block->next;
    }
    throw runtime_error("Invalid pointer");
  }

  ~BuddyAllocator() {
    sbrk(-totalSize);
    BuddyBlock* current = freeList;
    while (current) {
      BuddyBlock* next = current->next;
      delete current;
      current = next;
    }
  }
};

#endif
