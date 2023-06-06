#include "logger_builder_concrete.h"
#include "logger_concrete.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <ctime>

logger_builder *logger_builder_concrete::add_stream(
    std::string const &path,
    logger::severity severity)
{
    _construction_info[path] = severity;

    return this;
}

logger_builder *logger_builder_concrete::add_from_json(std::string const & file_json_format){
    
    logger::severity curr_severity;
    std::ifstream f(file_json_format);
    if(!f.is_open()){
        throw std::logic_error("error with open\n");
    }
    nlohmann::json data = nlohmann::json::parse(f);

    for (auto& el : data.items()){
        if(el.value() == "warning") curr_severity = logger::severity::warning;
        else if(el.value() == "critical") curr_severity = logger::severity::critical;
        else if(el.value() == "error") curr_severity = logger::severity::error;
        else if(el.value() == "trace") curr_severity = logger::severity::trace;
        else if(el.value() == "debug") curr_severity = logger::severity::debug;
        else if(el.value() == "information") curr_severity = logger::severity::information;
        else continue;
        _construction_info[el.key()] = curr_severity;
    }
    return this;
}


logger *logger_builder_concrete::construct() const
{
    return new logger_concrete(_construction_info);
}
