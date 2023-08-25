
#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H


#include "Allocator.h"

#include <stddef.h>
//#include "../Math/IcicleMath.h"
#include "IcicleMath.h"
#include <string>

/**
 * taken from: https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
 * fill in where necessary, needs pointer math and asserts
 * 
 * This approach avoids memory fragmentation
 * Assumption: levels are loaded once, and whole level fits into 
 * memory in its entirety
 *
*/
class StackAllocator : public Allocator
{
    public: 

    StackAllocator (size_t size, void* start);
    ~StackAllocator();

    void* allocate (size_t size, uint8_t alignment) override;

    /**
     * To deallocate memory the allocator checks if the address to the memory that you 
     * want to deallocate corresponds to the address of the last allocation made. If 
     * so the allocator accesses the allocation header so it also frees the memory 
     * used to align the allocation and store the allocation header, and it replaces 
     * the pointer to the last allocation made with the one in the allocation header.
    */
    void deallocate(void* p) override;

    private: 

    void* _current_pos;

    StackAllocator(const StackAllocator&);

    //prevent copies
    StackAllocator& operator=(const StackAllocator&);


    struct AllocationHeader
    {
        #if _DEBUG
            void* prev_address;
        #endif

        uint8_t alignment;
        uint8_t adjustment;
    };

    #if _DEBUG
        void* prev_position;
    #endif

    

};

#endif //STACKALLOCATOR_H
