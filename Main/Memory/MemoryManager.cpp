#include "MemoryManager.h"



namespace Icicle {

class MemoryManager {
    private:
    static MemoryManager* instancePtr;

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

    static MemoryManager* getInstance() {
        if (instancePtr == NULL)
        {
            instancePtr = new MemoryManager();
            return instancePtr;
        }
    }

    void startUp()
    {
        std::cout<<" Starting Memory Manager. "<< std::endl;
        // start up manager...
        
    }

    void* allocate(size_t size) {
        printf("allocation called succesfully");
        return 0;
    }
    void free(void* address) {
        printf("free called succesfully");
    }


    void* operator new[ ] (size_t size)
    {
        https://discourse.cmake.org/t/cmake-project-not-linking-correctly/8806/5
        return getInstance.allocate(size);
    }

    void MemoryManager::operator delete (void* pointerToDelete)
    {
        IceMemoryManager.free(pointerToDelete);
    }

    void MemoryManager::operator delete[ ] (void* arrayToDelete)
    {
        IceMemoryManager.free(arrayToDelete);
    }

}
};
