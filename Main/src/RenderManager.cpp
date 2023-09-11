#include "RenderManager.h"





    RenderManager::RenderManager() 
    {
        // do nothing, see http://ce.eng.usc.ac.ir/files/1511334027376.pdf pg.261
        // use startUp() instead to make sure order is preserved
    }
    RenderManager::~RenderManager()
    {
        // do nothing
    }

    void RenderManager::startUp()
    {
        // start up manager...
    }

    

    int RenderManager::render_loop() {
    https://github.com/bkaradzic/bgfx/blob/master/examples/00-helloworld/helloworld.cpp
    while (!quit)
        {
        // Update the camera transform based on interactive
        // inputs or by following a predefined path.
        updateCamera();
        // Update positions, orientations and any other
        // relevant visual state of any dynamic elements
        // in the scene.
        updateSceneElements();
        // Render a still frame into an off-screen frame
        // buffer known as the "back buffer".
        renderScene();
        // Swap the back buffer with the front buffer, making
        // the most recently rendered image visible
        // on-screen. (Or, in windowed mode, copy (blit) the
        // back buffer's contents to the front buffer.
        swapBuffers();
        }
    }
    
    void RenderManager::shutDown()
    {
        //shut down manager...
    }
};