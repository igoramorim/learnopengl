#version 330 core

layout (location = 0) in vec3 aPos;       // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;     // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;  // texture coord

out vec3 ourColor; // output a color to the fragment shader
out vec3 ourPos;
out vec2 TexCoord;

uniform float time;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   ourPos = aPos;
   // ourPos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
   ourColor = aColor; // set ourColor to the input color we got from the vertex data
   TexCoord = aTexCoord;
}
