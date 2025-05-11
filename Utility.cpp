// Arquivo : Utility.cpp
// Implementa utilitários para shaders

#include "UTILITY.h"
#include <iostream>
#include <GLAD/glad.h>

// Compila um shader (Vertex ou Fragment)
unsigned int compileShader(const std::string& source, GLenum shaderType)
{
    // Cria o shader
    unsigned int shader = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // Verifica erros de compilação
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Erro ao compilar o shader: " << infoLog << std::endl;
    }

    return shader;
}

// Cria um programa de shader a partir de um Vertex e Fragment Shader
unsigned int createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
    // Compila os shaders
    unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Cria o programa de shader
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Verifica erros de linkagem
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Erro ao linkar o programa de shader: " << infoLog << std::endl;
    }

    // Exclui os shaders intermediários
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
