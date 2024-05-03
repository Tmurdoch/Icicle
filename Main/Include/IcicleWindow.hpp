#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
namespace Icicle {

class IcicleWindow {

 public:

	 static IcicleWindow* getInstance() {
		 if (instancePtr == nullptr)
		 {
			 instancePtr = new IcicleWindow();
		 }
		 return instancePtr;
	 }

	 static bool isInstanceInitialized() {
		return (instancePtr != nullptr);
	 }

  void startUp(int w, int h, std::string name);
  void cleanUp();

  IcicleWindow(const IcicleWindow &) = delete;
  IcicleWindow &operator=(const IcicleWindow &) = delete;

  bool shouldClose() { return glfwWindowShouldClose(window); }
  VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
  bool wasWindowResized() { return framebufferResized; }
  void resetWindowResizedFlag() { framebufferResized = false; }
  GLFWwindow *getGLFWwindow() const { return window; }

  void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
	static IcicleWindow* instancePtr;
	IcicleWindow(); //do nothing
	~IcicleWindow();
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	void initWindow();

	int width;
	int height;
	bool framebufferResized = false;

	std::string windowName;
	GLFWwindow* window;
};
}  // namespace Icicle