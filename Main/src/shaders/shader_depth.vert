#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform Push {
  mat4 transform; //projection * view * model
  mat4 modelMatrix;
} push;

const vec3 DIRECTION_TO_LIGHT = normalize(vec3(1.0, -3.0, -1.0)); //directional lighting
const float AMBIENT = 0.02;

void main() {
  gl_Position = push.transform * vec4(position, 1.0);

  //temporary, this is only correct in certain situations
  //when scale is uniform (sx == sy == sz)
  //vec3 normalWorldSpace = normalize(mat3(push.modelMatrix) * normal);

  //computationally expensive, see constructing normal matrix if wish to have non-uniform scale computations
  //https://www.youtube.com/watch?v=wfh2N4u-nOU
  mat3 normalMatrix = transpose(inverse(mat3(push.modelMatrix)));
  vec3 normalWorldSpace = normalize(normalMatrix * normal);

  float lightIntensity = AMBIENT + max(dot(normalWorldSpace, DIRECTION_TO_LIGHT), 0); // when noraml is facing away from light surface this is 0


  fragColor = lightIntensity * color;
}