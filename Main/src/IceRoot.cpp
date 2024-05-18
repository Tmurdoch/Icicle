#include "IceRoot.hpp"
#include "VulkanUtils.hpp"
#include "keyboard_movement_controller.hpp"

#include "ImageLoad.cpp"


namespace Icicle {


    Root* Root::instancePtr = nullptr;
    //RenderManager* Root::renderManager = nullptr;

    Root::Root() {}

    void Root::startUp() {

        IcicleWindow::getInstance()->startUp(WIDTH, HEIGHT, "Icicle");
        
        LogicalDevice::getInstance()->startUp();
        
        Renderer::getInstance()->startUp();
        
        RenderSystem::getInstance()->startUp(Renderer::getInstance()->getSwapChainRenderPass());

    }
    
    void Root::run() {
        loadGameObjects();
        Camera camera{};

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();
        while (!IcicleWindow::getInstance()->shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime =
                std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(IcicleWindow::getInstance()->getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = Renderer::getInstance()->getAspectRatio();
            
            camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 15.f);

            if (auto commandBuffer = Renderer::getInstance()->beginFrame()) {
                Renderer::getInstance()->beginSwapChainRenderPass(commandBuffer);

                RenderSystem::getInstance()->renderGameObjects(commandBuffer, gameObjects, camera);

                Renderer::getInstance()->endSwapChainRenderPass(commandBuffer);
                Renderer::getInstance()->endFrame();
            }
        }

        vkDeviceWaitIdle(logicalDevice->device());
        cleanUp();
    }

    void Root::loadGameObjects() {
#if WIN32
        std::shared_ptr<Model> model =
            Model::createModelFromFile(LogicalDevice::getInstance(), "D:\\Projects\\VSIcicle\\Main\\Resources\\Models\\diffuseTest.obj");
#else
        std::shared_ptr<Model> model =
            Model::createModelFromFile(LogicalDevice::getInstance(), "../Resources/Models/diffuseTest.obj");
#endif
        auto gameObj = GameObject::createGameObject();
        gameObj.model = model;
        gameObj.transform.translation = { 0.0f, 0.0f, 2.5f };
        gameObj.transform.scale = glm::vec3(3.0f);
        gameObjects.push_back(std::move(gameObj));
    }


    bool Root::addImage(char* path, char* name) {
        int texWidth, texHeight, texChannels;

        unsigned char* pixels = load_texture(path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);


    }

    void Root::cleanUp() {
        renderSystem->cleanUp();
        renderer->cleanUp();
        logicalDevice->cleanUp();
        window->cleanUp();
    }

}


