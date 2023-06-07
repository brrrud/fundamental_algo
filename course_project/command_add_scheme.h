#ifndef FUNDAMENTAL_ALGO_COMMAND_ADD_SCHEME_H
#define FUNDAMENTAL_ALGO_COMMAND_ADD_SCHEME_H
#include <iostream>
#include "command.h"
#include "logger_singleton.h"
#include "parse.h"

class command_add_scheme final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
public:
    bool can_execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_add_scheme::can_execute(std::string const &request) called", logger::severity::trace);
        logger_singleton::get_instance()->get_logger()->log("command_add_collection::can_execute(std::string const &request) called", logger::severity::trace);
        if(!prefix_validation("ADD_SCHEME", request)) return false;
        std::vector<std::string> result_parsed_strings = validation("ADD_SCHEME", request);
        if(result_parsed_strings.size() == 2)
        {
            _pool_name = std::move(result_parsed_strings[0]);
            _scheme_name = std::move(result_parsed_strings[1]);
            return true;
        }
        return false;
    }

    void execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_add_scheme::execute(std::string const &request) called", logger::severity::trace);
    }
};

#endif //FUNDAMENTAL_ALGO_COMMAND_ADD_SCHEME_H
