#include "IceRoot.hpp"
#include "RenderManager.hpp"

namespace Icicle {

    Root* Root::instancePtr = nullptr;

    Root::Root() {}

    int Root::startUp()
    {
        
        std::cout<<"Starting up systems"<<std::endl;
        MemoryManager::startUp();

        RenderManager& renderManager = RenderManager::getInstance();
        renderManager.startUp();
        
        


        return 0;
    }

}


