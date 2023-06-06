#ifndef GLOBAL_HEAP_ALLOC
#define GLOBAL_HEAP_ALLOC

#include "memory.h"
#include "../logger/logger.h"
#include "../logger/logger_holder.h"
#include "typename_holder.h"
#include <stddef.h>

class global_heap_allocator final:
    public memory,
    protected logger_holder,
    protected typename_holder
{
private:

    logger *_logger;

public:

    explicit global_heap_allocator(
        logger *logger = nullptr);
public:

    size_t get_occupied_block_size(
        void * const current_block_address) const override;

    void*  allocate(
        size_t block_size) const override;

    void deallocate(
        void* const block_pointer) const override;

    void setup_allocation_mode(
        memory::allocation_mode mode) override;
private:

    logger *get_logger() const override;

private:

    std::string get_typename() const noexcept override;
};

#endif GLOBAL_HEAP_ALLOC