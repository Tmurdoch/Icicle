#include "keyboard_movement_controller.hpp"
#include "GameObject.hpp"

// std
#include <GLFW/glfw3.h>
#include <exception>
#include <limits>
#include <stdexcept>
#include <ctime>

namespace Icicle {

int KeyboardMovementController::moveInPlaneXZ(GLFWwindow *window, float dt,
                                              GameObject &gameObject) {
  glm::vec3 rotate{0};
  if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS)
    rotate.y += 1.f;
  if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS)
    rotate.y -= 1.f;
  if (glfwGetKey(window, keys.lookUp) == GLFW_PRESS)
    rotate.x += 1.f;
  if (glfwGetKey(window, keys.lookDown) == GLFW_PRESS)
    rotate.x -= 1.f;

  if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
    gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);
  }

  // limit pitch values between about +/- 85ish degrees
  gameObject.transform.rotation.x =
      glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
  gameObject.transform.rotation.y =
      glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

  float yaw = gameObject.transform.rotation.y;
  const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
  const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
  const glm::vec3 upDir{0.f, -1.f, 0.f};

  glm::vec3 moveDir{0.f};
  if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS)
    moveDir += forwardDir;
  if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS)
    moveDir -= forwardDir;
  if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS)
    moveDir += rightDir;
  if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS)
    moveDir -= rightDir;
  if (glfwGetKey(window, keys.moveUp) == GLFW_PRESS)
    moveDir += upDir;
  if (glfwGetKey(window, keys.moveDown) == GLFW_PRESS)
    moveDir -= upDir;
  if (glfwGetKey(window, keys.escape) == GLFW_PRESS)
    return -1;

  if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
    gameObject.transform.translation +=
        moveSpeed * dt * glm::normalize(moveDir);
  }
  return 0;
}

void KeyboardMovementController::mouse_button_callback(GLFWwindow *window,
                                                       int button, int action,
                                                       int mods) {
  // Get the current timestamp
  time_t currentTime = time(NULL);

  // Convert the timestamp to a human-readable string (local time)
  char *dateTimeString = ctime(&currentTime);

  // Print the formatted date and time
  printf("Current date and time: %s", dateTimeString);
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
    return;
  }
  KeyboardMovementController *controller =
      static_cast<KeyboardMovementController *>(
          glfwGetWindowUserPointer(window));

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    controller->mouseData = {xpos, ypos};
    printf("nice");
  }
}

int KeyboardMovementController::enableTopDownMovementController(
    GLFWwindow *window) {
  printf("enabled mouse");
  // In static callback:
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //see
  // https://www.glfw.org/docs/latest/input_guide.html#input_mouse
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  return 0;
}
} // namespace Icicle
