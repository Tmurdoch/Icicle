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

Note: can setup message callbacks to handle certain errors, VK_EXT_debug_utils extension
*/

namespace Icicle {
    //TODO: Separate channel this classes debug info
class RenderManager
{
    private:
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger; //handle for debug callbacks
    
    public:
        void setupDebugMessenger();
        void initVulkan();
        void create_VK_instance();
        void destroyVK();
        static RenderManager* RenderManagerInstancePtr;

        static RenderManager* getInstance() {
            if (RenderManagerInstancePtr == NULL) {
                RenderManagerInstancePtr = new RenderManager();
            }
            return RenderManagerInstancePtr;
        }
};
}