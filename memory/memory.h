#ifndef _MEMORY
#define _MEMORY

#include <stddef.h>
#include "../logger/logger.h"
#include <iostream>

class memory{
public:
    enum class allocation_mode
    {
        best_fit,
        first_fit,
        worst_fit
    };
    class dealloc_fail final : public std::exception
    {
    public:
        char const* what()const noexcept override
        {
            return "Failed to deallocate";
        }
    };

public:
    std::string get_allocate_mode_string(allocation_mode method) const;
    std::string get_pointer_address(void *target_ptr) const;


public:
    virtual void * allocate(std::size_t block_size) const = 0;
    virtual void deallocate(void * const block_pointer) const = 0;

    virtual std::size_t get_occupied_block_size(void * const current_block_address) const;
    virtual std::size_t get_current_aviable_block_size(void const*) const;
    virtual std::size_t get_service_part_aviable_block_size()const;
    virtual std::size_t get_service_part_occupied_block_size()const;
    virtual std::size_t get_allocator_size() const;
    virtual std::size_t get_service_part_allocator_size() const;
    
    virtual void setup_allocation_mode(memory::allocation_mode mode);
    virtual void* const get_first_aviable_block()const;

    virtual void** get_first_aviable_block_ptr()const;
    virtual void** get_first_occup_block_ptr() const;
    virtual void **get_pointer_prev_block(void *target_ptr) const;
    virtual void **get_pointer_next_block(void *target_ptr) const;


    virtual void **get_first_occup_block() const;

    virtual void* get_next_aviable_block(void*) const;
    virtual void* get_previous_aviable_block(void*) const;
    virtual void* get_right_border_of_memory_ptr() const;

    virtual size_t *get_block_size(void *target_ptr) const;
    
public:
    virtual ~memory() noexcept = default;
};

#endif //_MEMORY
