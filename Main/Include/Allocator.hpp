
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#ifndef ALLOCATOR_H
#define ALLOCATOR_H


namespace Icicle {
/*
 * compliant with std method allocators?
*/

class Allocator
/**
 * USAGE: 
 * 
 * 
 * Pre-allocate a memory block of size x bytes
 * char memoryBlock[x];

 * Create an allocator instance using the pre-allocated memory block
 * Allocator myAllocator(sizeof(memoryBlock), memoryBlock);

 * Now you can use myAllocator to manage memory within the provided memoryBlock.
*/

{

    protected:

    void* _start;
    size_t _size;
    size_t _used_memory;
    size_t _num_allocations;
    public:


    public:
    Allocator(size_t size, void* start)
    {
        _start = start; //starting address of memory block
        _size = size; //size of memory block
        _used_memory = 0;
        _num_allocations = 0;
    }

    ~Allocator();
    

    virtual void* allocate(size_t size, uint8_t alignment = 4) = 0;
    virtual void deallocate(void* p) = 0;
    void* getStart() const { return _start; }
    size_t getSize() const;
    size_t getUsedMemory() const;
    size_t getNumAllocations() const;

    

};

namespace allocator
{
    template <class T> T* allocateNew(Allocator& allocator)
    {
        return new (allocator.allocate(sizeof(T), __alignof(T))) T;
    }

    template <class T> T* allocateNew(Allocator& allocator, const T& t) {
        return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
    }

    template <class T> void deallocateDelete(Allocator& allocator, T& object)
    {
        object.~T();
        allocator.deallocate(&object);
    }


    /**
     * @PREREQS: length != 0, check before calling
     * 
     * this code snippet seems to mix C-style memory manipulation with C++ object construction, 
     * which can be error-prone. Using standard containers like std::vector or smart pointers
     *  like std::unique_ptr might be a more robust and safer way to manage dynamic arrays in 
     * modern C++ code.
    */
    template <class T> T* allocateArray(Allocator& allocator, size_t length)
    {
        // _assert(length != 0);
        uint8_t headerSize = sizeof(size_t)/sizeof(T);

        //Allocate extra space to store array length in the bytes before array
        T* p ( (T*) allocator.allocate(sizeof(T)*(length + headerSize), __alignof(T)) );
        p = p + headerSize;
        *( ((size_t*)p) - 1 ) = length;

        for (size_t i = 0; i < length; i++)
            new (&p) T;
        
        return p;
    }


    /**
    *  * @PREREQS: array != nullptr, check before calling
    */
    template <class T> void deallocateArray(Allocator& allocator, T* array)
    {
        // ASSERT(array != nullptr);
        size_t length = *( ((size_t*)array) - 1 );

        for (size_t i = 0; i < length; i++) array.~T();

        //calculate how much extra memory was allocated to store the length before the array
        uint8_t headerSize = sizeof(size_t)/sizeof(T);
        if (sizeof(size_t)%sizeof(T) > 0)
            headerSize +=1;
        allocator.deallocate(array - headerSize);
    }
}
}

#endif

