#include "IceRoot.hpp"
#include "IcicleWindow.hpp"
#include "VulkanUtils.hpp"
#include "keyboard_movement_controller.hpp"

namespace Icicle {

Root *Root::instancePtr = nullptr;
// RenderManager* Root::renderManager = nullptr;

Root::Root() {}

void Root::startUp() {

  // window
  IcicleWindow::getInstance()->startUp(WIDTH, HEIGHT, "Icicle");
  // device
  LogicalDevice::getInstance()->startUp();
  // renderer
  Renderer::getInstance()->startUp();

  // renderSystem
  RenderSystem::getInstance()->startUp(
      Renderer::getInstance()->getSwapChainRenderPass());
}

void Root::run() {
  printf("running");
  loadGameObjects();
  Camera camera{};

  auto viewerObject = GameObject::createGameObject();
  KeyboardMovementController cameraController =
      KeyboardMovementController(IcicleWindow::getInstance()->getGLFWwindow());
  cameraController.enableTopDownMovementController(
      IcicleWindow::getInstance()->getGLFWwindow());

  auto currentTime = std::chrono::high_resolution_clock::now();
  // Window loop
  while (!IcicleWindow::getInstance()->shouldClose()) {
    glfwPollEvents();

    auto newTime = std::chrono::high_resolution_clock::now();
    float frameTime =
        std::chrono::duration<float, std::chrono::seconds::period>(newTime -
                                                                   currentTime)
            .count();
    currentTime = newTime;

    int ret = cameraController.moveInPlaneXZ(
        IcicleWindow::getInstance()->getGLFWwindow(), frameTime, viewerObject);

    if (ret == -1)
      IcicleWindow::getInstance()->cleanUp();

    camera.setViewYXZ(viewerObject.transform.translation,
                      viewerObject.transform.rotation);

    float aspect = Renderer::getInstance()->getAspectRatio();

    // set the clipping space
    camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 1000.f);

    if (auto commandBuffer = Renderer::getInstance()->beginFrame()) {
      Renderer::getInstance()->beginSwapChainRenderPass(commandBuffer);

      RenderSystem::getInstance()->renderGameObjects(commandBuffer, gameObjects,
                                                     camera);

      Renderer::getInstance()->endSwapChainRenderPass(commandBuffer);
      Renderer::getInstance()->endFrame();
    }
  }

  vkDeviceWaitIdle(logicalDevice->device());
  cleanUp();
}

void Root::loadGameObjects() {
#if WIN32
  std::shared_ptr<Model> model = Model::createModelFromFile(
      LogicalDevice::getInstance(), "..\\Resources\\Models\\diffuseTest.obj");
#else
  std::shared_ptr<Model> model = Model::createModelFromFile(
      LogicalDevice::getInstance(), "build/Resources/Models/diffuseTest.obj");
#endif
  auto gameObj = GameObject::createGameObject();
  gameObj.model = model;
  gameObj.transform.translation = {0.0f, 0.0f, 2.5f};
  gameObj.transform.scale = glm::vec3(3.0f);
  gameObjects.push_back(std::move(gameObj));
}

void Root::cleanUp() {
  renderSystem->cleanUp();
  renderer->cleanUp();
  logicalDevice->cleanUp();
  window->cleanUp();
}

} // namespace Icicle
