// Arquivo: VECTOR3F.h
// Define a classe Vector3f para operações matemáticas em 3D
#pragma once

#include <iostream>
#include <cmath>

class Vector3f
{
public:
    // Componentes do vetor
    float x, y, z;

    // Construtor padrão
    Vector3f();

    // Construtor com valores iniciais
    Vector3f(float x, float y, float z);

    // Adição de dois vetores
    Vector3f operator+(const Vector3f& other) const;

    // Subtração de dois vetores
    Vector3f operator-(const Vector3f& other) const;

    // Produto escalar (dot product)
    float dot(const Vector3f& other) const;

    // Magnitude (comprimento) do vetor
    float magnitude() const;

    // Normalização do vetor
    Vector3f normalize() const;

    // Impressão do vetor (para debug)
    void print() const;
};
