#include "StackAllocator.h"



namespace Icicle {
StackAllocator::StackAllocator(size_t size, void* start) : Allocator(size, start), _current_pos(start)
{
    assert(size > 0);
     #if _DEBUG
         _prev_position = nullptr;
     #endif

}

StackAllocator::~StackAllocator()
{
    #if _DEBUG
        _prev_position = nullptr;
    #endif

    _current_pos = nullptr;
}


/**
Primitive data is said to be aligned if the memory address where it is stored
is a multiple of the size of the primitive. A data aggregate is said to be
aligned if each primitive element in the aggregate is aligned.
**/
uint8_t alignForwardAdjustment(const void* address, uint8_t alignment) {
    uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));
    if (adjustment == alignment) 
        return 0; //already aligned
    
    return adjustment;
}

/**
* Non-template version
**/
uint8_t alignForwardAdjustmentWithHeader(void* address, uint8_t alignment) {
    uint8_t adjustment = alignForwardAdjustment(address, alignment);
    return adjustment;
}


/**
* Template version
* TODO: find out if this is necessary?
* see: https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
**/
template<typename T>
uint8_t alignForwardAdjustmentWithHeader(void* address, uint8_t alignment) {
    if (__alignof(T) > alignment)
         alignment = __alignof(T);

    uint8_t adjustment = sizeof(T) + alignForwardAdjustment(Icicle::ptr_add(address, sizeof(T)), alignment);
    uint8_t adjustment = alignForwardAdjustment(address, alignment);
    return adjustment;
}

void* StackAllocator::allocate(size_t size, uint8_t alignment)
{
    assert(size != 0);

    
    uint8_t adjustment = Icicle::alignForwardAdjustmentWithHeader(_current_pos, alignment);

    //TODO: determine max size allocatable -> store in _size
    if(_used_memory + adjustment + size > _size) return nullptr;

    void* aligned_address = Icicle::ptr_add(_current_pos, adjustment);

    //Add allocation header
    AllocationHeader* header = (AllocationHeader*)(Icicle::ptr_subtract(aligned_address, sizeof(AllocationHeader)));
    header->adjustment = adjustment;

    #if _DEBUG
        header->prev_address = _prev_position;
        _prev_position = aligned_address;
    #endif

    _current_pos = Icicle::ptr_add(aligned_address, size);
    _used_memory += size + adjustment;
    _num_allocations++;

    return aligned_address;
}

void StackAllocator::deallocate(void* p)
{
    assert( p == _prev_position );

    //Access the AllocationHeader in the bytes before p
    AllocationHeader* header = (AllocationHeader*)(Icicle::ptr_subtract(p, sizeof(AllocationHeader)));
    _used_memory -= (uintptr_t)_current_pos - (uintptr_t)p + header->adjustment;
    _current_pos = Icicle::ptr_subtract(p, header->adjustment);

    #if _DEBUG
        _prev_position = header->prev_address;
    #endif

    _num_allocations--;
}
}