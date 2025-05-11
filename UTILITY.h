// Arquivo : UTILITY.h
// Define os shaders e utilit�rios para compila��o e linkagem
#pragma once

#include <string>
#include <GLFW/glfw3.h>

// Vertex Shader Source Code
const std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos; // Posi��o do v�rtice
layout (location = 1) in vec3 aColor; // Cor do v�rtice

out vec3 vertexColor; // Passa a cor para o Fragment Shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // Define a posi��o do v�rtice
    vertexColor = aColor; // Passa a cor para o pr�ximo est�gio
}
)";

// Fragment Shader Source Code
const std::string fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor; // Recebe a cor do Vertex Shader

out vec4 FragColor; // Cor final do fragmento

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Define a cor do fragmento
}
)";

// Fun��es utilit�rias para shaders
unsigned int compileShader(const std::string& source, GLenum shaderType);
unsigned int createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
