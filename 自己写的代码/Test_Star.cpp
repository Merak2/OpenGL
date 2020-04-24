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
//顶https://zhidao.baidu.com/question/489102691.html?oldq=1
//https://zhidao.baidu.com/question/1578193834272676580.html
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
    
    /*
     **
     A(0,10)
     B(－9.5106,3.0902)
     C(-5.8779,-8.0902)
     D(5.8779,-8.0902)
     E(9.5106,3.0902)
     F(0,-3.8197)
     G(3.6328,-1.1804)
     H(2.2452,3.0902)
     I(-2.2452,3.0902)
     J(-3.6328,-1.1804)

     */
    
    float vertices[] = {
        0, 10, 0, //A 0 v_up
        -9.5106*0.75, 3.0902, 0, //B 1 v_left
        -5.8779*0.75, -8.0902, 0, //C 2 v_down_left
        5.8779*0.75, -8.0902, 0, //D 3 v_down_right
        9.5106*0.75, 3.0902, 0,//E 4 v_right
        
        0, -3.8197, 0, //F 5 C*D
        3.6328*0.75, -1.1804, 0, //G 6 D*E
        2.2452*0.75, 3.0902, 0,//H 7 A*E
        -2.2452*0.75, 3.0902, 0,//I 8 A*B
        -3.6328*0.75, -1.1804, 0,//J 9 B*C
    };
    for(int i=0; i<30; ++i)
    {
        vertices[i] = vertices[i] / 50.0;
    }

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
