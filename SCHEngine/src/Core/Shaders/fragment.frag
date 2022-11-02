#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 newPosition;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(newPosition, 1.0f);
    FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord), 0.2);
}