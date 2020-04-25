//
//  Coordinate_Systems.cpp
//  first
//
//  Created by Admin on 2020/4/25.
//  Copyright © 2020 Admin. All rights reserved.
//

#include "Coordinate_Systems.hpp"
#include "glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include "shader_s.h"
#include "Some Function.hpp"
#include <bits/stdc++.h>
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int Coordinate_Systems()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800.0f, 600.0f, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);  //open Depth_Test    off--->glDisable.

    Shader ourShader("/Users/admin/Desktop/code/OpenGL/自己写的代码/5.Coordinate_Systems.vs", "/Users/admin/Desktop/code/OpenGL/自己写的代码/5.Coordinate_Systems.fs");

    float vertices[] = {
        //position        texture coord
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
    
    vec3 cubePositions[] = {
      vec3( 0.0f,  0.0f,  0.0f),
      vec3( 2.0f,  5.0f, -15.0f),
      vec3(-1.5f, -2.2f, -2.5f),
      vec3(-3.8f, -2.0f, -12.3f),
      vec3( 2.4f, -0.4f, -3.5f),
      vec3(-1.7f,  3.0f, -7.5f),
      vec3( 1.3f, -2.0f, -2.5f),
      vec3( 1.5f,  2.0f, -2.5f),
      vec3( 1.5f,  0.2f, -1.5f),
      vec3(-1.3f,  1.0f, -1.5f)
    };
    
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    
    
    unsigned int texture1, texture2;
    // texture 1
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/admin/Desktop/code/OpenGL/自己写的代码/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);
    
    
    //trexture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    data = stbi_load("/Users/admin/Desktop/code/OpenGL/自己写的代码/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }
    stbi_image_free(data);

    
    
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glClear(GL_COLOR_BUFFER_BIT);

        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        
        ourShader.use();

        
        mat4 model, view, projection;
        model = rotate(model, (float)glfwGetTime(), vec3(0.5f, 1.0f, 0.0f));
        view  = translate(view, vec3(0.0f, 0.0f, -3.0f));
        projection = perspective(radians(45.0f), 800.00f/600.00f, 0.1f, 100.0f);
        
        unsigned int matLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, value_ptr(model));
        
        matLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, value_ptr(view));
        
        matLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, value_ptr(projection));
    
        

        
        for(int i = 0; i < 10; ++i)
        {
            mat4 model;
            model = translate(model, cubePositions[i]);
            if(i % 3 == 0 || i == 0)
            {
                model = rotate(model, float(glfwGetTime()), vec3(1.0f, 0.0f, 0.0f));
            }else
            {
               model = rotate(model, radians(20.0f * i), vec3(1.0f, 0.3f, 0.5f));
            }
            
            matLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(matLoc, 1, GL_FALSE, value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
            
        }
        
        


        // render box
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
