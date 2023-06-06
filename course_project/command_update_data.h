//
// Created by Рудольф Брайнингер on 03.06.2023.
//

#ifndef FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H
#include "logger_singleton.h"
#include "logger/logger.h"
#include <iostream>
#include "command.h"

class command_update_data final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
public:
    bool can_execute(std::string const &request) const noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_update_data::can_execute(std::string const &request) called", logger::severity::trace);
        return false;
    }

    void execute(std::string const &request) const noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_update_data::execute(std::string const &request) called", logger::severity::trace);
    }
};

#endif //FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H
