#ifndef FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H

#include "logger_singleton.h"
#include "logger/logger.h"
#include <iostream>
#include "command.h"
#include "parse.h"

class command_update_data final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
public:
    bool can_execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_update_data::can_execute(std::string const &request) called", logger::severity::trace);
        if(!prefix_validation("UPDATE_DATA", request)) return false;
        std::vector<std::string>result_parsed_strings = validation("UPDATE_DATA", request);
        if(result_parsed_strings.size() == 3)
        {
            _pool_name = result_parsed_strings[0];
            _scheme_name = result_parsed_strings[1];
            _collection_name = result_parsed_strings[2];
        }
        return false;
    }

    void execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_update_data::execute(std::string const &request) called", logger::severity::trace);
    }
};

#endif //FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H
