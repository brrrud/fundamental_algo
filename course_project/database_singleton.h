#ifndef FUNDAMENTAL_ALGO_DATABASE_SINGLETON_H
#define FUNDAMENTAL_ALGO_DATABASE_SINGLETON_H
#include "../memory/memory.h"
#include "logger_singleton.h"
#include "../logger/logger.h"
#include "comparers.h"
#include "allocator_type.h"
#include "tree_type.h"
#include "student_definition.h"
#include "./trees/associative_container.h"
#include "./trees/bplus_tree.h"

class database_singleton
{
private:
    class stdpair_int_int_comparer final
    {
    private:
        int_comparer _int_comparer;
    public:
        int operator()(std::pair<int, int> const &left, std::pair<int, int> const &right)
        {
            auto user_id_comparison_result = _int_comparer(left.first, right.first);
            if (user_id_comparison_result != 0)
            {
                return user_id_comparison_result;
            }

            return _int_comparer(left.second, right.second);
        }
    };
private:
    static database_singleton *_instance;
public:
    static database_singleton *get_instance()
    {
        if (_instance == nullptr)
        {
            _instance = new database_singleton();
        }

        return _instance;
    }
private:
    associative_container<std::string, std::pair<associative_container<std::string,
    associative_container<std::string, associative_container<std::pair<int, int>,
    student_definition *> *> *> *, memory *> > *_database_entrypoint;
private:
    database_singleton()
    {
        _database_entrypoint = new bplus_tree<std::string,
        std::pair<associative_container<std::string,
        associative_container<std::string,
        associative_container<std::pair<int, int>,
        student_definition *> *> *> *, memory *>,
        stdstring_comparer>(10);
    }
public:
    ~database_singleton()
    {
        delete _database_entrypoint;
    }
    database_singleton(database_singleton const &) = delete;
    database_singleton(database_singleton &&) = delete;
    database_singleton &operator=(database_singleton const &) = delete;
    database_singleton &operator=(database_singleton &&) = delete;
public:
    void add_pool(
            std::string const &pool_name,
            allocator_type pool_allocator_type,
            unsigned int pool_allocator_size,
            memory::allocation_mode pool_allocator_allocation_mode,
            tree_type tree_type, )
    {
        try {
            memory *allocator = nullptr;
//            switch (pool_allocator_type) {
//                case allocator_type::global_heap:
//                    allocator = new memory_from_global_heap(logger_singleton::get_instance()->get_logger());
//                    break;
//                case allocator_type::sorted_list:
//                    allocator = new memory_with_sorted_list_deallocation(pool_allocator_size, nullptr,
//                                                                         logger_singleton::get_instance()->get_logger(),
//                                                                         pool_allocator_allocation_mode);
//                    break;
//                case allocator_type::boundary_tags:
//                    allocator = new memory_with_boundary_tags_deallocation(pool_allocator_size, nullptr,
//                                                                           logger_singleton::get_instance()->get_logger(),
//                                                                           pool_allocator_allocation_mode);
//                    break;
//                case allocator_type::buddy_system:
//                    allocator = new memory_buddy_system(pool_allocator_size, nullptr,
//                                                        logger_singleton::get_instance()->get_logger(),
//                                                        pool_allocator_allocation_mode);
//                    break;
//            }

            _database_entrypoint->insert(pool_name,
                                         std::move(std::make_pair(new bplus_tree<std::string, associative_container<std::string, associative_container<std::pair<int, int>,
                                                 student_definition *> *> *, stdstring_comparer>(10), allocator)));
            switch (tree_type) {
                case tree_type::b_plus_tree:

                    break;
                case tree_type::avl_tree:
                    break;
                case tree_type::red_black_tree:
                    break;
                case tree_type::b_tree:
                    break;

            }
        }
        catch (search_tree<std::string, std::pair<associative_container<std::string, associative_container<std::string, associative_container<std::pair<int, int>, delivery_info *> *> *> *, memory *>, stdstring_comparer>::insertion_exception const &ex)
        {
            // TODO: ?!
        }
    }
};
#endif //FUNDAMENTAL_ALGO_DATABASE_SINGLETON_H
