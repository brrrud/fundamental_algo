#include"buddy_allocator.h"
//[size, (+-)] info occupied block
//[size, (+-), prev, next] info availble block
//dump памяти такой же

logger* buddy_allocator::get_logger() const noexcept
{
    return *reinterpret_cast<logger**>(reinterpret_cast<unsigned char*>(_trusted_memory) + sizeof(unsigned char));
}

memory* buddy_allocator::get_memory() const noexcept
{
    return *reinterpret_cast<memory **>(_trusted_memory);
}

std::string buddy_allocator::get_typename() const noexcept
{
    return "buddy allocator";
}

buddy_allocator::buddy_allocator(
        unsigned char size_as_power_of_2,
        memory::allocation_mode mode,
        logger *log,
        memory *outer_allocator)
    {

        if (size_as_power_of_2 > 127)
        {
            throw memory::dealloc_fail();
        }
        size_t target_size = 1 << size_as_power_of_2;
        if (target_size < 1 + 2 * sizeof(void *))
        {
            throw memory::dealloc_fail();
            //throw std::logic_error("Few memory");
        }

        target_size += get_service_part_allocator_size();

        _trusted_memory = outer_allocator == nullptr
            ? ::operator new(target_size)
            : outer_allocator->allocate(target_size);
        auto* size_of_allocator = reinterpret_cast<unsigned char*>(_trusted_memory);
        *size_of_allocator = size_as_power_of_2;

        auto * allocator_space = reinterpret_cast<memory **>(size_of_allocator + 1);
        *allocator_space = outer_allocator;

        auto * logger_space = reinterpret_cast<logger **>(allocator_space + 1);
        *logger_space = log;

        auto * mode_space = reinterpret_cast<memory::allocation_mode *>(logger_space + 1);
        *mode_space = mode;

        auto * first_aviable_block = reinterpret_cast<void **>(mode_space + 1);
        *first_aviable_block = first_aviable_block + 1;

        auto * size_and_aviability = reinterpret_cast<unsigned char *>(*first_aviable_block);
        *size_and_aviability = static_cast<unsigned char>(size_as_power_of_2 << 1);
        auto * previous_to_single_block_ptr = reinterpret_cast<void **>(size_and_aviability + 1);
        auto * next_to_single_block_ptr = previous_to_single_block_ptr + 1;

        *previous_to_single_block_ptr = *next_to_single_block_ptr = nullptr;

        this->trace_with_guard("Buddy system allocator initialized!");
    }

buddy_allocator::~buddy_allocator()
{
    auto * outer_allocator = get_memory();
    auto * got_logger = get_logger();
    outer_allocator == nullptr
        ? ::operator delete(_trusted_memory)
        : outer_allocator->deallocate(_trusted_memory);
    if (got_logger != nullptr)
    {
        got_logger->log("Destructor of " + get_typename() + " executed successfully", logger::severity::trace);
    }
}

size_t buddy_allocator::get_service_part_allocator_size() const
{
    return sizeof(unsigned char) + sizeof(memory::allocation_mode) + sizeof(logger*) + sizeof(memory*) + sizeof(void*);
}

bool buddy_allocator::is_aviable(void* target_block) const
{
    return (*reinterpret_cast<unsigned char*>(target_block)) & 1;
}

size_t buddy_allocator::get_service_part_occupied_block_size()const
{
   return sizeof(unsigned char);
}

unsigned char buddy_allocator::get_nearest_size_pow2(size_t size) const
{
    return static_cast<unsigned char>(floor(log2(size) + 1));
}

size_t buddy_allocator::get_occupied_block_size(void * const current_block_address) const //TODO: [переписать const в функции get_occupied_block_size()] [сделать как в функции get_current_aviable_block_size() -> void const* target_aviable_block]
{
    return static_cast<size_t>(*reinterpret_cast<unsigned char*>(current_block_address) >> 1);
}

size_t buddy_allocator::get_service_part_aviable_block_size()const
{
    return sizeof(unsigned char) + 2 * sizeof(void*);
}
//сделать функцию compact на уровне buddy_alloc.h
unsigned char buddy_allocator::compact_block_size_and_occupancy(unsigned char mem_size_as2, bool block_occupancy)const
{
    return static_cast<unsigned char>((mem_size_as2 << 1)|(block_occupancy & 1));
}

size_t buddy_allocator::get_current_aviable_block_size(void const* target_aviable_block) const
{
    return 1 << (static_cast<size_t>((*reinterpret_cast<unsigned char*>(const_cast<void*>(target_aviable_block))) >> 1));
}

void** buddy_allocator::get_first_aviable_block_ptr()const
{
    return reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(_trusted_memory) + get_service_part_allocator_size() - sizeof(void*));
}

void* const buddy_allocator::get_first_aviable_block()const
{
    return *get_first_aviable_block_ptr();
}
///////////////////////////////////////////////////////////////////////////
void* buddy_allocator::get_previous_aviable_block(void* target_block) const //TODO: переделать на (void const* target_block)
{
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(target_block) + 1);
}

void* buddy_allocator::get_next_aviable_block(void* target_block) const //TODO: переделать на (void const* target_block)
{
    return *(reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(target_block) + 1) + 1);
}

///////////////////////////////////////////////////////////////////////////

//unsigned char compact_block_size()

void * buddy_allocator::allocate(size_t block_size) const
{
    auto overridden_block_size = block_size;
    if (overridden_block_size < sizeof(void*))
    {
        overridden_block_size = sizeof(void*);
    }
    memory::allocation_mode current_alloc_mode = *reinterpret_cast<memory::allocation_mode*>(reinterpret_cast<unsigned char*>(_trusted_memory)+sizeof(size_t)+sizeof(memory*)+sizeof(logger*));
    void* current_aviable_block = get_first_aviable_block();
    void* prev_block = nullptr;
    void* target_block = nullptr,
     *prev_to_target_block = nullptr,
     *next_to_target_block = nullptr;
    auto curr_sz = 0;
    while (current_aviable_block != nullptr)
    {
        void* next_block = get_next_aviable_block(current_aviable_block);
        curr_sz = get_current_aviable_block_size(current_aviable_block);
        if (curr_sz + sizeof(void*) >= overridden_block_size)
        {
            if (current_alloc_mode == memory::allocation_mode::first_fit ||
                current_alloc_mode == memory::allocation_mode::best_fit && (target_block == nullptr || curr_sz < get_current_aviable_block_size(target_block)) ||
                current_alloc_mode == memory::allocation_mode::worst_fit && (target_block == nullptr || curr_sz > get_current_aviable_block_size(target_block)))
            {
                target_block = current_aviable_block;
                prev_to_target_block = prev_block;
                next_to_target_block = next_block;
            }

            if (current_alloc_mode == memory::allocation_mode::first_fit)
            {
                break;
            }
        }

        prev_block = current_aviable_block;
        current_aviable_block = next_block;
    }

    if (target_block == nullptr)
    {
        //TODO: переделать проброс исключений на пользовательский из class memory
        throw std::bad_alloc();
    }

    while((curr_sz >= block_size + get_service_part_occupied_block_size())
        && ((curr_sz >> 1) >= block_size + get_service_part_occupied_block_size() ))
    {
        auto* const left_buddy_adress = reinterpret_cast<unsigned char*>(target_block);
        auto* const right_buddy_adress = left_buddy_adress + (curr_sz >>= 1);
        *left_buddy_adress = *right_buddy_adress = ((*left_buddy_adress >> 1) - 1) << 1;
        *(reinterpret_cast<void**>(right_buddy_adress + 1) + 1) = get_next_aviable_block(left_buddy_adress);
        *(reinterpret_cast<void**>(left_buddy_adress + 1) + 1) = reinterpret_cast<void*>(right_buddy_adress);
        *reinterpret_cast<void**>(right_buddy_adress + 1)  = reinterpret_cast<void*>(left_buddy_adress);
    }


    *reinterpret_cast<unsigned char*>(target_block) = compact_block_size_and_occupancy(static_cast<unsigned char>(static_cast<unsigned char>(std::log2(curr_sz))), true);
    if(get_previous_aviable_block(target_block) == nullptr)
    {
        *get_first_aviable_block_ptr() = get_next_aviable_block(target_block);
    }
    //TODO: dump all

    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(target_block) + 1);

}

void buddy_allocator::dump_allocator_state(bool is_allocate) const noexcept
{
    auto *log = get_logger();
    if (log == nullptr)
    {
        return;
    }

    auto allocator_memory_size = 2 << *reinterpret_cast<size_t *>(get_memory());
    std::string constructed_state_string("|");
    auto *current_aviable_block = get_first_aviable_block();
    auto *current_any_block = reinterpret_cast<unsigned char *>(_trusted_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(logger *) + sizeof(allocation_mode) + sizeof(void *);

    while (current_any_block - reinterpret_cast<unsigned char *>(_trusted_memory) < allocator_memory_size)
    {
        size_t any_block_size;
        if (current_any_block == current_aviable_block)
        {
            constructed_state_string += "avlbl " + std::to_string(any_block_size = get_current_aviable_block_size(current_any_block)) + '|';
            current_aviable_block = get_next_aviable_block(current_aviable_block);
            any_block_size += get_service_part_aviable_block_size();
        }
        else
        {
            constructed_state_string += "occpd " + std::to_string(any_block_size = get_occupied_block_size(current_any_block)) + '|';
            any_block_size += get_service_part_occupied_block_size();
        }
        current_any_block += any_block_size;
    }

    log->log(std::string("Memory state after ") + (is_allocate
        ? ""
        : "de") + "allocation operation: " + constructed_state_string, logger::severity::debug);
}

void buddy_allocator::deallocate(void * const block_pointer) const
{

}