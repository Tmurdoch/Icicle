#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MemoryManager.h"


#if ASSERTIONS_ENABLED
// define some inline assembly that causes a break
// into the debugger -- this will be different on each
// target CPU
#define debugBreak() asm { int 3 }
// check the expression and fail if it is false
#define ASSERT(expr) \
if (expr) { } \
else \
{ \
reportAssertionFailure(#expr, \
__FILE__, __LINE__); \
debugBreak(); \
}
#else
#define ASSERT(expr) // evaluates to nothing
#endif


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
    

    static Root* getInstance();
    int startUp();
};
