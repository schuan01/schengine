/*
 * This is a base class for an object that can be placed in the World
 * Has a position and vertex data
 * Also shader data for rendering
 */
#pragma once
#include <glad/glad.h>

enum class EObjectState
{
 Active,
 Inactive,
 Hidden
};

class WorldObject
{
private:
 EObjectState state;
 float* vertexData;
 GLsizei vertexAmount;

 GLuint VBO; // vertex buffer obj
 GLuint VAO; // vertex array obj
 
public:
    WorldObject(float* objVertexData, GLsizei objVertexAmount);
 
    void Init();
    void Use() const;
    void Draw() const;
    void Destroy() const;
};
