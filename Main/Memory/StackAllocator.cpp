#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t size, void* start) : Allocator(size, start), _current_pos(start)
{
    ASSERT(size > 0);
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

void* StackAllocator::allocate(size_t size, uint8_t alignment)
{
    ASSERT(size != 0);
    uint8_t adjustment = Math::alignForwardAdjustmentWithHeader(_current_pos, alignment, sizeof(AllocationHeader));

    if(_used_memory + adjustment + size > _size) return nullptr;

    void* aligned_address = Math::ptr_add(_current_pos, adjustment);

    //Add allocation header
    AllocationHeader* header = (AllocationHeader*)(Math::ptr_subtract(aligned_address, sizeof(AllocationHeader)));
    header->adjustment = adjustment;

    #if _DEBUG
        header->prev_address = _prev_position;
        _prev_position = aligned_address;
    #endif

    _current_pos = Math::ptr_add(aligned_address, size);
    _used_memory += size + adjustment;
    _num_allocations++;

    return aligned_address;
}

void StackAllocator::deallocate(void* p)
{
    ASSERT( p == _prev_position );

    //Access the AllocationHeader in the bytes before p
    AllocationHeader* header = (AllocationHeader*)(Math::ptr_subtract(p, sizeof(AllocationHeader)));
    _used_memory -= (uintptr_t)_current_pos - (uintptr_t)p + header->adjustment;
    _current_pos = Math::ptr_subtract(p, header->adjustment);

    #if _DEBUG
        _prev_position = header->prev_address;
    #endif

    _num_allocations--;
}