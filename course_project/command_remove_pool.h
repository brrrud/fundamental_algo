//
// Created by Рудольф Брайнингер on 03.06.2023.
//

#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
#include "logger_singleton.h"
#include "logger/logger.h"
#include "command.h"
class command_remove_pool final : public command<std::string>
{
private:
    std::string _pool_name;
public:
    bool can_execute(std::string const &request) const noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_pool::can_execute(std::string const &request) called", logger::severity::trace);
        return false;
    }

    void execute(std::string const &request) const noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_pool::execute(std::string const &request) called", logger::severity::trace);
    }
};
#endif //FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
