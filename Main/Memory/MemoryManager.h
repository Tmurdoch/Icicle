#include <iostream>


class MemoryManager 
/**
 * make sure limit dynamic memory allocation where possible
 * TODO: some kind of chunk allocator, stack or something see gregory textbook chapter 5
*/
{
public:
    MemoryManager() ;
    ~MemoryManager() ;
    void startUp();

    void shutDown();
};

