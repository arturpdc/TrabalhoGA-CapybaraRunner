// Arquivo : COLLISIONS.h
// Aqui est� sendo definido a classe Colision contendo todas as suas variaveis
#pragma once

// Estrutura para representar a hitbox de um objeto
struct Hitbox
{
	float x;		// Posi��o X do canto superior esquerdo
	float y;		// Posi��o Y do canto superior esquerdo
	float width;	// Largura da hitbox
	float height;	// Altura da hitbox
};

// Fun��o para verificar se duas hitbox est�o colidindo
bool checkCollision(const Hitbox& a, const Hitbox& b);