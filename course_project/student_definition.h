#ifndef STUDENT_DEFINITION
#define STUDENT_DEFINITION
#include<iostream>
//     session_id ///student_id  ///subject_name for tuple 
struct student_definition
{
    enum class reporting_format{
        course_project,
        credit,
        exam
    };
    std::tuple<unsigned int, unsigned int, reporting_format, std::string> keys;
    struct values
    {
        std::string student_name;
        std::string student_surname;
        std::string student_patronymic;
        std::string event_day;
        std::string event_start;
        unsigned int event_grade;
        std::string tutor_name;
        std::string tutor_surname;
        std::string tutor_patronymic;
    };
    values _values;

};
#endif//STUDENT_DEFINITION