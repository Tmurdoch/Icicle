#include "Zergcore.h"


// TODO: move to header file 
RenderManager           zRenderManager;
PhysicsManager          zPhysicsManager;
AnimationManager        zAnimationManager;
TextureManager          zTextureManager;
VideoManager            zVideoManager;
MemoryManager           zMemoryManager;
FileSystemManager       zFileSystemManager;


int main(int argc, const char* argv) {
    // Start up engine systems in correct order.
    //re-organize as necessary
    zMemoryManager.startUp();
    zFileSystemManager.startUp();
    zVideoManager.startUp();
    zTextureManager.startUp();
    zRenderManager.startUp();
    zAnimationManager.startUp();
    zPhysicsManager.startUp();

    // Run the game.
    zSimulationManager.run();

    // Shut everything down in reverse order.
    zPhysicsManager.shutDown();
    zAnimationManager.shutDown();
    zRenderManager.shutDown();
    zTextureManager.shutDown();
    zVideoManager.shutDown();
    zFileSystemManager.shutDown();
    zMemoryManager.shutDown();

    return 0;
}