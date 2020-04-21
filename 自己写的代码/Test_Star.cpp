//
//  Test_Star.cpp
//  first
//
//  Created by Admin on 2020/4/21.
//  Copyright © 2020 Admin. All rights reserved.
//
#include "Test_Star.hpp"
#include "glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int Test_Star()
{
    const char *vertexShaderSource={
       "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}"
    };

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.9f, 0.0f, 0.0f, 1.0f);\n"
        "}\n\0";
    
    float vertices[] = {
        0.0,0.06,0.0f, //F 0
        0.04f,0.02f,0.0f,//G 1
        0.03f,-0.04f,0.0f,//H 2
        -0.03f,-0.04f,0.0f,//I 3
        -0.04f,0.02f,0.0f,//J 4
        -0.01f,0.02f,0.0f,//K 5
        0.01f,0.02f,0.0f,//L 6
        0.02f,0.0f,0.0f,//M 7
        0.0f,-0.0155f,0.0f,//N 8
        -0.02f,0.0f,0.0f,//O 9
    };

    unsigned int indices[] = { // 注意索引从0开始!
        0,9,7,
        1,5,8,
        2,6,9,
        3,5,7,
        4,6,8,
        
    };



    
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    unsigned int VBO,VAO,EBO ;
    

    

    
    float step=0.01;
    bool flog=true;
    while(!glfwWindowShouldClose(window))
    {
        if(flog)
        {
            for(int i=0;i<30;i=i+3)
            {
                vertices[i]+=step;
                if(vertices[i]>1)
                    flog=false;
            }
        }
        
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1,&EBO);
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);//忽略了解绑
        glBindVertexArray(0);//忽略了解绑
        
    
    // ------------------------------------
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        
        int  success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }else
        {
            std::cout<<"yes"<<std::endl;
        }
        
     // ------------------------------------
        
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        
    //--------------------------------------
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
            
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        
        
        //    glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        
        
        
        
        
        
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
    glfwTerminate();
    return 0;
}
