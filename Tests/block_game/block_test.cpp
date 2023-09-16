#include "block_test.h"

void Icicle::BlockGameApp::run() {
    initWindow();
    RenderManager::getInstance()->create_VK_instance();
    mainLoop();
    cleanup();
}
        
void Icicle::BlockGameApp::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //specify to glfw not to use opengl
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "BlockGame", nullptr, nullptr);
}

void Icicle::BlockGameApp::initVulkan() {

}

void Icicle::BlockGameApp::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Icicle::BlockGameApp::cleanup() {
    RenderManager::getInstance()->destroyVK();

    glfwDestroyWindow(window);

    glfwTerminate();
}



/**
 * entry point for game-jam september game,
 * goal is for the engine to do most of the hard work and 
 * this project to tell the engine what assets to use, 
 * what actions to take and what the world looks like
**/
int main(int argc, char* argv[]) {
    Icicle::BlockGameApp app;

    std::cout << "starting app" << std::endl;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    

    return EXIT_SUCCESS;
}