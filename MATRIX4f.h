#pragma once
// Arquivo : MATRIX.H
// Define a Classe Matrix contendo as opera��es necess�rias

#pragma once
#include <vector>
#include <iostream>
#include "VECTOR3F.h"

class Matrix
{
public: 
	// Construtor para criar uma matriz com linhas e colunas especificadas
	Matrix(int rows, int cols);

	// Construtor para criar uma matriz a partir de um vetor
	Matrix(const std::vector<std::vector<float>>& values);

	// Retorna o n�mero de linhas
	int getRows() const;

	// Retorna o n�mero de colunas
	int getCols() const;

	// Acessa um elemento da matriz
	float& at(int row, int col);

	// Acessa um elemento da matriz (somente leitura)
	const float& at(int row, int col) const;

	// Multiplica a matriz por um vetor 3D
	Vector3f operator*(const Vector3f& vector) const;

	// Imprime a matriz (para debug)
	void print() const;

private:
	int rows; // N�mero de linhas
	int cols; // N�mero de Colunas
	std::vector<std::vector<float>>data; // Dados da matriz
};