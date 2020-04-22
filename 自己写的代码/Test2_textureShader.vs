#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
//    int flog=-1,dis=2;
//
//    float x=glfwGetTime();
//
//    if(x>(dis+2))
//    {
//        dis=x;
//        flog=flog*-1;
//    }
//
    
//       旋转
//    vertices[0]=cos(x)/5*flog; vertices[1]=sin(x)/5; vertices[2]=0;
//    vertices[8]=sin(x)/5*flog; vertices[9]=-cos(x)/5; vertices[10]=0;
//    vertices[16]=-cos(x)/5*flog; vertices[17]=-sin(x)/5; vertices[18]=0;
//    vertices[24]=-sin(x)/5*flog; vertices[25]=cos(x)/5; vertices[26]=0;

    
    
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
    
}



        
