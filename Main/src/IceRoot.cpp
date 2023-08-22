#include <stddef.h>
#include "IceRoot.h"

namespace Icicle {

class Root
{
    private:

    // member variables

    static Root* instancePtr;

    Root() {}

    public:

    void operator=(const Root &) = delete;

    static Root* getInstance()
    {
        if (instancePtr == NULL)
        {
            instancePtr = new Root();
            return instancePtr;
        }
    }

    int startUp()
    {
        
        std::cout<<"Starting up systems"<<std::endl;
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
};
}