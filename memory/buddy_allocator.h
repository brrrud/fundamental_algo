#ifndef BUDDY_ALLOCATOR
#define BUDDY_ALLOCATOR

#include <cmath>
#include"memory.h"
#include "typename_holder.h"
#include "exception/not_implemented.h"
#include "../logger/logger.h"
#include "../logger/logger_holder.h"
#include "memory_holder.h"

class buddy_allocator final : public memory,
                              private logger_holder,
                              private memory_holder,
                              private typename_holder
{
public:
    buddy_allocator(
        unsigned char size_as_power_of_2,
        memory::allocation_mode mode = memory::allocation_mode::first_fit,
        logger *log = nullptr,
        memory *outer_allocator = nullptr);

    buddy_allocator(buddy_allocator const &obj) = delete;
    ~buddy_allocator()noexcept;
public:
    void * allocate(size_t block_size) const override;
    void deallocate(void * const block_pointer) const override;
    logger* get_logger() const noexcept override;
    memory* get_memory() const noexcept override;
    std::string get_typename() const noexcept override;
    size_t get_service_part_allocator_size() const override;
    size_t get_occupied_block_size(void * const current_block_address) const override;
    size_t get_service_part_occupied_block_size()const override;
    void* get_next_aviable_block(void*) const override;
    void** get_first_aviable_block_ptr() const override;
    void* const get_first_aviable_block() const override;
    void* get_previous_aviable_block(void*) const override;
    size_t get_current_aviable_block_size(void const*) const override;
    size_t get_service_part_aviable_block_size()const override;
public:
    bool is_aviable(void* target_block) const;
    unsigned char get_nearest_size_pow2(size_t size) const;
    unsigned char compact_block_size_and_occupancy(unsigned char mem_size_as2, bool block_occupancy)const;
    void dump_allocator_state(bool is_allocate) const noexcept;
private:
    void* _trusted_memory;
private:
    //size_t get_service_part_allocator_size() const override;
};

#endif BUDDY_ALLOCATOR
