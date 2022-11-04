#include "CommonTypes/Shader.h"
#include "CommonTypes/Texture.h"
#include "CommonTypes/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "CommonTypes/WorldObject.h"

// global scope
namespace
{
    Window* mainWindow = nullptr;
    // settings
    constexpr unsigned int DEFAULT_SCR_WIDTH = 800;
    constexpr unsigned int DEFAULT_SCR_HEIGHT = 600;
}

void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
   init();
    
    // glfw window creation
    // --------------------
    mainWindow = new Window(DEFAULT_SCR_WIDTH, DEFAULT_SCR_HEIGHT);
    if(mainWindow)
    {
        mainWindow->Init();
    }
    else
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetFramebufferSizeCallback(mainWindow->GetGLFWWindow(), framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Enable Depth buffer for proper rendering
    glEnable(GL_DEPTH_TEST);

    Shader mainShader("./src/Core/Shaders/vertex.vert", "./src/Core/Shaders/fragment.frag");
    
    Texture texture1("container.jpg", GL_RGB);
    texture1.LoadTexture();

    Texture texture2("awesomeface.png", GL_RGBA);
    texture2.LoadTexture();

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3( -1.2f, -2.2f, -2.5f),
        glm::vec3( -3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3( -1.70f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3( -1.3f, 1.0f, -1.5f),
    };

    /*float vertices[] = {//PIRAMYD 
        //side 1
        0.5f, -0.5f, 0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.5f, 1.0f,
        //side 2
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.5f, 1.0f,
        //side 3
         0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.5f, 1.0f,
        //side 4
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.5f, 1.0f,

        //side 5 - bottom
         0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, //triangle 1
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

        
         0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //triangle 2
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        
    };*/

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {//3D cube
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    /*float vertices[] = { //rectangle
         // positions        //colors           //texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// top left 
    };*/

    /*float vertices[] = {
        //vertices            //colors
        -0.5f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bot left
         0.5f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bot right
         0.0f,   0.5f, 0.0f,  0.0f, 0.0f, 1.0f // top
    };*/

    /*float vertices[] = { //double triangles
        -1.0,  -0.5f,  0.0f, //1st bot left
         0.0f, -0.5f,  0.0f, //1st bot right
        -0.5f,  0.5f,  0.0f, //1st top
         0.0f, -0.5f, 0.0f, //2nd bot left
         1.0f, -0.5f, 0.0f, //2nd bot right
         0.5f,  0.5f, 0.0f //2nd top
    };*/

    /*float vertices1[] = { //1 triange left
        -1.0,  -0.5f,  0.0f, //1st bot left
         0.0f, -0.5f,  0.0f, //1st bot right
        -0.5f,  0.5f,  0.0f //1st top
    };

    float vertices2[] = { //1 triangle right
         0.0f, -0.5f, 0.0f, //2nd bot left
         1.0f, -0.5f, 0.0f, //2nd bot right
         0.5f,  0.5f, 0.0f //2nd top
    };*/
    
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    WorldObject* cube = new WorldObject(vertices, 36);
    cube->Init();

    
    unsigned int VBOs[2], VAOs[2];//, EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    //glGenBuffers(1, &EBO);
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOs[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attributes
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // color attributes
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // text coord attributes
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);


    /*glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VAOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);*/
    
    //Location = 0 - From Vertex Shader
    //Size of Vertex attribute - vec3 = x,y,z - 3 values per vertex
    //type of data
    //data to be normalized
    //stride - space between vertex
    //We are still attached to VBO at this moment
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    mainShader.use();
    mainShader.setInt("texture1", 0);
    mainShader.setInt("texture2", 1);

    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(mainWindow->GetGLFWWindow()))
    {
        // input
        // -----
        processInput(mainWindow->GetGLFWWindow());

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1.GetId());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2.GetId());

        // draw our first triangle
        mainShader.use();

        // Camera
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

        

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, ((float)glfwGetTime() * glm::radians(50.0f)), glm::vec3(0.0f, 1.0f, 0.0f));

        const float radius = 10.f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0, 1.0f, 0.0f));

        //glm::mat4 view = glm::mat4(1.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(mainWindow->GetWidth()) / static_cast<float>(mainWindow->GetHeight()), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(mainShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(mainShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(mainShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        
        //unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

        //ourShader.setFloat("horizontalOffset",0.2f);

        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f + 0.5f);
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        //cube->Use();
        glBindVertexArray(VAOs[0]);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            mainShader.setMat4("model", model);

            //cube->Draw();
            glDrawArrays(GL_TRIANGLES, 0, 36); //cube or pyramid
        }
        //glDrawArrays(GL_TRIANGLES, 0, 3); //1 triangle
        
        //glBindVertexArray(VAOs[1]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3); //1 triangle
        //glDrawArrays(GL_TRIANGLES, 0, 6); //2 triangles
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // rectangle(2 triangles)
        //glDrawArrays(GL_TRIANGLES, 0, 36); //cube or pyramid
        
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(mainWindow->GetGLFWWindow());
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //cube->Destroy();
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    //glDeleteBuffers(1, &EBO);
    mainShader.remove();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        mainWindow->Close();

    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    mainWindow->SetWindowSize(width, height);
}

/*
 * This is the init function that we are going to use for init any global variable
 * also the idea is to init OPEN GL, set the main window, etc
 */
void init()
{
    // glfw: initialize and configure
    // ------------------------------
    //glfw init
    glfwInit();

    // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Just in case for Apple OS
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    
}