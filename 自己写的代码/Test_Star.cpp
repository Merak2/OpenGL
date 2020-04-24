//
//  Test_Star.cpp
//  first
//
//  Created by Admin on 2020/4/21.
//  Copyright © 2020 Admin. All rights reserved.
///
#include "Test_Star.hpp"
#include "glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include "shader_s.h"
#include <bits/stdc++.h>
using namespace std;
//顶https://zhidao.baidu.com/question/489102691.html?oldq=1
//https://zhidao.baidu.com/question/1578193834272676580.html
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float toRadian(float x);

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
    
    /*
     **R=10时
     A(0,10)           0
     B(－9.5106,3.0902)3
     C(-5.8779,-8.0902)6
     D(5.8779,-8.0902) 9
     E(9.5106,3.0902) 12
     F(0,-3.8197)   15
     G(3.6328,-1.1804) 18
     H(2.2452,3.0902)21
     I(-2.2452,3.0902) 24
     J(-3.6328,-1.1804) 27

     */
    
    float vertices[30];
    memset(vertices,0,sizeof(vertices));
    float x;
    
    vertices[1] = 1.0;//A 假设A在Y轴上，且为1，五个顶点构成半径为1的圆
    x = toRadian(18);
    vertices[12] = cos(x); vertices[13] = sin(x); //E   ∠EOA=360°/5=72°,OE与X轴的夹角θ=90°－72°=18°
    vertices[3] = -cos(x); vertices[4] = sin(x);//B     B与E关于Y轴对称
    x = toRadian(36);                           //K是BIHE的中点,且OA⊥BE,∴OK=E.y，∠AOH=72°/2=36°，
    vertices[21] = vertices[13] * tan(x); vertices[22] = vertices[13];//H
    vertices[24] = -vertices[21]; vertices[25] = vertices[22]; //I 与H 关于Y轴对称
    vertices[16] = -sqrt((vertices[21] * vertices[21])+(vertices[22] * vertices[22]));//F   OH=sqrt(H.x^2+H.y^2),OF=OH
    x = toRadian(36);
    vertices[6] = -sin(x); vertices[7] = -cos(x); //C ∠COF=36°
    vertices[9] = -vertices[6]; vertices[10] = vertices[7];//D 与C关于Y轴对称
    x = toRadian(-18);
    vertices[18] = abs(vertices[16]) * cos(x); vertices[19] = abs(vertices[16]) * sin(x); //G  OG=OF=vertices[16],OG与X轴的夹角为－18°
    vertices[27] = -vertices[18]; vertices[28] = vertices[19];//J 与G关于Y轴对称
   
    unsigned int indices[] = { // 注意索引从0开始!
        0,9,6,
        4,8,5,
        3,7,9,
        2,6,8,
        1,5,7,
    };
    
    float size=1;
    std::cout<<"输入比例："<<std::endl;
    std::cin>>size;
    size/=5;
    for(int i=0;i<30;++i)
        vertices[i]=vertices[i]*size;


    
    
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
    

    

    
    float step=0.005;
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


float toRadian(float x)
{
    while(x>360)
    {
        x-=360;
    }
    
    while(x<-360)
    {
        x+=360;
    }
    return (x * 3.1415926535 / 180.0);
}
