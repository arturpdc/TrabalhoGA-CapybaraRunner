// Arquivo : COLLISIONS.h
// Aqui está sendo definido a classe Colision contendo todas as suas variaveis
#pragma once

// Estrutura para representar a hitbox de um objeto
struct Hitbox
{
	float x;		// Posição X do canto superior esquerdo
	float y;		// Posição Y do canto superior esquerdo
	float width;	// Largura da hitbox
	float height;	// Altura da hitbox
};

// Função para verificar se duas hitbox estão colidindo
bool checkCollision(const Hitbox& a, const Hitbox& b);