#ifndef FUNDAMENTAL_ALGO_COMMAND_ADD_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_ADD_DATA_H
#include "logger_singleton.h"
#include "command.h"
#include <iostream>
#include "parse.h"
#include "student_definition.h"

class command_add_data final : public command<std::string>
{
private:
    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    student_definition _current_student;
public:
    bool can_execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_add_data::can_execute(std::string const &request) called", logger::severity::trace);
        if(!prefix_validation("ADD_DATA", request)) return false;
        std::vector<std::string>result_parsed_strings = validation("ADD_DATA", request);
        if(result_parsed_strings.size() == 3)
        {
            _pool_name = std::move(result_parsed_strings[0]);
            _scheme_name = std::move(result_parsed_strings[1]);
            _collection_name = std::move(result_parsed_strings[2]);
            _current_student._values.student_name = std::move(result_parsed_strings[3]);
            _current_student._values.student_surname = std::move(result_parsed_strings[4]);
            _current_student._values.student_patronymic = std::move(result_parsed_strings[5]);
            _current_student._values.tutor_name = std::move(result_parsed_strings[6]);
            _current_student._values.tutor_surname = std::move(result_parsed_strings[7]);
            _current_student._values.tutor_patronymic = std::move(result_parsed_strings[8]);
            //_current_student._reporting_format = reporting_format_convert(result_parsed_strings[9]);
            _current_student.keys.
            _current_student._values.event_grade = is_valid_grade(_current_student._reporting_format,
                                                                  result_parsed_strings[10]);

            return true;
        }
        return false;
    }

    void execute(std::string const &request) noexcept final
    {
        logger_singleton::get_instance()->get_logger()->log("command_add_data::execute(std::string const &request) called", logger::severity::trace);
    }
};
#endif //FUNDAMENTAL_ALGO_COMMAND_ADD_DATA_H
