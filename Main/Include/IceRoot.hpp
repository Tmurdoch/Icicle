#pragma once

#include "MemoryManager.hpp"
#include "Renderer.hpp"
#include "RenderManager.hpp"
#include "RenderSystem.hpp"
#include "GameObject.hpp"
#include "LogicalDevice.hpp"
#include "IcicleWindow.hpp"



namespace Icicle {


/**
 * Singleton class, everything in game engine is started here
 * 
 *  * generally good idea to take advantage of all CPU cores, leaving 
 * as little work as possible for main thread
*/
class Root
{
    private:

    // member variables

        static Root* instancePtr;

    Root();

    public:
    std::vector<GameObject> gameObjects;
    void loadGameObjects();
    static Root* getInstance()
    {
        if (instancePtr == NULL)
        {
            instancePtr = new Root();
        }
        return instancePtr;
    }

    Root(const Root& obj) = delete; //delete copy constructor

    void operator=(const Root &) = delete;
    

    //singletons
    static RenderManager*           renderManager;
    IcicleWindow *window;
    LogicalDevice *logicalDevice;

    Renderer *renderer;
    RenderSystem *renderSystem;
// PhysicsManager          zPhysicsManager;
// AnimationManager        zAnimationManager;
// TextureManager          zTextureManager;
// VideoManager            zVideoManager;

// FileSystemManager       zFileSystemManager;
    
    void startUp();
    void cleanUp();
    void run();
};

}
