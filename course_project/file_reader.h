#ifndef FUNDAMENTAL_ALGO_FILE_READER_H
#define FUNDAMENTAL_ALGO_FILE_READER_H
#include<iostream>
#include<fstream>
#include "request_handler_with_command_chain.h"
#include "request_handler_with_command.h"
#include "command.h"
#include "abstract_handler.h"
#include "command_add_pool.h"
#include "command_add_collection.h"
#include "command_remove_pool.h"
#include "command_add_scheme.h"
#include "command_remove_scheme.h"
#include "command_remove_collection.h"
#include "command_add_data.h"
#include "command_get_data.h"
#include "command_get_data_between.h"
#include "command_update_data.h"
#include "command_remove_data.h"

class file_reader:
{
private:
    std::string _file_name;
    std::ifstream _file;
public:
    explicit file_reader(std::string& file_name): _file_name(std::move(file_name)) {}
    bool file_open(std::string const& _file_stream)
    {
        _file.open(_file_name);
        return  _file.is_open();
    }
    void file_reader_by_line(std::ifstream& opened_file)
    {
        while(getline(opened_file, current_line))
        {

        }
    }
};

#endif //FUNDAMENTAL_ALGO_FILE_READER_H
