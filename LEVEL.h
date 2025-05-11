// Arquivo : LEVEL.h
// Define a classe LEVEL e a classe Obstacle

#pragma once
#define DEBUG_LEVEL 1

/*
	Incluindo as bibliotecas necess�rias
*/
#include <vector>
#include "PLAYER.h"
#include "COLLISIONS.h"
#include <GLFW/glfw3.h>

// Classe para representar um obst�culo
class Obstacle
{
public:
	Obstacle(float x, float y, float width, float height);

	// Renderiza o obst�culo
	void render() const;

	// Retorna a hitbox do obst�culo
	Hitbox getHitbox() const;

	float getX() const { return posX; } // Retorna a posi��o X do obst�culo

private:
	float posX;    // Posi��o X do obst�culo
	float posY;    // Posi��o Y do obst�culo
	float width;   // Largura do obst�culo
	float height;  // Altura do obst�culo
};

class Level
{
public:
	// M�todo construtor que aceita uma janela existente
	Level(GLFWwindow* existingWindow);

	// M�todo destrutor
	~Level();

	// M�todo de Inicializa��o
	void initialize();

	// Renderiza o n�vel
	void render();

	// Lida com a entrada do jogador
	void handleInput();

	// Verifica se o n�vel est� ativo
	bool isActive() const;

	// Aguarda o movimento do jogador antes de iniciar o jogo
	void waitForPlayerInput();

	// Limpa os recursos quando n�o s�o mais necess�rios
	void cleanup();

	// Adiciona obst�culos
	void addObstacle(const Obstacle& obstacle);

	// Renderiza os obst�culos
	void renderObstacles();

	// Renderiza o ch�o
	void renderFloor();

	// Verifica se o jogador est� sobre o ch�o
	void checkPlayerOnFloor();

	// Manuzeia as colis�es dos obst�culos
	void handleObstacleCollisions();

	// Gera novos obst�culos dinamicamente
	void generateObstacles();

	// Remove obst�culos que sa�ram da �rea vis�vel
	void removeOffscreenObstacles();

	// Checa erros 
	void checkGLError(const std::string& context);

private:
	GLFWwindow* window; // Janela do GLFW
	Player player;		// Objeto do jogador
	bool active;		// Indica se o n�vel est� ativo
	std::vector<Obstacle> obstacles;
	float floorY;		// Posi��o Y do ch�o
	float lastGeneratedX; // �ltima posi��o X onde um obst�culo foi gerado
	bool isFirstObstacle; // Indica se o pr�ximo obst�culo � o primeiro
};


