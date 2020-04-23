#include "glad.h"
#include "glfw3.h"
#include "stb_image.h"
#include "shader_s.h"
#include "Test_2.hpp"
#include "Some Function.hpp"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float step=1,angle=-360,radian,cosx,sinx,acc=1.2;
const float pi = 3.1415926535;
int tot=0,flog=-1;

float vertices1[] = {
    0.0f, 0.2f, 0.0f,   // up
    0.0f, -0.2f, 0.0f,  // down
    -0.2f, 0.0f, 0.0f, // left
    0.2f, 0.0f, 0.0f   // right
};

unsigned int indices1[] = { // 注意索引从0开始!
    0, 1, 2, // 第一个三角形
    0, 1, 3  // 第二个三角形
};

int Test_2()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("/Users/admin/Desktop/code/OpenGL/自己写的代码/Test2_textureShader.vs", "/Users/admin/Desktop/code/OpenGL/自己写的代码/Test2_textureShader.fs");
    Shader ourShader1("/Users/admin/Desktop/code/OpenGL/自己写的代码/3.Test2_Shader.vs","/Users/admin/Desktop/code/OpenGL/自己写的代码/3.Test2_Shader.fs");
    ourShader.use();
    ourShader1.use();
    unsigned int VAO1;
    //顶点数组
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    //绑定顶点数组缓存
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    //绑定索引缓存
    unsigned int EBO1;
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

      
       
    

    
    float vertices[] = {
        // positions          // colors           // texture coords  //cosx sinx
        0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,        0.0f, 0.0f,// top right
         0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,       0.0f, 0.0f, // bottom right
        -0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,       0.0f, 0.0f, // bottom left
        -0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,       0.0f, 0.0f, // top left

    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    

    // load and create a texture
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("/Users/admin/Desktop/code/OpenGL/自己写的代码/awesomeface_dark.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    
    
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        acc+=0.09;
        angle=angle+(step*acc);
        if(angle<-370)
        {
            step=1;
            acc=1.1;
        }
        if(angle>370)
        {
            step=-1;
            acc=1.1;
        }
//        cout<<"angle"<<angle<<"   "<<"acc"<<acc<<"   "<<step<<endl;
        
        radian = angle * (pi/180.0);
        
        
        cosx = cos(radian) ;
        sinx = sin(radian);
        
        vertices[8] = cosx; vertices[9] = sinx;
        vertices[18] = cosx; vertices[19] = sinx;
        vertices[28] = cosx; vertices[29] = sinx;
        vertices[38] = cosx; vertices[39] = sinx;
        
        
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
            // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
            // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
            //cos sin
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        ourShader1.use();
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &EBO1);

    glfwTerminate();
    return 0;
}
