// Arquivo: VECTOR3F.h
// Define a classe Vector3f para opera��es matem�ticas em 3D
#pragma once

#include <iostream>
#include <cmath>

class Vector3f
{
public:
    // Componentes do vetor
    float x, y, z;

    // Construtor padr�o
    Vector3f();

    // Construtor com valores iniciais
    Vector3f(float x, float y, float z);

    // Adi��o de dois vetores
    Vector3f operator+(const Vector3f& other) const;

    // Subtra��o de dois vetores
    Vector3f operator-(const Vector3f& other) const;

    // Produto escalar (dot product)
    float dot(const Vector3f& other) const;

    // Magnitude (comprimento) do vetor
    float magnitude() const;

    // Normaliza��o do vetor
    Vector3f normalize() const;

    // Impress�o do vetor (para debug)
    void print() const;
};
