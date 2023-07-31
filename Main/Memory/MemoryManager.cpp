#include "MemoryManager.h"
#include "StackAllocator.h"
#include "../src/IceRoot.h"



class MemoryManager 
{
public:
    MemoryManager() 
    {
        // do nothing, see http://ce.eng.usc.ac.ir/files/1511334027376.pdf pg.261
        // use startUp() instead to make sure order is preserved
    }
    ~MemoryManager() 
    {
        // do nothing
    }

    void startUp()
    {
        std::cout<<" Starting Memory Manager. "<< std::endl;
        // start up manager...
        StackAllocator stalloc;
    }

    

    void* operator new (size_t size) 
    {
        return IceMemoryManager.allocate(size);
    }

    void* operator new[ ] (size_t size)
    {
        return  gMemoryManager.allocate(size);
    }

    void operator delete (void∗ pointerToDelete)
    {
        gMemoryManager.free(pointerToDelete);
    }

    void operator delete[ ] (void∗ arrayToDelete)
    {
        gMemoryManager.free(arrayToDelete);
    }

  
};