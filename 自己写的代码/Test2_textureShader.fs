#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
//    FragColor = mix(texture(ourTexture, TexCoord),vec4(0.0f, 0.1058f, 0.545f, -1.0f),1);
//    FragColor = texture(ourTexture, TexCoord)*vec4(0.0f, 0.1058f, 0.445f, 1.0f);
    
    FragColor = texture(ourTexture, TexCoord);
    
}
