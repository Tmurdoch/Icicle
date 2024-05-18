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
 * A typical pattern of working with Vulkan involves 
 * performing large (e.g. 16 MB – 256 MB depending on how 
 * dynamic the memory requirements are) allocations using 
 * vkAllocateMemory, and performing suballocation of objects
 *  within this memory, effectively managing it yourself.
 *  Critically, the application needs to handle alignment
 *  of memory requests correctly, as well as 
 * bufferImageGranularity limit that restricts valid 
 * configurations of buffers and images.
 * 
 * track resource type, adding padding if necessary for
 * image resources that require it
 * 
 * see https://zeux.io/2020/02/27/writing-an-efficient-vulkan-renderer/
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
