#pragma once

#include <iostream>
#include "StackAllocator.hpp"
#include "Resource.hpp"

#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#define RESOURCE_LIMIT 1000 //1 gb?
#define DEFAULT_MEM_SIZE 100

namespace Icicle {



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
    private:
    
    Resource memory[RESOURCE_LIMIT] ;
    
    public:
    MemoryManager() ;
    ~MemoryManager() ;

    static MemoryManager* MemInstancePtr;
    static void startUp();
    void shutDown();
    //delete should be called AFTER the destructor is called on object
    //this function does not call objects destructor

    void* allocate(size_t size);
    void free(void* address);
    void operator=(const MemoryManager &) = delete;
    


    /**
     * Note: calling this initially will default to 100 memsize
     * TODO: implement a constructor function
    */
    static MemoryManager* getInstance() {
        if (MemInstancePtr == NULL) 
        {
            MemInstancePtr = new MemoryManager();
        }
        return MemInstancePtr;
    }
    
    


};
}
#endif
