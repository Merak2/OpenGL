#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
//    FragColor = mix(texture(ourTexture, TexCoord),vec4(0.0f, 0.1058f, 0.545f, -1.0f),1);
//    FragColor = texture(ourTexture, TexCoord)*vec4(0.0f, 0.1058f, 0.445f, 1.0f);
    lowp vec4 col = texture(ourTexture, TexCoord);
    FragColor = vec4(col.r*0.299+col.g*0.587+col.b*0.114,col.r*0.299+col.g*0.587+col.b*0.114,col.r*0.299+col.g*0.587+col.b*0.114,1.0f);
    //rgb转灰度 https://blog.csdn.net/xiaxl/article/details/72622236
    //
//    FrageColor = vec4(1.0f,1.0f,1.0f,1.0f);
    
}
