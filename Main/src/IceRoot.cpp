#include "IceRoot.h"

namespace Icicle {

    Root::Root() {}

    int startUp()
    {
        
        std::cout<<"Starting up systems"<<std::endl;
        MemoryManager::startUp();
        return 0;
    // Start up engine systems in correct order.
    //re-organize as necessary
    // zMemoryManager.startUp();
    // zFileSystemManager.startUp();
    // zVideoManager.startUp();
    // zTextureManager.startUp();
    // zRenderManager.startUp();
    // zAnimationManager.startUp();
    // zPhysicsManager.startUp();

    // // Run the game.
    // zSimulationManager.run();

    // // Shut everything down in reverse order.
    // zPhysicsManager.shutDown();
    // zAnimationManager.shutDown();
    // zRenderManager.shutDown();
    // zTextureManager.shutDown();
    // zVideoManager.shutDown();
    // zFileSystemManager.shutDown();
    // zMemoryManager.shutDown();
    }

}