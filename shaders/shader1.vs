#version 330 core

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor; // output a color to the fragment shader

uniform float time;

void main()
{
   gl_Position = vec4(vec3(aPos.x + sin(time * 0.5), aPos.y, aPos.z), 1.0);
   ourColor = aColor; // set ourColor to the input color we got from the vertex data
}
