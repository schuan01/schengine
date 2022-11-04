/*
 * This one for a basic 2D texture
 * Just for simplicity we are going to look the texture to ./data/texture folder
 */
#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
private:
 GLuint id;
 std::string name;
 GLenum format;
 
public:
 Texture(const std::string& textureName, GLenum textureFormat);

 // Load the texture in memory using stbi_load
 void LoadTexture();

 GLuint GetId() const { return id; }

private:
 void LoadInternal();
    
};
