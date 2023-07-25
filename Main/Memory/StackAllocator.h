
#include "Allocator.h"
#include "../src/IceRoot.h"
#include <stddef.h>


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
*/
class StackAllocator : public Allocator
{
    public: 

    StackAllocator (size_t size, void* start);
    ~StackAllocator();

    void* allocate(size_t size, u8 alignment) override;
    void deallocate(void* p) override;

    private: 

    StackAllocator(const StackAllocator&);

    //prevent copies
    StackAllocator& operator=(const StackAllocator&);

    struct AllocationHeader
    {
        #if _DEBUG
            void* prev_address;
        #endif

        u8 alignment;
    };

    #if _DEBUG
        void* prev_position;
    #endif

    void* _current_pos;

};
