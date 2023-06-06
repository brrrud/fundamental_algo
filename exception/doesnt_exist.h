#ifndef FUNDAMENTAL_ALGO_DOESNT_EXIST_H
#define FUNDAMENTAL_ALGO_DOESNT_EXIST_H
#include <iostream>

class doesnt_exist final : public std::exception
{
private:
    std::string _what;
public:
    doesnt_exist(std::string const &method_name)
            : _what("invalid input in " + method_name)
    {

    }

    [[nodiscard]] char const* what() const noexcept override
    {
        return _what.c_str();
    }
};
#endif //FUNDAMENTAL_ALGO_DOESNT_EXIST_H
