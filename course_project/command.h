#ifndef FUNDAMENTAL_ALGO_COMMAND_H
#define FUNDAMENTAL_ALGO_COMMAND_H
template<typename trequest> class command
{
public:
    virtual ~command() = default;
public:
    virtual bool can_execute(trequest const &) noexcept = 0;
    virtual void execute(trequest const &) noexcept = 0;
};

#endif //FUNDAMENTAL_ALGO_COMMAND_H
