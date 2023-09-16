#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MemoryManager.h"
#include "RenderManager.h"
#include <iostream>


#ifndef VULKAN_DEPS
#define VULKAN_DEPS

#define GLFW_INCLUDE_VULKAN
//windows version #include <glfw/glfw3.h> //maybe rename windows folder to GLFW so we don't have to comment this out
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#endif

#define TEST_RETURN 0;


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
// RenderManager           zRenderManager;
// PhysicsManager          zPhysicsManager;
// AnimationManager        zAnimationManager;
// TextureManager          zTextureManager;
// VideoManager            zVideoManager;

// FileSystemManager       zFileSystemManager;
    
    int testWindow();
    
    int startUp();
};

}
