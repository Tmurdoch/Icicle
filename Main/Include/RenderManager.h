/**
* **************DESIGN***************
* if using BGfx rendering library
*
* Can set custom allocator in Init struct
*
* Communication needed between this class and time class, 
memory class (object will be rendered from memory), Game logic class?
*
* 
* 
* Things to think about before maybe: 
*   - what is each scene going to look like?
*       - how are we going to set up the scene (what will be loaded first)
*   - coordinate system?
*   - What's the first thing we're going to render? --> think of MVP (Minimum viable product)
*/


class RenderManager
{
    //TODO: Separate channel this classes debug info
    void updateCamera();
    void updateSceneElements();
    void renderScene();
    void swapBuffers();
    bool quit;
public:
    int render_loop();
}