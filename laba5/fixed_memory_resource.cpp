#include "fixed_memory_resource.h"
#include <algorithm>
#include <stdexcept>

fixed_memory_resource::fixed_memory_resource(size_t total_size) 
    : pool_size(total_size), current_offset(0) {
    memory_pool = ::operator new(total_size);
}

fixed_memory_resource::~fixed_memory_resource() {
    ::operator delete(memory_pool);
}

void* fixed_memory_resource::do_allocate(size_t bytes, size_t alignment) {
    size_t aligned_offset = (current_offset + alignment - 1) & ~(alignment - 1);
    
    if (aligned_offset + bytes > pool_size) {
        throw std::bad_alloc();
    }
    
    void* ptr = static_cast<char*>(memory_pool) + aligned_offset;
    current_offset = aligned_offset + bytes;
    allocated_blocks.push_back(ptr);
    return ptr;
}

void fixed_memory_resource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    auto it = std::find(allocated_blocks.begin(), allocated_blocks.end(), p);
    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
    }
}

bool fixed_memory_resource::do_is_equal(const memory_resource& other) const noexcept {
    return this == &other;
}
