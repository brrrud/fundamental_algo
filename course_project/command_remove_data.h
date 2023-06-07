//
// Created by Рудольф Брайнингер on 03.06.2023.
//

#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_DATA_H
#include <iostream>
#include "command.h"
#include "logger_singleton.h"
#include "parse.h"
#include <vector>
class command_remove_data final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
public:
    bool can_execute(std::string const &request) noexcept final
    {
        if(!prefix_validation("REMOVE_DATA", request)) return false;
        std::vector<std::string> result_parsed_strings = validation("REMOVE_DATA", request);
        if(result_parsed_strings.size() == 3)
        {
            _pool_name = std::move(result_parsed_strings[0]);
            _scheme_name = std::move(result_parsed_strings[1]);
            _collection_name = std::move(result_parsed_strings[2]);
            return true;
        }
        logger_singleton::get_instance()->get_logger()->log("command_remove_data::can_execute(std::string const &request) called", logger::severity::trace);
        return false;
    }

    void execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_data::execute(std::string const &request) called", logger::severity::trace);
    }
};
#endif //FUNDAMENTAL_ALGO_COMMAND_REMOVE_DATA_H
