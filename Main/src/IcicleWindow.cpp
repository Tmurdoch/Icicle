#include "IcicleWindow.hpp"

// std
#include <stdexcept>

namespace Icicle {

IcicleWindow::IcicleWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
  initWindow();
}

IcicleWindow::~IcicleWindow() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void IcicleWindow::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void IcicleWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
  if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
    throw std::runtime_error("failed to craete window surface");
  }
}

void IcicleWindow::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
  auto icicleWindow = reinterpret_cast<IcicleWindow *>(glfwGetWindowUserPointer(window));
  icicleWindow->framebufferResized = true;
  icicleWindow->width = width;
  icicleWindow->height = height;
}

}  // namespace Icicle