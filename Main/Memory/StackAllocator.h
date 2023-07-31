
#include "Allocator.h"
#include "../src/IceRoot.h"
#include <stddef.h>
#include "../Math/IcicleMath.h"
#include <string>


/**
 * taken from: https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
 * fill in where necessary, needs pointer math and asserts
 * 
 * This approach avoids memory fragmentation
 * Assumption: levels are loaded once, and whole level fits into 
 * memory in its entirety
 * 
 * TODO: double allocator:
 * The lower stack is used for persistent data loads, while the upper
 * is used for temporary allocations that are freed every frame.
 * 
 * Contains: 
 * A start pointer to the top of the memory arena (allocating from the
 *  top).
 * A start offset pointer to the current top of the stack (allocating 
 * from the top).
 * An end pointer to the top of the memory arena (allocating from the 
 * bottom).
 * An end offset pointer to the current top of the stack (allocating 
 * from the bottom).
 * A header before each allocation.
*/
class StackAllocator : public Allocator
{
    public: 

    StackAllocator (size_t size, void* start);
    ~StackAllocator();

    void* allocate (size_t size, uint8_t alignment) override;
    void* allocate_bottom(size_t size, uint8_t alignment);
    void* allocate_top(size_t size, uint8_t alignment);

    /**
     * To deallocate memory the allocator checks if the address to the memory that you 
     * want to deallocate corresponds to the address of the last allocation made. If 
     * so the allocator accesses the allocation header so it also frees the memory 
     * used to align the allocation and store the allocation header, and it replaces 
     * the pointer to the last allocation made with the one in the allocation header.
    */
    void deallocate(void* p) override;

    private: 

    void* start_top;
    void* offset_top;
    void* start_bottom;
    void* offset_bottom;

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
