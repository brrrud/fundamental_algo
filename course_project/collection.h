#ifndef FUNDAMENTAL_ALGO_COLLECTION_H
#define FUNDAMENTAL_ALGO_COLLECTION_H
#include "../memory/memory.h"
#include "../trees/associative_container.h"
#include ""
class collection final
{
private:
    memory * _allocator;
    associative_container<key*, value*> * _data;
};
#endif //FUNDAMENTAL_ALGO_COLLECTION_H
