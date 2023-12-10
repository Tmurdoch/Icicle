#include "IceRoot.hpp"

#include "keyboard_movement_controller.hpp"


namespace Icicle {


    Root* Root::instancePtr = nullptr;
    //RenderManager* Root::renderManager = nullptr;

    Root::Root() {}

    void Root::startUp() {

        //window
        window->startUp(WIDTH, HEIGHT, "Icicle");
        //device
        logicalDevice->startUp(window);
        //renderer
        renderer->startUp(window, logicalDevice );
        
        //renderSystem
        renderSystem->startUp(logicalDevice, renderer->getSwapChainRenderPass());


    }

    //TODO: rename this to run
    void Root::run() {


        
        Camera camera{};

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();
        while (!window->shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime =
                std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(window->getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = renderer->getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 10.f);

            if (auto commandBuffer = renderer->beginFrame()) {
                renderer->beginSwapChainRenderPass(commandBuffer);

                renderSystem->renderGameObjects(commandBuffer, gameObjects, camera);

                renderer->endSwapChainRenderPass(commandBuffer);
                renderer->endFrame();
            }
        }

        vkDeviceWaitIdle(logicalDevice->device());
    }

    void Root::loadGameObjects() {
        std::shared_ptr<Model> model =
            Model::createModelFromFile(logicalDevice, "../Resources/Models/character1.obj");
        auto gameObj = GameObject::createGameObject();
        gameObj.model = model;
        gameObj.transform.translation = { 0.0f, 0.0f, 2.5f };
        gameObj.transform.scale = glm::vec3(3.0f);
        gameObjects.push_back(std::move(gameObj));
    }

}


