#include "IceRoot.hpp"

namespace Icicle {

    Root* Root::instancePtr = nullptr;

    Root::Root() {}

    int Root::testWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);

        uint32_t extension_count = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

        std::cout << extension_count << " extensions supported\n";

        glm::mat4 matrix; 
        glm::vec4 vec;

        auto test = matrix * vec;

        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
        
        glfwDestroyWindow(window);

        glfwTerminate();
        return 0;
    }

    int Root::startUp()
    {
        
        std::cout<<"Starting up systems"<<std::endl;
        MemoryManager::startUp();



        return 0;
    }

}