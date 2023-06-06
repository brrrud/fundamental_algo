#include <iostream>
#include "logger/logger.h"
#include "logger/logger_builder.h"
#include "course_project/logger_singleton.h"
#include "memory/list_memory.h"
#include "memory.h"
#include "memory/global_heap_allocator.h"
#include <vector>
#include "course_project/command_add_collection.h"

//void memory_global_heap_demo()
//{
//    logger_builder *builder = new logger_builder_concrete();
//    logger *log = builder
//            ->add_stream("file1.txt", logger::severity::trace)
//            ->add_stream("file2.txt", logger::severity::debug)
//            ->add_stream("file3.txt", logger::severity::information)
//            ->construct();
//    list_memory *mem_outer = new list_memory(50000, nullptr, log);
//    list_memory *mem_inner = new list_memory(15000, mem_outer, log, memory_with_fit_allocation::allocation_mode::the_worst_fit);
//
//    int *ptr = reinterpret_cast<int *>(mem_inner->allocate(sizeof(int) * 30));
//    char *ptr1 = reinterpret_cast<char *>(mem_inner->allocate(sizeof(char) * 49));
//    int *ptr2 = reinterpret_cast<int *>(const_cast<void *>(*mem_outer += 0));
//    int *ptr3 = reinterpret_cast<int *>(const_cast<void *>(*mem_outer += 10));
//    auto *ptr4 = reinterpret_cast<unsigned char *>(const_cast<void *>(*mem_outer += 1000));
//
//    srand((unsigned)time(NULL));
//
//    for (auto i = 0; i < 1000; i++)
//    {
//        *(ptr4 + i) = rand() % (sizeof(unsigned char) << 8);
//    }
//
//    *mem_inner -= ptr;
//    *mem_inner -= ptr1;
//    mem_outer->deallocate(ptr2);
//    mem_outer->deallocate(ptr3);
//    mem_outer->deallocate(ptr4);
//
//    delete mem_inner;
//    delete mem_outer;
//    delete log;
//    delete builder;
//}


int main() {
    ifstream
    return 0;
}
