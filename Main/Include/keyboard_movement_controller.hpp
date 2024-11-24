#pragma once

#include "GameObject.hpp"
#include "IcicleWindow.hpp"

namespace Icicle {
/*
 *TODO: add remappable keys
 *
 */
class KeyboardMovementController {
public:
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
  void topDownMovementController(GLFWwindow *window, float dt, GameObject selectedGameObjects[]);

  KeyMappings keys{};
  float moveSpeed{6.f};
  float lookSpeed{1.5f};
};
} // namespace Icicle
