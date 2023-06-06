//
// Created by Рудольф Брайнингер on 07.06.2023.
//

#ifndef FUNDAMENTAL_ALGO_OPERATION_NOT_SUPPORTED_H
#define FUNDAMENTAL_ALGO_OPERATION_NOT_SUPPORTED_H

#include<iostream>
class operation_not_supported : public std::exception{
private:
    std::string _what;
public:
    operation_not_supported()
    : _what("operation not supported") { }

    [[nodiscard]] char const* what() const noexcept override
    {
        return _what.c_str();
    }
};


#endif //FUNDAMENTAL_ALGO_OPERATION_NOT_SUPPORTED_H
