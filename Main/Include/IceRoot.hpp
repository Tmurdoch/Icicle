#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MemoryManager.hpp"
#include <iostream>



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
    static Root* getInstance()
    {
        if (instancePtr == NULL)
        {
            instancePtr = new Root();
        }
        return instancePtr;
    };

    Root(const Root& obj) = delete; //delete copy constructor

    void operator=(const Root &) = delete;

    //singletons
   // RenderManager           renderManager;
// PhysicsManager          zPhysicsManager;
// AnimationManager        zAnimationManager;
// TextureManager          zTextureManager;
// VideoManager            zVideoManager;

// FileSystemManager       zFileSystemManager;
    
    int testWindow();
    
    int startUp();
};

}
