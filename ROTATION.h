// Arquivo : ROTATION.h
// Define m�todos para realizar rota��es em vetores 3D

#pragma once

#include "VECTOR3F.h"

class Rotation
{
public:
    // Rotaciona um vetor 3D em torno de um eixo por um �ngulo especificado (em radianos)
    static Vector3f rotateAroundAxis(const Vector3f& vector, const Vector3f& axis, float angle);
};

