// Arquivo : LEVEL.h
// Define a classe LEVEL e a classe Obstacle

#pragma once
#define DEBUG_LEVEL 1

/*
	Incluindo as bibliotecas necessárias
*/
#include <vector>
#include "PLAYER.h"
#include "COLLISIONS.h"
#include <GLFW/glfw3.h>

// Classe para representar um obstáculo
class Obstacle
{
public:
	Obstacle(float x, float y, float width, float height);

	// Renderiza o obstáculo
	void render() const;

	// Retorna a hitbox do obstáculo
	Hitbox getHitbox() const;

	float getX() const { return posX; } // Retorna a posição X do obstáculo

private:
	float posX;    // Posição X do obstáculo
	float posY;    // Posição Y do obstáculo
	float width;   // Largura do obstáculo
	float height;  // Altura do obstáculo
};

class Level
{
public:
	// Método construtor que aceita uma janela existente
	Level(GLFWwindow* existingWindow);

	// Método destrutor
	~Level();

	// Método de Inicialização
	void initialize();

	// Renderiza o nível
	void render();

	// Lida com a entrada do jogador
	void handleInput();

	// Verifica se o nível está ativo
	bool isActive() const;

	// Aguarda o movimento do jogador antes de iniciar o jogo
	void waitForPlayerInput();

	// Limpa os recursos quando não são mais necessários
	void cleanup();

	// Adiciona obstáculos
	void addObstacle(const Obstacle& obstacle);

	// Renderiza os obstáculos
	void renderObstacles();

	// Renderiza o chão
	void renderFloor();

	// Verifica se o jogador está sobre o chão
	void checkPlayerOnFloor();

	// Manuzeia as colisões dos obstáculos
	void handleObstacleCollisions();

	// Gera novos obstáculos dinamicamente
	void generateObstacles();

	// Remove obstáculos que saíram da área visível
	void removeOffscreenObstacles();

	// Checa erros 
	void checkGLError(const std::string& context);

private:
	GLFWwindow* window; // Janela do GLFW
	Player player;		// Objeto do jogador
	bool active;		// Indica se o nível está ativo
	std::vector<Obstacle> obstacles;
	float floorY;		// Posição Y do chão
	float lastGeneratedX; // Última posição X onde um obstáculo foi gerado
	bool isFirstObstacle; // Indica se o próximo obstáculo é o primeiro
};


