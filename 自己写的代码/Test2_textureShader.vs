#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 cossin;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
    
//    aPos.x = (aPos.x * cossin.x) - (aPos.y * cossin.y);
//    aPos.y = (aPos.x * cossin.y) + (aPos.y * cossin.x);
    
    if(cossin.x>-4)
    {
        gl_Position = vec4(((aPos.x * cossin.x) - (aPos.y * cossin.y)), ((aPos.x * cossin.y) + (aPos.y * cossin.x)),aPos.z,1.0);
    }
    ourColor = aColor;
    TexCoord = aTexCoord;
    
}



        
