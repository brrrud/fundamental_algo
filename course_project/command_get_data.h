#ifndef FUNDAMENTAL_ALGO_COMMAND_GET_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_GET_DATA_H
#include <iostream>
#include "logger_singleton.h"
#include "../logger/logger.h"
#include "command.h"
#include "parse.h"
class command_get_data final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
public:
    bool can_execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_get_data::can_execute(std::string const &request) called", logger::severity::trace);
        if(!prefix_validation("GET_DATA", request)) return false;
        std::vector<std::string> result_parsed_strings = validation("GET_DATA", request);
        if(result_parsed_strings.size() == 3)
        {
            _pool_name = std::move(result_parsed_strings[0]);
            _scheme_name = std::move(result_parsed_strings[1]);
            _collection_name = std::move(result_parsed_strings[2]);
            return true;
        }
        return false;
    }

    void execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_get_data::execute(std::string const &request) called", logger::severity::trace);
    }
};
#endif //FUNDAMENTAL_ALGO_COMMAND_GET_DATA_H
