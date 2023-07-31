#include <iostream>


class MemoryManager 
/**
 * make sure limit dynamic memory allocation where possible
 * 
 * 
 * https://developer.ibm.com/tutorials/au-memorymanager/
 * based off this, hook up to allocator
*/
{
public:
    MemoryManager() ;
    ~MemoryManager() ;
    void startUp();

    void shutDown();
};

