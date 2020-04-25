//
//  MyTest.cpp
//  first
//
//  Created by Admin on 2020/4/24.
//  Copyright © 2020 Admin. All rights reserved.
//

/*最右边的矩阵是第一个与向量相乘的，所以应该从右向左读这个乘法。
    先缩放操作、再旋转、最后位移。
 
 *构建矩阵的时候是：位移、旋转、缩放
 glm::radians() 角度制转弧度制
 trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));
 trans = rotate(trans, radians(90.0f), vec3(0.0, 0.0, 1.0));
 trans = scale(trans, vec3(0.5, 0.5, 0.5));
 
 
 *缩放
    如果把缩放变量表示为(S1 S2 S3)我们可以为任意向量(x,y,z)定义一个缩放矩阵。
    S1  0  0  0     x     S1*x
    0  S2  0  0  .  y  =  S2*y
    0  0  S3  0     z     S3*z
    0  0   0  1     1      1
 
 *旋转
    弧度转角度：角度 = 弧度 * (180.0f / PI)
    角度转弧度：弧度 = 角度 * (PI / 180.0f)
    
 
 *位移
    如果把位移向量表示为(T.x,T.y,T.z)，我们就能把位移矩阵定义为：
    1  0  0  T.x     x     x+T.x
    0  1  0  T.y  .  y  =  y+T.y
    0  0  1  T.z     z     z+T.z
    0  0  0  1       1       1
 */




#include "Transformations.hpp"
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

int Transformations()
{

    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };


    unsigned int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
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
    
    Shader ourShader("/Users/admin/Desktop/code/OpenGL/自己写的代码/4.Transformations.vs","/Users/admin/Desktop/code/OpenGL/自己写的代码/4.Transformations.fs");
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    

    
    
    
//        -------------------------
    unsigned int VBO,VAO,EBO ;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
       glEnableVertexAttribArray(1);
       glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
       glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);//忽略了解绑
    glBindVertexArray(0);//忽略了解绑
    
//-----------------------------------
    unsigned int texture1,texture2;
    glGenTextures(1, &texture1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("/Users/admin/Desktop/code/OpenGL/自己写的代码/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
// ------------------------------------
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
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
//    ------------------------------------

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2",1);
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        
        mat4 trans;
        trans = translate(trans, vec3(0.5, -0.5, 0.0));
        trans = rotate(trans, float(glfwGetTime()), vec3(0.0f, 0.0f, 1.0f));
        
        
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));
        /*
         * 首先查询uniform变量地址，然后用有Matrix4fv后缀的glUniform函数把矩阵数据发送给着色器。
            参数一：uniform的位置值
            参数二：告诉OpenGL我们将要发送多少个矩阵，这里是1
            参数三：是否希望对矩阵进行置换Transpose
            参数四：真正的矩阵数据，但是需要用GLM的自带函数来变换这些数据
         */
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        
        trans = mat4(1.0f);
        trans = translate(trans, vec3(-0.5, 0.5, 0.0));
        trans = scale(trans, vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));
        transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1,&EBO);
    glfwTerminate();
    return 0;


    
    
    
    
    
    
    return 0;
}
