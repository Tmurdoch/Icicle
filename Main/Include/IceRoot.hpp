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

    void loadGameObjects();

    

    std::vector<GameObject> gameObjects;

    IcicleWindow *window;
    LogicalDevice *logicalDevice;

    Renderer *renderer;
    RenderSystem *renderSystem;


    Root();

    public:
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
// PhysicsManager          zPhysicsManager;
// AnimationManager        zAnimationManager;
// TextureManager          zTextureManager;
// VideoManager            zVideoManager;

// FileSystemManager       zFileSystemManager;
    
    void startUp();
    void run();
};

}
