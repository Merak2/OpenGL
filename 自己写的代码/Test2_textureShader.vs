#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 _time;

out vec3 ourColor;
out vec2 TexCoord;

uniform float time;

void main()
{
    
    
//    aPos.x = ((aPos.x /0.075 * cos(radian)) - (aPos.y * sin(radian)))*0.075;
//    aPos.y = (aPos.x /0.075 * sin(radian)) + (aPos.y * cos(radian));
    
    float deltaAngle = sin(_time.x) * 360;
    float radian = deltaAngle * 3.1415926535 / 180.0;
    
    gl_Position = vec4((((aPos.x /0.75 * cos(radian)) - (aPos.y * sin(radian))) * 0.75), ((aPos.x /0.75 * sin(radian)) + (aPos.y * cos(radian))) , aPos.z, 1.0);
    // 0.75之类的操作是为了保证在800*600的窗口上显示的是正方形
    ourColor = aColor;
    TexCoord = aTexCoord;
    
}



        
