#include "MemoryManager.h"



namespace Icicle {

    MemoryManager::MemoryManager() 
    {
        // do nothing, see http://ce.eng.usc.ac.ir/files/1511334027376.pdf pg.261
        // use startUp() instead to make sure order is preserved
    }
    MemoryManager::~MemoryManager() 
    {
        // do nothing
    }

    void MemoryManager::startUp()
    {
        std::cout<<" Starting Memory Manager. "<< std::endl;
        // start up manager...
        
    }

    void* allocate(size_t size) {
        printf("allocation called succesfully");
    }
    void free(void* address) {
        printf("free called succesfully");
    }

    

    void* MemoryManager::operator new[] (size_t size) 
    {
        return IceMemoryManager.allocate(size);
    }

    void* MemoryManager::operator new[ ] (size_t size)
    {
        return IceMemoryManager.allocate(size);
    }

    void MemoryManager::operator delete (void* pointerToDelete)
    {
        IceMemoryManager.free(pointerToDelete);
    }

    void MemoryManager::operator delete[ ] (void* arrayToDelete)
    {
        IceMemoryManager.free(arrayToDelete);
    }

  
};
