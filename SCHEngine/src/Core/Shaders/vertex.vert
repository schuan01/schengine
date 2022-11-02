#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // color variable has atttribue position 1
layout (location = 2) in vec2 aTexCoord; // texture coordinate has atttribue position 2

out vec3 ourColor; //specify a color output to the fragment shader
out vec3 newPosition;
out vec2 TexCoord;

uniform float horizontalOffset; //offset
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  //gl_Position = transform * vec4(aPos.x + horizontalOffset, aPos.y, aPos.z, 1.0);
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  newPosition = aPos;
  ourColor = aColor;
  TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}