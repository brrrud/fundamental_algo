#ifndef BORDER_DESCRIPTORS_MEMORY_H
#define BORDER_DESCRIPTORS_MEMORY_H

#include <iostream>
#include "../logger/logger.h"
#include "../logger/logger_concrete.h"
#include "../logger/logger_holder.h"
#include <cstring>
#include "memory.h"

class border_descriptors_memory final : public memory, private logger_holder
{
private:
    void *_all_memory;

private:
    std::size_t get_service_part_allocator_size() const override;
    void **get_first_occup_block() const override;
    std::size_t get_allocator_size() const override;
    std::size_t get_service_part_occupied_block_size() const override;
    void **get_pointer_prev_block(void *target_ptr) const override;
    void **get_pointer_next_block(void *target_ptr) const override;
    size_t *get_block_size(void *target_ptr) const override;

    void dump_allocator_state(bool is_allocate) const noexcept;
    logger *get_logger() const noexcept override;


    void debug_alloc(const void *target_ptr) const;


    std::pair<void *, size_t> get_aviable_block_address_and_size(
        void *const previous_occupied_block_address,
        void *const next_occupied_block_address) const ;

public:
    void *allocate(size_t target_size) const override;

public:
    void deallocate(void *const target_to_dealloc) const override;

public:
    border_descriptors_memory(logger *log, memory *allocator, size_t size, memory::allocation_mode method);

public:
    border_descriptors_memory(border_descriptors_memory const &) = delete;
    border_descriptors_memory &operator=(border_descriptors_memory const &) = delete;

public:
    ~border_descriptors_memory();
};

#endif // BORDER_DESCRIPTORS_MEMORY_H