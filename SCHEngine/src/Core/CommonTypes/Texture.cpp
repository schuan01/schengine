#include "Texture.h"

#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"

namespace 
{
    const std::string TexturesPath = "./data/textures/";
}
Texture::Texture(const std::string& textureName, GLenum textureFormat)
{
    id = 0; //just for the compiler, it's is init below
    
    // Generate the texture and bind, only one
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // texture filtering/wrapping options (currently bound object)
    // TODO make this variables or custom parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    name = textureName;
    format = textureFormat; // format give for the image. ie jpg = GL_RGB, png = GL_RGBA
}

void Texture::LoadTexture()
{
    LoadInternal();
}

void Texture::LoadInternal()
{
    // load and generate the texture
    int width, height, nrChannels;
    const std::string location = TexturesPath + name;
    unsigned char* data = stbi_load(location.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture:" << name << std::endl;
    }

    // Free the data after it is binded by GL
    stbi_image_free(data);
}
