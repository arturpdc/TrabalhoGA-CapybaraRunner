// Arquivo : PLAYER.h
// Define a classe Player com suporte a textura, renderização de um cubo e mecânica de pulo
#pragma once

/*
	Incluindo as bibliotecas necessárias
*/
#include <GLFW/glfw3.h>
#include "COLLISIONS.h"
#include <string>

class Player
{
public:
	// Método construtor que aceita uma janela existente
	Player(GLFWwindow* existingWindow);

	// Renderiza o jogador na tela
	void render();

	// Lida com a entrada do jogador
	void handleInput();

	// Atualiza a posição do jogador (inclui lógica de pulo e gravidade)
	void update();

	// Define a posição inicial do jogador em um espaço 2D
	void setPosition(float x, float y);

	// Obtém a posição atual do jogador
	void getPosition(float& x, float& y) const;

	// Atualiza a posição da câmera para seguir o jogador
	void updateCameraPosition();

	// Obtém a posição atual da câmera
	void getCameraPosition(float& x, float& y) const;

	// Retorna a hitbox do jogador
	Hitbox getHitbox() const;

	// Carrega a textura do jogador
	bool loadTexture(const std::string& filePath);

private:
	GLFWwindow* window; // Janela do GLFW
	float posX;			// Posição no eixo X do jogador
	float posY;			// Posição no eixo Y do jogador
	float speed;		// Velocidade de movimento do jogador
	float cameraX;		// Posição no eixo X da câmera
	float cameraY;		// Posição no eixo Y da câmera
	unsigned int textureID; // ID da textura carregada

	// Atributos para o pulo
	bool isJumping;			// Indica se o jogador está pulando
	float jumpSpeed;		// Velocidade inicial do pulo
	float gravity;			// Gravidade aplicada ao jogador
	float verticalVelocity; // Velocidade vertical do jogador
};
