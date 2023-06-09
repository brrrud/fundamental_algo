#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_COLLECTION_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_COLLECTION_H
#include <iostream>
#include "command.h"
#include "logger_singleton.h"
#include "parse.h"
class command_remove_collection final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
public:
    bool can_execute(std::string const &request)noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_remove_collection::can_execute(std::string const &request) called", logger::severity::trace);
        if(!prefix_validation("REMOVE_COLLECTION", request)) return false;
        std::vector<std::string>result_parsed_strings = validation("REMOVE_COLLECTION", request);
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
        logger_singleton::get_instance()->get_logger()->log("command_remove_collection::execute(std::string const &request) called", logger::severity::trace);
    }
};
#endif //FUNDAMENTAL_ALGO_COMMAND_REMOVE_COLLECTION_H
