#include "memory.h"
#include "exception/not_implemented.h"

void memory::setup_allocation_mode(memory::allocation_mode mode)
{
    throw not_implemented("setup_allocation_mode");
}
size_t memory::get_current_aviable_block_size(void const*) const
{
    throw not_implemented("get_current_aviable_block_size");
}
size_t memory::get_service_part_aviable_block_size()const
{
    throw not_implemented("get_current_aviable_block_size");
}
size_t memory::get_service_part_occupied_block_size()const
{
    throw not_implemented("get_service_part_occupied_block_size");
}
void* const memory::get_first_aviable_block()const
{
    throw not_implemented("get_first_aviable_block");
}
void** memory::get_first_aviable_block_ptr()const
{
    throw not_implemented("get_first_aviable_block_ptr");
}
void* memory::get_next_aviable_block(void*) const
{
    throw not_implemented("get_next_aviable_block");
}
size_t memory::get_occupied_block_size(void * const current_block_address) const
{
    throw not_implemented("get_occupied_block_size");
}
void* memory::get_right_border_of_memory_ptr() const
{
    throw not_implemented("get_right_border_of_memory_ptr");
}
size_t memory::get_service_part_allocator_size() const
{
    throw not_implemented("get_service_part_allocator_size");
}
void* memory::get_previous_aviable_block(void*) const
{
    throw not_implemented("get_previous_aviable_block");
}
void ** memory::get_first_occup_block_ptr() const
{
    throw not_implemented("get_first_occup_block");
}
size_t memory::get_allocator_size() const
{
    throw not_implemented("get_allocator_size()");
}

void **memory::get_first_occup_block() const
{
    throw not_implemented("get_first_occup_block()");
}

void **memory::get_pointer_prev_block(void *target_ptr) const
{
    throw not_implemented("get_pointer_prev_block");
}

void **memory::get_pointer_next_block(void *target_ptr) const
{
    throw not_implemented("get_pointer_next_block");
}
size_t *memory::get_block_size(void *target_ptr) const
{
    throw not_implemented("get_pointer_next_block");
}
std::string memory::get_allocate_mode_string(memory::allocation_mode method) const
{
    std::string allocate_mode;
    switch (method)
    {
    case memory::allocation_mode::first_fit:
        allocate_mode = "the first fit method";
        break;

    case memory::allocation_mode::best_fit:
        allocate_mode = "the best fit method";
        break;
    default:
        allocate_mode = "the worst fit method";
        break;
    }
    return allocate_mode;
}

std::string memory::get_pointer_address(void *target_ptr) const
{

    char str[20];
    memset(str, 0, 20);
    sprintf(str, "%p", target_ptr);
    std::string add;
    add.append(str);
    return add;
}
