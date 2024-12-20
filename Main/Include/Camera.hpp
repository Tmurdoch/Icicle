#pragma once

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace Icicle {

class Camera {
public:
  void setOrthographicProjection(float left, float right, float top,
                                 float bottom, float near, float far);
  /**
   * Set the clipping space
   */
  void setPerspectiveProjection(float fovy, float aspect, float near,
                                float far);

  /*
  @position: position of camera
  @direction: direction camera is pointing
  @up: which direction is up, default is -Y*/
  void setViewDirection(glm::vec3 position, glm::vec3 direction,
                        glm::vec3 up = glm::vec3{0.f, -1.f, 0.f});

  void setViewTarget(glm::vec3 position, glm::vec3 target,
                     glm::vec3 up = glm::vec3{0.f, -1.f, 0.f});

  /*
  uses euler angles to specify orientation of camera
  Tait-Bryan angle ordering
  converting to canonical view*/
  void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

  const glm::mat4 &getProjection() const { return projectionMatrix; }
  const glm::mat4 &getView() const { return viewMatrix; }

private:
  glm::mat4 projectionMatrix{1.f};
  glm::mat4 viewMatrix{1.f};
};
} // namespace Icicle
