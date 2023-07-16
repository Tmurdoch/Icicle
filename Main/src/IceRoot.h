#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MemoryManager.h"

class Root
{
    private:

    // member variables

    static Root* instancePtr;

    Root() {}

    public:

    Root(const Root& obj) = delete; //delete copy constructor

    void operator=(const Root &) = delete;

    //singletons
// RenderManager           zRenderManager;
// PhysicsManager          zPhysicsManager;
// AnimationManager        zAnimationManager;
// TextureManager          zTextureManager;
// VideoManager            zVideoManager;

// FileSystemManager       zFileSystemManager;
    MemoryManager           zMemoryManager;

    static Root* getInstance();
    int startUp();
};
