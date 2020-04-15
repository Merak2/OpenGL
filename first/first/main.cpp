#include "glad.h"
#include "glfw3.h"
#include <iostream>
using namespace std;

/*
 *openGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。并不是一个平台

 GLFW是一个专门针对OpenGL的C语言库,它提供了一些渲染物体所需的最低限度的接口。它允许用户
 创建OpenGL上下文，定义窗口参数以及处理用户输入。

 GLAD：由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。所以任务就落在了
开发者身上，开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。取得地址的方法因平台而异,代码非常复杂，而且很繁琐，我们需要对每个可能使用的函数都要重复这个过程。幸运的是，有些库能简化此过程，其
 中GLAD是目前最新，也是最流行的库。GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要
 初始化GLAD。
 */

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    
    glfwInit();                                     //必要的初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //规定glfw的版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 兼容性设置
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "First window", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();                                //事后处理
        return -1;
    }
    glfwMakeContextCurrent(window);                     //配置上下文context，具体context在不同场景下不一样
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /*
     *framebuffer_size_callback是回调函数。
     *回调函数作为参数传入，本身又会被调用。
     *glfwSetFramebufferSizeCallback设置好属性，当窗口大小被改变时，会自动调用匹配窗口大小。
     *执行顺序为：glfwSetFramebufferSizeCallback首先被调用，framebuffer_size_callback回调函数被调用，回调函数内部被调用。
     */

    //初始化glad的所有指针，在使用前必须这样做。
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//检测ESC按键
        glfwSetWindowShouldClose(window, true);//更改属性，退出循环

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//重置缓冲区颜色
        glClear(GL_COLOR_BUFFER_BIT);       //清除缓冲区颜色

        glfwSwapBuffers(window);
        /*
         *双缓冲区：图像展示的过程是边绘制边展示，这样会出现闪屏，（可以将glclear相关函数代码删除试试）
         而我们不需要看到绘制过程，所以采用双缓冲区，一个绘制，一个展现，然后交替展示，于是有了swapBuffers
         */
        glfwPollEvents();
        /*
         *检测有没有事件发生
         */
    }
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
