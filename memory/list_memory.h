#ifndef LIST_ALLOC
#define LIST_ALLOC

#include "memory.h"
#include "../logger/logger.h"
#include "../logger/logger_holder.h"
#include "typename_holder.h"
#include <stddef.h>
#include "exception/not_implemented.h"

class list_memory final: public memory,
                         private typename_holder,
                         private logger_holder
                
{

public:
    void * allocate(size_t block_size) const override;
    void deallocate(void * const block_pointer) const override;
private:
    void* const get_first_aviable_block()const override;
    void** get_first_aviable_block_ptr()const override;
    size_t get_current_aviable_block_size(void const*) const override;
    void* get_next_aviable_block(void*) const  override;
    size_t get_service_part_aviable_block_size()const override;
    size_t get_service_part_occupied_block_size()const override;
    void* get_right_border_of_memory_ptr() const override;
    logger* get_logger() const override;
    size_t get_occupied_block_size(void * const current_block_address) const override;
    std::string get_typename() const noexcept override;
    // TODO: move this to memory interface
    void dump_allocator_state(bool is_allocate) const noexcept;
    size_t get_service_part_allocator_size() const override;
    void dump_occupied_block_before_deallocate(void* recent_mem, logger *_logger) const;
private:
    void* _memory;
public:
    list_memory(size_t size,
     memory::allocation_mode allocation_mode,
     logger* logger = nullptr,
     memory* another_allocator = nullptr); // конструктор
    
    ~list_memory(); //деструктор
    list_memory(list_memory const& obj) = delete; // копирование
    list_memory& operator=(list_memory const& obj) = delete; //присваивание 
    explicit list_memory(list_memory&&); //конструктор перемещения
    list_memory& operator=(list_memory&& obj); //присваивание перемещением 
private:
    void destroy();
    void move(list_memory&&);
};
#endif LIST_ALLOC
// конструктор копирования(3 случая)  A a = b; A a(b);   A foo(A obj); C++11> // до с++11 прятали private
// lvalue rvalue
//inline