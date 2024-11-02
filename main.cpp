#include "/home/chiranjeet/memory_allocator/header_files/memory_allocator_free_list_method.hpp"
#include <iostream>

using namespace std;
 
int main() {
    try {

        MemoryAllocator allocator(1024);

        void* ptr1 = allocator.allocate(128);
        std::cout << "Allocated 128 bytes at " << ptr1 << std::endl;

        void* ptr2 = allocator.allocate(256);
        std::cout << "Allocated 256 bytes at " << ptr2 << std::endl;

        allocator.deallocate(ptr1);
        std::cout << "Deallocated 128 bytes at " << ptr1 << std::endl;

        allocator.deallocate(ptr2);
        std::cout << "Deallocated 256 bytes at " << ptr2 << std::endl;


        void* ptr3 = allocator.allocate(128);
        std::cout << "Re-allocated 128 bytes at " << ptr3 << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
    }

    return 0;
}

