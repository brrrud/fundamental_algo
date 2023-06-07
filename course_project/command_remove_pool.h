#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
#include "logger_singleton.h"
#include "logger/logger.h"
#include "command.h"
#include "parse.h"

class command_remove_pool final : public command<std::string>
{
private:
    std::string _pool_name;
public:
    bool can_execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_pool::can_execute(std::string const &request) called", logger::severity::trace);
        if(!prefix_validation("REMOVE_SCHEME", request)) return false;
        std::vector<std::string> result_parsed_strings = validation("REMOVE_SCHEME", request);
        if(result_parsed_strings.size() == 1)
        {
            _pool_name = result_parsed_strings[0];
            return true;
        }
        return false;
    }

    void execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_pool::execute(std::string const &request) called", logger::severity::trace);
    }
};
#endif //FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
