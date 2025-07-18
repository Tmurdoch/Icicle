#pragma once

#include "GameObject.hpp"
#include "Subject.hpp"
#include <GLFW/glfw3.h>

namespace Icicle {
/*
 *TODO: add remappable keys
 *
 */

struct keyboardData {
  double posx = 0;
  double posy = 0;
};

class KeyboardMovementController : Subject<keyboardData> {
public:

  KeyboardMovementController(GLFWwindow *window) {
    glfwSetWindowUserPointer(window, this);
  }
  keyboardData mouseData = {0.0, 0.0};
  struct KeyMappings {
    int moveLeft = GLFW_KEY_A;
    int moveRight = GLFW_KEY_D;
    int moveForward = GLFW_KEY_W;
    int moveBackward = GLFW_KEY_S;
    int moveUp = GLFW_KEY_E;
    int moveDown = GLFW_KEY_Q;
    int lookLeft = GLFW_KEY_LEFT;
    int lookRight = GLFW_KEY_RIGHT;
    int lookUp = GLFW_KEY_UP;
    int lookDown = GLFW_KEY_DOWN;
    int escape = GLFW_KEY_ESCAPE;
  };

  int moveInPlaneXZ(GLFWwindow *window, float dt, GameObject &gameObject);

  /*
   *dt: delta?
   * selectedGameObjects: game objects to move
   */
  int enableTopDownMovementController(GLFWwindow *window);

  KeyMappings keys{};
  float moveSpeed{6.f};
  float lookSpeed{1.5f};

private:
  static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                    int mods);
};
} // namespace Icicle
