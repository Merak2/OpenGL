/*
 *本小节可在原代码上进行扩充，仅需要更改
    1.顶点着色器和片段着色器的源码，增加uniform vec4 ourColor等相关字符串源代码。
    2.更改main()中while循环内的代码。
    3.增加支持sin函数等头文件库，此处我直接改了Xcode的头文件代码，增加stdc++.h头文件。
*本小节源代码：https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/3.1.shaders_uniform/shaders_uniform.cpp
*/
#include "glad.h"
#include "glfw3.h"
#include <bits/stdc++.h>
using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//用c字符串的方式存储源码，为了能够让OpenGL使用它，我们必须在运行时动态变异它的源码。
//layout (location = 0)是OpenGL的属性槽位置，坐标、颜色、纹理等
const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

/*
 *颜色被表示为4个元素的数组，红、绿、蓝、alpha透明度分量，通常缩写为RGBA。每个强度在0.0～1.0之间，
 *out关键字声明输出变量，in声明输入顶点属性
 */


const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    //processInput(window);
    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    //以上代码注释见上一次学习记录
    //----------------------------------------------------------------------------------

    
    /*
     *顶点数组对象：Vertex Array Object，VAO
     *顶点缓冲对象：Vertex Buffer Object，VBO
     *索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
     */
    
    /*
     *在OpenGL中，任何事物都在三维空间中，而屏幕和窗口是二维的像素数组，这导致OpenGL的大部分工作是把3D坐标转换为适应不同屏幕的2D像素（注意不是坐标，与坐标比，是坐标的近似值，原因是受到屏幕/窗口分辨率的影响）。这一过程由OpenGL的图形渲染管线（Graphics Pipeline，大多翻译为管线（实际上指的是处理过程是一堆原始图形数据途径一个传送管道，期间经过各种变化处理最终出现在屏幕的过程）。
     *图形渲染管线可以被划分为两个主要部分：
        1.将3D坐标转换为2D坐标。
        2.将2D坐标转变为实际的有颜色的像素。
     */
    
    /*
     *顶点数据->【顶点着色器 VertexShader->形状（图元）装配ShapeAssembly->几何着色器GeometryShader->光栅化Rasterization->片段着色器FragmentShader->测试与混合TestsAndBlending】
     
     *以上为图形渲染管线被划分的几个阶段，每个阶段会把前一个阶段的输出作为输入。
     *GPU有成千上万的小处理核心，它们在GPU上为每一个渲染管线阶段运行各自的小程序，因此可以并行执行。
     *使用OpenGL着色器语言(OpenGL Shading Language，GLSL)写成的程序可以配置顶点着色器、几何着色器、片段着色器。
     *各阶段的功能：
        *顶点着色器：把一个单独的顶点作为输入，3D坐标->另一种3D坐标，同时可以对顶点属性进行一些基本处理。
        *图元装配：将顶点着色器输出的所有顶点作为输入，将所有的点装配成制定图元（参数GL_POINTS、GL_TRIANGLES、GL_LINE_STRIP）的形状。
        *几何着色器：通过产生新顶点构造出新的（或是其他的）图元来生成其他形状。
        *光栅化阶段：把图元映射为最终屏幕上相应的像素，生成供片段着色器使用的片段（片段是OpenGL渲染一个像素所需的所有数据）。还会执行裁切，裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。
        *片段着色器：计算一个像素的最终颜色，也是OpenGL高级效果产生的地方。
        *Alpha测试和混合：检测片段对应的深度和模板值，用来判断这个像素是其他物体的前面还是后面，决定是否应该丢弃，也会检查slpha值（定义了一个物体的透明度，1是不透明），综合计算出像素最终的颜色。
     */
    
    
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建着色器，用ID来引用
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    //将源码附加到着色器对象上，然后编译它。参数一是要编译的着色器对象，参数二指定了传递的源码字符串数量，参数三是源码
    glCompileShader(vertexShader);
   
    
    
    
    /*
     *检测编译错误可以通过如下代码来实现。
     */
    int success;
    char infoLog[512];//存取错误信息
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检查是否编译成功
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    
    //片段着色器 原理同上
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
   
    
    
    /*
     *着色器程序对象（Shader Program Object）是多个着色器合并之后并最终链接完成的版本，如果要使用刚才编译的着色器，我们必须把它们连接Link为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序。已激活的着色器程序的着色器将在我们发送渲染调用的时候被使用。
     *当连接着色器至一个程序的时候，它会把每个着色器的输出连接到下个着色器的输入。当输出和输入不匹配的时候，会得到连接错误。
     */
    
    int shaderProgram = glCreateProgram();//创建一个程序，并返回新创建程序对象的ID引用
    /*
     *把着色器附加到程序上，然后用glLinkProgram链接
     */
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    
    
    //检错
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    
    
    //着色器对象链接到程序对象以后，要删除着色器对象。如果一个着色器连接到一个程序对象，调用glDeleteShader不会立刻删除着色器，而是将着色器标记为删除，在着色器不再连接任何程序对象时，内存将被释放。
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    
    float vertices[] = {//一组三角形坐标
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };


    unsigned int VBO, VAO;//顶点缓冲对象、顶点数组对象
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers() 第一个参数是要生成的缓冲对象的数量，第二个是要输入用来存储缓冲对象名称的变量/数组
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
     *void glBindBuffer() 第一个参数就是缓冲对象的类型，第二个参数是要绑定的缓冲对象的名称，也就是glGenBuffers()中产生的名称，使用该函数将缓冲对象绑定到OpenGL context中以便使用。如果第二个参数是0，则不再将第一个参数的target使用任何缓存对象。
     *绑定对象的过程就设置铁路的道岔开关，每一个缓冲类型的各个对象就像不同的轨道一样，将开关设置为其中一个状态，那么之后的列车都会驶入这条轨道。
     *允许绑定多个缓冲类型，但不能绑定多个相同类型的缓冲对象。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
     *glBufferData()专门用来把用户定义的数据复制到当前绑定缓冲的函数。参数一是目标缓冲类型，参数二指定传输数据大小，单位字节（用sizeof可方便计算）参数三是希望发送的实际数据，参数四是希望显卡如何管理给订的数据，共有三种格式。
     *GL_STATIC_DRAW ：数据不会或几乎不会改变。
     *GL_DYNAMIC_DRAW：数据会被改变很多。
     *GL_STREAM_DRAW ：数据每次绘制时都会改变。
     *用于区分将常变动的数据优先放入高速内存中。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
       /*
        *在渲染前告诉OpenGL如何解释顶点数据。
        *参数一：指定我们要配置的顶点属性，与layout(location=0)有关系
        *参数二：制定顶点属性的大小，vec3，由三个值组成。
        *参数三：指定数据的类型，这里是GL_FLOAT，都是由浮点数值组成的
        *参数四：是否希望数据被标准化，设置为GL_TRUE所有数据都会被影射到0～1，有符号型的是-1～1。
        *参数五：步长（Stride），告诉我们在连续的顶点属性组之间的间隔。由于下组位置数据在3个float之后，我们把步长设置为3*sizeof(float)。也可以设置为0让OpenGL决定具体步长是多少（只有在数值是紧密排列时才可以使用）。
        *参数六：类型是void*，因此要强制类型转换， 它表示位置数据在缓冲中起始位置的偏移量（Offset)。
        */
    
    glEnableVertexAttribArray(0);//以顶点属性位置作为参数，启用顶点属性；顶点属性默认是禁用的。
    glBindVertexArray(VAO);



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//将缓存颜色用此颜色进行清除
        glClear(GL_COLOR_BUFFER_BIT);//清除屏幕颜色，用缓存的颜色。
        //两者搭配使用可以更改窗口背景色

        glUseProgram(shaderProgram);//在查找、更改uniform时，需要先激活程序，以激活变量ourColor
        /*
         *更改uniform主要代码
         */
        float timeValue = glfwGetTime();//获取时间用以不断改变颜色
        float greenValue = sin(timeValue) / 2.0f + 0.5f;//设置不断变换的颜色变量
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//获取shaderProgram中的ourColor位置
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//设置uniform ourColor颜色值
        
        //绘制
        glDrawArrays(GL_TRIANGLES, 0, 3);

        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
    
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
