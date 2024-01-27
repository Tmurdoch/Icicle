
#include "IceRoot.hpp"
#include "StackAllocator.hpp"
#include "Allocator.hpp"
#include "IcicleMath.hpp"
#include "keyboard_movement_controller.hpp"

namespace Icicle {

	


	void run() {
       
        Root::getInstance()->loadGameObjects();
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

                RenderSystem::getInstance()->renderGameObjects(commandBuffer, Root::getInstance()->gameObjects, camera);

                Renderer::getInstance()->endSwapChainRenderPass(commandBuffer);
                Renderer::getInstance()->endFrame();
            }
        }

        vkDeviceWaitIdle(Root::getInstance()->logicalDevice->device());
        Root::getInstance()->cleanUp();
	}


    int main() {

        Icicle::Root::getInstance()->startUp();

        run();

        std::cout << "test\n";
        return 0;
    }
}//namespace Icicle