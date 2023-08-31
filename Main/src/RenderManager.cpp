class RenderManager
{
    void updateCamera();
    void updateSceneElements();
    void renderScene();
    void swapBuffers();
    bool quit;
public:
    RenderManager() 
    {
        // do nothing, see http://ce.eng.usc.ac.ir/files/1511334027376.pdf pg.261
        // use startUp() instead to make sure order is preserved
    }
    ~RenderManager() 
    {
        // do nothing
    }

    void startUp()
    {
        // start up manager...
    }

    

    int Renderloop() {
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

void shutDown()
    {
        //shut down manager...
    }
};