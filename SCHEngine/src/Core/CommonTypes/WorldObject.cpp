#include "WorldObject.h"

#include "Shader.h"

WorldObject::WorldObject(float* objVertexData, GLsizei objVertexAmount):
    state(EObjectState::Inactive),
    vertexData(objVertexData),
    vertexAmount(objVertexAmount)
{
    // We generate 1 vertex buffer and array to this obj
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
}

void WorldObject::Init()
{
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);


    // We are expecting this:
    // 3 floats as x,y,z for position
    // 2 floats as u,v for UV coordinates

    //Location - From Vertex Shader
    //Size of Vertex attribute - vec3 = x,y,z - 3 values per vertex
    //type of data
    //data to be normalized
    //stride - space between vertex in memory(for example 5 for x,y,z,u,v)
    
    //We are still attached to VBO at this moment
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    
}

void WorldObject::Use() const
{
    glBindVertexArray(VAO);
}

void WorldObject::Draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, vertexAmount);
}

void WorldObject::Destroy() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
