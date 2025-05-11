// Arquivo : Rotation.cpp
// Implementa métodos para realizar rotações em vetores 3D

#include "ROTATION.h"
#include <cmath>

// Rotaciona um vetor 3D em torno de um eixo por um ângulo especificado (em radianos)
Vector3f Rotation::rotateAroundAxis(const Vector3f& vector, const Vector3f& axis, float angle)
{
    // Normaliza o eixo de rotação
    Vector3f normalizedAxis = axis.normalize();

    // Calcula os componentes do eixo normalizado
    float u = normalizedAxis.x;
    float v = normalizedAxis.y;
    float w = normalizedAxis.z;

    // Calcula os valores trigonométricos
    float cosTheta = std::cos(angle);
    float sinTheta = std::sin(angle);

    // Calcula os elementos da matriz de rotação
    float m00 = cosTheta + u * u * (1 - cosTheta);
    float m01 = u * v * (1 - cosTheta) - w * sinTheta;
    float m02 = u * w * (1 - cosTheta) + v * sinTheta;

    float m10 = v * u * (1 - cosTheta) + w * sinTheta;
    float m11 = cosTheta + v * v * (1 - cosTheta);
    float m12 = v * w * (1 - cosTheta) - u * sinTheta;

    float m20 = w * u * (1 - cosTheta) - v * sinTheta;
    float m21 = w * v * (1 - cosTheta) + u * sinTheta;
    float m22 = cosTheta + w * w * (1 - cosTheta);

    // Aplica a matriz de rotação ao vetor
    float x = m00 * vector.x + m01 * vector.y + m02 * vector.z;
    float y = m10 * vector.x + m11 * vector.y + m12 * vector.z;
    float z = m20 * vector.x + m21 * vector.y + m22 * vector.z;

    return Vector3f(x, y, z);
}

