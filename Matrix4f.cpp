// Arquivo : Matrix.cpp
// Implementa a classe Matrix

#include "MATRIX4f.h"
#include <stdexcept>
#include <iomanip>

// Construtor para criar uma matriz com linhas e colunas especificas
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<float>(cols, 0.0f)) {}

// Construtor para criar uma matriz a partir de um vetor bidimencional
Matrix::Matrix(const std::vector<std::vector<float>>& values) : rows(values.size()), cols(values[0].size()), data(values) {}

// Retorna o número de linhas
int Matrix::getRows() const
{
	return rows;
}

// Retorna o número de colunas
int Matrix::getCols() const
{
	return cols;
}

// Acessa o elemento da matriz
float& Matrix::at(int row, int col)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		throw std::out_of_range("Índice fora do intervalo");
	return data[row][col];
}

// Acessa um elemento da matriz (somente leitura)
const float& Matrix::at(int row, int col) const
{
	if (row < 0 || row >= rows || col < 0 || col >= cols)
		throw std::out_of_range("Indice fora do intervalo");
	return data[row][col];
}

// Multiplica a matriz por um vetor 3D
Vector3f Matrix::operator*(const Vector3f& vector) const
{
	if (cols != 3)
		throw std::invalid_argument("A matriz deve ter 3 colunas para multiplicação com um vetor 3D");
	std::vector<float> result(3, 0.0f);
	for (int i = 0; i < rows; i++)
	{
		result[i] = at(i, 0) * vector.x + at(i, 1) * vector.y + at(i, 2) * vector.z;
	}
	return Vector3f(result[0], result[1], result[2]);
}

// Imprime a matriz (para debug)
void Matrix::print() const
{
	for (const auto& row : data)
	{
		for (const auto& value : row)
		{
			std::cout << std::setw(8) << value << " ";
		}
		std::cout << std::endl;
	}
}