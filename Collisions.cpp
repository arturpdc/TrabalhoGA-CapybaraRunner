// Arquivo Collisions.cpp
// Implementa os métodos da classe
#include "COLLISIONS.h"

// Verifica se duas hitboxes estão colidindo
bool checkCollision(const Hitbox& a, const Hitbox b)
{
	// Verifica se há sobreposição entre as hitboxes
	return (a.x < b.x + b.width &&
		a.x + a.width > b.x &&
		a.y < b.y + b.height &&
		a.y + a.height > b.y);
}