// Arquivo: Vector3f.cpp
// Implementa a classe Vector3f para opera��es matem�ticas em 3D

#include "VECTOR3F.h"

// Construtor padr�o
Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}

// Construtor com valores iniciais
Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

// Adi��o de dois vetores
Vector3f Vector3f::operator+(const Vector3f& other) const
{
    return Vector3f(x + other.x, y + other.y, z + other.z);
}

// Subtra��o de dois vetores
Vector3f Vector3f::operator-(const Vector3f& other) const
{
    return Vector3f(x - other.x, y - other.y, z - other.z);
}

// Produto escalar (dot product)
float Vector3f::dot(const Vector3f& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

// Magnitude (comprimento) do vetor
float Vector3f::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

// Normaliza��o do vetor
Vector3f Vector3f::normalize() const
{
    float mag = magnitude();
    if (mag == 0.0f)
        return Vector3f(0.0f, 0.0f, 0.0f);
    return Vector3f(x / mag, y / mag, z / mag);
}

// Impress�o do vetor (para debug)
void Vector3f::print() const
{
    std::cout << "Vector3f(" << x << ", " << y << ", " << z << ")" << std::endl;
}
