#ifndef TYPENAME_HOLDER
#define TYPENAME_HOLDER

#include <string>

class typename_holder
{

public:

    virtual ~typename_holder() = default;

protected:

    virtual std::string get_typename() const noexcept = 0;

};

#endif //TYPENAME_HOLDER
