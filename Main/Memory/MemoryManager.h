#include <iostream>
#include "StackAllocator.h"

#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H


namespace Icicle {

MemoryManager          IceMemoryManager;

/**
 * Interface for memory manager class
*/
class IMemoryManager
{
    public:
    virtual void* allocate(size_t)= 0;
    virtual void free(void*) = 0;
};

/**
 * make sure limit dynamic memory allocation where possible
 * 
 * 
 * https://developer.ibm.com/tutorials/au-memorymanager/
 * based off this, hook up to allocator
*/
class MemoryManager : public IMemoryManager
{
public:
    MemoryManager() ;
    ~MemoryManager() ;
    void startUp();
    void shutDown();
    void* operator new (size_t size);
    void* operator new[ ] (size_t size);
    //delete should be called AFTER the destructor is called on object
    //this function does not call objects destructor
    void operator delete (void* pointerToDelete);
    void operator delete[ ] (void* arrayToDelete);

    void* allocate(size_t size);
    void free(void* address);

private:
    Resource[RESOURCE_LIMIT] memory;
};
}
#endif
