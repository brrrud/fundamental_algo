cmake_minimum_required(VERSION 3.25)
project(fundamental_algo)

set(CMAKE_CXX_STANDARD 20)
include_directories(.)
find_package(nlohmann_json 3.11.2 REQUIRED)

add_executable(fundamental_algo
        logger/logger.h
        logger/logger_builder.h
        logger/logger_holder.h
        logger/logger_concrete.h
        logger/logger_builder_concrete.h
        main.cpp
        course_project/logger_singleton.h logger/logger_holder.cpp logger/logger_builder_concrete.cpp logger/logger_builder.cpp
        logger/logger_concrete.cpp logger/logger.cpp course_project/command_add_pool.h course_project/command_remove_pool.h
        course_project/command_add_scheme.h course_project/command_remove_scheme.h course_project/command_add_collection.h
        course_project/command_remove_collection.h course_project/command_add_data.h
        course_project/command_get_data.h course_project/command_get_data_between.h course_project/command_update_data.h
        course_project/command_remove_data.h course_project/abstract_handler.h course_project/request_handler_with_command.h
        course_project/command.h course_project/request_handler_with_command_chain.h course_project/comparers.h memory/memory.h
        memory/memory.cpp course_project/allocator_type.h course_project/tree_type.h
        course_project/student_definition.h memory/list_memory.h memory/list_memory.cpp
        memory/global_heap_allocator.h memory/global_heap_allocator.cpp course_project/parse.h course_project/file_reader.h exception/doesnt_exist.h
        exception/operation_not_supported.h
        course_project/database_singleton.h course_project/collection.h
        trees/associative_container.h trees/search_tree.h)

target_link_libraries(fundamental_algo PRIVATE nlohmann_json::nlohmann_json)
