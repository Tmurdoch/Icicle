#include "../Include/MemoryManager.h"



namespace Icicle {
    MemoryManager* MemoryManager::MemInstancePtr = nullptr;

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
        uint8_t memory_block[10]; 
        StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);
        MemInstancePtr = new MemoryManager();
        // new MemoryManager(sizeof(memory_block));

        //TODO: setup listeners
    }


    //TODO: shutdown function, make sure destroy memory before destructor called 

    void* MemoryManager::allocate(size_t size) {
        printf("allocation called succesfully");
        return 0;
    }
    void MemoryManager::free(void* address) {
        printf("free called succesfully");
    }

}


