#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_SCHEME_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_SCHEME_H
#include "logger_singleton.h"
#include "logger/logger.h"
#include <iostream>
#include "command.h"

class command_remove_scheme final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
public:
    bool can_execute(std::string const &request) const noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_scheme::can_execute(std::string const &request) called", logger::severity::trace);
        return false;
    }

    void execute(std::string const &request) const noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_scheme::execute(std::string const &request) called", logger::severity::trace);
    }
};

#endif //FUNDAMENTAL_ALGO_COMMAND_REMOVE_SCHEME_H
