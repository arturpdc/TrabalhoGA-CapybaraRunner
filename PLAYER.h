// Arquivo : PLAYER.h
// Define a classe Player com suporte a textura, renderiza��o de um cubo e mec�nica de pulo
#pragma once

/*
	Incluindo as bibliotecas necess�rias
*/
#include <GLFW/glfw3.h>
#include "COLLISIONS.h"
#include <string>

class Player
{
public:
	// M�todo construtor que aceita uma janela existente
	Player(GLFWwindow* existingWindow);

	// Renderiza o jogador na tela
	void render();

	// Lida com a entrada do jogador
	void handleInput();

	// Atualiza a posi��o do jogador (inclui l�gica de pulo e gravidade)
	void update();

	// Define a posi��o inicial do jogador em um espa�o 2D
	void setPosition(float x, float y);

	// Obt�m a posi��o atual do jogador
	void getPosition(float& x, float& y) const;

	// Atualiza a posi��o da c�mera para seguir o jogador
	void updateCameraPosition();

	// Obt�m a posi��o atual da c�mera
	void getCameraPosition(float& x, float& y) const;

	// Retorna a hitbox do jogador
	Hitbox getHitbox() const;

	// Carrega a textura do jogador
	bool loadTexture(const std::string& filePath);

private:
	GLFWwindow* window; // Janela do GLFW
	float posX;			// Posi��o no eixo X do jogador
	float posY;			// Posi��o no eixo Y do jogador
	float speed;		// Velocidade de movimento do jogador
	float cameraX;		// Posi��o no eixo X da c�mera
	float cameraY;		// Posi��o no eixo Y da c�mera
	unsigned int textureID; // ID da textura carregada

	// Atributos para o pulo
	bool isJumping;			// Indica se o jogador est� pulando
	float jumpSpeed;		// Velocidade inicial do pulo
	float gravity;			// Gravidade aplicada ao jogador
	float verticalVelocity; // Velocidade vertical do jogador
};
