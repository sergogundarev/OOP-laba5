#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>

class fixed_memory_resource : public std::pmr::memory_resource {
private:
    void* memory_pool;
    size_t pool_size;
    size_t current_offset;
    std::vector<void*> allocated_blocks;
    
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const memory_resource& other) const noexcept override;

public:
    fixed_memory_resource(size_t total_size);
    ~fixed_memory_resource();
};
