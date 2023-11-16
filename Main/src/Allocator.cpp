#include "Allocator.hpp"


namespace Icicle {

Allocator::~Allocator()
{
	assert(_num_allocations == 0 && _used_memory == 0);
	_start = nullptr; _size = 0;
	//_size = 0;
}

size_t Allocator::getSize() const
{
	return _size;
}

size_t Allocator::getUsedMemory() const
{
	return _used_memory;
}

size_t Allocator::getNumAllocations() const
{
	return _num_allocations;
}

}
