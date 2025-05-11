// Arquivo : UTILITY.h
// Define os shaders e utilitários para compilação e linkagem
#pragma once

#include <string>
#include <GLFW/glfw3.h>

// Vertex Shader Source Code
const std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos; // Posição do vértice
layout (location = 1) in vec3 aColor; // Cor do vértice

out vec3 vertexColor; // Passa a cor para o Fragment Shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // Define a posição do vértice
    vertexColor = aColor; // Passa a cor para o próximo estágio
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

// Funções utilitárias para shaders
unsigned int compileShader(const std::string& source, GLenum shaderType);
unsigned int createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
