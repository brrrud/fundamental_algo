#ifndef FUNDAMENTAL_ALGO_PARSE_H
#define FUNDAMENTAL_ALGO_PARSE_H
#include <iostream>
#include <vector>
#include <map>
#include "allocator_type.h"
#include "memory.h"
#include "exception/doesnt_exist.h"
#include "student_definition.h"

std::vector<std::string> chop_string_to_vector(
        std::string::iterator const &begin,
        std::string::iterator const &end,
        const char delim)
{
    std::vector<std::string> out;
    auto it = begin;
    std::string lexem;
    size_t start;
    size_t finish = 0;

    while (it != end)
    {
        if (*it == delim && !lexem.empty())
        {
            out.push_back(std::move(lexem));
        }
        else
        {
            lexem += *it;
        }

        ++it;
    }

    if (!lexem.empty())
    {
        out.push_back(std::move(lexem));
    }

    return out;
}

bool prefix_validation(std::string const& prefix, std::string const& request)
{
    return (request.starts_with(prefix+'(') && request.ends_with(")"));
}

std::vector<std::string>validation(std::string prefix, std::string const& request)
{
    std::string* non_const_request = const_cast<std::string*>(&request);

    std::vector<std::string> chopped_string = chop_string_to_vector(
            non_const_request->begin() + std::string(prefix).length(),
            non_const_request->end(),
            ' ');
    return chopped_string;
}

allocator_type string_to_allocator_type(std::string const& string_allocator_type)
{
    if(string_allocator_type == "global_heap") return allocator_type::global_heap;
    if(string_allocator_type == "border_descriptors") return allocator_type::border_descriptors;
    if(string_allocator_type == "buddy_allocator") return allocator_type::buddy_allocator;
    if(string_allocator_type == "list_memory") return allocator_type::list_memory;
    throw doesnt_exist("string_to_allocator_type");
}

unsigned  int is_unsigned_with_convert(std::string& current_line)
{
    size_t check_size = -1;
    try
    {
        std::stoi(current_line, &check_size);
    }
    catch(std::invalid_argument&)
    {
       throw doesnt_exist("is_unsigned_with_convert");
    }
    catch (std::out_of_range&)
    {
        throw doesnt_exist("is_unsigned_with_convert");
    }
    if (check_size != current_line.size())
    {
        throw doesnt_exist("is_unsigned_with_convert");
    }
    return std::stoi(current_line);
}

memory::allocation_mode allocation_mode_convert(std::string& string_allocation_mode)
{
    if(string_allocation_mode == "first_fit") return memory::allocation_mode::first_fit;
    if(string_allocation_mode == "best_fit") return memory::allocation_mode::best_fit;
    if(string_allocation_mode == "worst_fit") return memory::allocation_mode::worst_fit;
    throw doesnt_exist("allocation_mode_convert");
}

student_definition::reporting_format reporting_format_convert(std::string& string_reporting_format)
{
    if(string_reporting_format == "course_project") return student_definition::reporting_format::course_project;
    if(string_reporting_format == "credit") return student_definition::reporting_format::credit;
    if(string_reporting_format == "exam") return student_definition::reporting_format::exam;
    throw doesnt_exist("reporting_format_convert");
}

unsigned int is_valid_grade(student_definition::reporting_format reporting_format_for_validate, std::string& string_grade)
{
    unsigned int grade;
    try
    {
        grade = is_unsigned_with_convert(string_grade);
    }catch(doesnt_exist())
    {
        throw doesnt_exist("is_valid_grade");
    }
    if ((grade >= 2 && grade <= 5) &&
    ((reporting_format_for_validate == student_definition::reporting_format::exam) ||
    (reporting_format_for_validate == student_definition::reporting_format::course_project)))
    {
        return grade;
    }
    else if ((grade == 0 || grade == 1) &&
    (reporting_format_for_validate == student_definition::reporting_format::credit))
    {
        return grade;
    }
    else
    {
        throw  doesnt_exist("is_valid_grade");
    }
}

#endif //FUNDAMENTAL_ALGO_PARSE_H
