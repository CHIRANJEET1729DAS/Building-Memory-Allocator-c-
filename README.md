# Building-Memory-Allocator-c++

# Memory Allocator Project  

This project features a custom memory allocator implemented in C++. It showcases three different memory allocation techniques: Free List Allocator, Buddy Allocator, and a Basic Allocator. The goal is to demonstrate various approaches to memory management, their advantages, and their limitations.

# Memory Allocation Techniques

# [Free List Allocator](https://github.com/CHIRANJEET1729DAS/Building-Memory-Allocator-c-/blob/main/header_files/memory_allocator_free_list_method.hpp)

The Free List Allocator is a powerful and flexible memory management technique that maintains a dynamic linked list of free memory blocks. When a memory request comes in, the allocator leaps into action, searching through the free list to find the perfect fit!

Pros:

1) Dynamic Flexibility: Adapts well to variable-sized memory requests, making it ideal for applications with unpredictable memory usage.
2) Coalescing Blocks: By merging adjacent free blocks upon deallocation, it effectively reduces fragmentation over time.
3) Multiple Allocation Strategies: Supports various strategies (First-Fit, Best-Fit, Worst-Fit), allowing optimization based on specific use 
                                   cases.
Cons:

1) Fragmentation: Over time, fragmentation can still occur, particularly if memory is allocated and deallocated in an irregular pattern.
2) Overhead: Maintaining a linked list incurs some overhead, as each allocation and deallocation requires updating pointers.

# [Buddy Allocator](https://github.com/CHIRANJEET1729DAS/Building-Memory-Allocator-c-/blob/main/header_files/memory_allocator_buddy_method.hpp)

Get ready for the Buddy Allocator! This clever allocator splits memory into blocks of sizes that are powers of two, making allocation and deallocation lightning-fast! When a request comes in, it quickly finds the smallest suitable block and, if necessary, splits it into two buddy blocks, ready to serve future requests.

Pros:

1) Fast Allocation/Deallocation: The binary structure allows for efficient management of memory, leading to rapid allocations and 
                                 deallocations.
2) Reduced Fragmentation: By merging buddy blocks, it significantly minimizes fragmentation in the memory pool.
3) Simplicity: Easy to implement due to its binary structure, making it straightforward to track available blocks.

Cons:

1) Internal Fragmentation: Blocks allocated might be larger than needed, leading to wasted space within those blocks.
2) Power of Two Limitation: Best suited for applications that request memory in powers of two; can be less efficient for arbitrary sizes.

# [Basic Allocator](https://github.com/CHIRANJEET1729DAS/Building-Memory-Allocator-c-/blob/main/header_files/memoryPool.hpp)

The Basic Allocator is the simplest form of memory allocation, ideal for applications that need quick and straightforward memory management. It allocates a fixed block of memory from the operating system and serves requests in a linear fashion.

Pros:

1) Simplicity: Very easy to implement, making it great for educational purposes or simple applications.
2) Low Overhead: Minimal bookkeeping required, leading to reduced management overhead compared to more complex allocators.

Cons:

1) Fragmentation: Can lead to significant fragmentation, as it does not manage free blocks effectively.
2) Limited Flexibility: Not suitable for applications with varying memory needs, as it lacks dynamic memory management capabilities.
