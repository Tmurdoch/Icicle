#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#if ASSERTIONS_ENABLED
// define some inline assembly that causes a break
// into the debugger -- this will be different on each
// target CPU
#define debugBreak() asm { int 3 }
// check the expression and fail if it is false
#define ASSERT(expr) \
if (expr) { } \
else \
{ \
reportAssertionFailure(#expr, \
__FILE__, __LINE__); \
debugBreak(); \
}
#else
#define ASSERT(expr) // evaluates to nothing
#endif

/**
 * compliant with std method allocators?
*/

class Allocator
/**
 * construct + destroy??
*/

{
    public:

    Allocator(size_t size, void* start)
    {
        _start = start;
        _size = size;
        _used_memory = 0;
        _num_allocations = 0;
    }

    virtual ~Allocator()
    {
        ASSERT(_num_allocations == 0 && _used_memory == 0);
        _start = nullptr; _size = 0;
    }

    virtual void* allocate(size_t size, uint8_t alignment = 4) = 0;
    virtual void deallocate(void* p) = 0;
    void* getStart() const { return _start; }
    size_t getSize() const { return _size; }
    size_t getUsedMemory() const { return _used_memory; }
    size_t getNumAllocations() const { return _num_allocations; }

    protected:

    void* _start;
    size_t _size;
    size_t _used_memory;
    size_t _num_allocations;

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
     * this code snippet seems to mix C-style memory manipulation with C++ object construction, 
     * which can be error-prone. Using standard containers like std::vector or smart pointers
     *  like std::unique_ptr might be a more robust and safer way to manage dynamic arrays in 
     * modern C++ code.
    */
    template <class T> T* allocateArray(Allocator& allocator, size_t length)
    {
        ASSERT(length != 0);
        uint8_t headerSize = sizeof(size_t)/sizeof(T);

        //Allocate extra space to store array length in the bytes before array
        T* p ( (T*) allocator.allocate(sizeof(T)*(length + headerSize), __alignof(T)) );
        p = p + headerSize;
        *( ((size_t*)p) - 1 ) = length;

        for (size_t i = 0; i < length; i++)
            new (&p) T;
        
        return p;
    }

    template <class T> void deallocateArray(Allocator& allocator, T* array)
    {
        ASSERT(array != nullptr);
        size_t length = *( ((size_t*)array) - 1 );

        for (size_t i = 0; i < length; i++) array.~T();

        //calculate how much extra memory was allocated to store the length before the array
        uint8_t headerSize = sizeof(size_t)/sizeof(T);
        if (sizeof(size_t)%sizeof(T) > 0)
            headerSize +=1;
        allocator.deallocate(array - headerSize);
    }
}
