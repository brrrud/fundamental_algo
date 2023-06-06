#ifndef TEST_MEMORY
#define TEST_MEMORY

#include<list>
#include<iostream>
#include"../logger/logger_builder_concrete.h"
#include"list_memory.h"
#include"../logger/logger.h"

void test1(memory* all1)
{
    std::list<void *> allocated_blocks;
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 250000; i++)
    {
        switch (rand() % 2)
        {
            case 0:
                try
                {
                    allocated_blocks.push_back(all1->allocate(rand() % 201 + 150));
                }
                catch (std::bad_alloc const &ex)
                {
                    std::cout << i << " allocate failed? да и хуй с ним =)" << std::endl;
                }
                break;
            case 1:
                try
                {
                    if (allocated_blocks.empty())
                    {
                        std::cout << i << " nothing to deallocate" << std::endl;
                        continue;
                    }

                    auto ptr_to_deallocate_index = rand() % allocated_blocks.size();
                    auto it = allocated_blocks.begin();
                    std::advance(it, ptr_to_deallocate_index);
                    all1->deallocate(*it);
                    allocated_blocks.erase(it);
                }
                catch (memory::dealloc_fail const &ex)
                {
                    std::cout << i << " deallocate failed" << std::endl;
                }
                break;
        }
    }
    while (!allocated_blocks.empty())
    {
        auto ptr_to_deallocate_index = rand() % allocated_blocks.size();
        auto it = allocated_blocks.begin();
        std::advance(it, ptr_to_deallocate_index);
        all1->deallocate(*it);
        allocated_blocks.erase(it);
    }
}



#endif TEST_MEMORY