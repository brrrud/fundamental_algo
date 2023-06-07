//
// Created by Рудольф Брайнингер on 03.06.2023.
//

#ifndef FUNDAMENTAL_ALGO_ABSTRACT_HANDLER_H
#define FUNDAMENTAL_ALGO_ABSTRACT_HANDLER_H
#include "request_handler_with_command.h"
#include "request_handler_with_command_chain.h"
template<typename trequest> class abstract_handler
{
    friend class request_handler_with_command_chain<trequest>;

public:
    abstract_handler<trequest> *_next_handler;
public:
    abstract_handler()
            : _next_handler(nullptr)
    {

    }
    virtual ~abstract_handler() = default;
public:
    virtual bool handle(trequest const &) const noexcept = 0;
};
#endif //FUNDAMENTAL_ALGO_ABSTRACT_HANDLER_H
