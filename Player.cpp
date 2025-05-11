// Arquivo: Player.cpp
// Implementa os métodos da classe Player para criar e controlar o jogador

/*
	Incluindo as bibliotecas necessárias
*/
#include "PLAYER.h"
#include "COLLISIONS.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h> // Biblioteca para carregar imagens

// Método construtor que aceita uma janela existente
Player::Player(GLFWwindow* existingWindow)
	: window(existingWindow), posX(0.0f), posY(0.0f), speed(5.0f), textureID(0), isJumping(false), jumpSpeed(15.0f), gravity(0.8f), verticalVelocity(0.0f)
{
	// Define a posição inicial do jogador no centro da tela
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	posX = width / 2.0f;
	posY = height - 100.0f; // Posição inicial próxima à parte inferior da tela

	// Inicializa a posição da câmera para seguir o jogador
	cameraX = posX - width / 2.0f;
	cameraY = posY - height / 2.0f;

	// Carrega a textura do jogador
    std::string texturePath = std::string(getenv("USERPROFILE")) + "\\Desktop\\CapybaraPhoto.JPG";
	if (!loadTexture(texturePath))
	{
		// Caso falhe mostra a mensagem de erro
		std::cerr << "Falha ao carregar a textura do jogador: " << texturePath << std::endl;
	}
}

// Método para carregar a textura do jogador
bool Player::loadTexture(const std::string& filePath)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // Inverte a imagem verticalmente
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		// Caso falhe mostra a mensagem de erro
		std::cerr << "Falha ao carregar a imagem: " << filePath << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Configura os parâmetros da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Carrega a textura para o OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return true;
}

// Renderiza o jogador
void Player::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Configurando o tamanho do jogador
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Configurando a projeção ortográfica
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(cameraX, cameraX + width, cameraY, cameraY + height, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Renderiza o cubo com a textura
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(posX - 25, posY - 25); // Superior Esquerdo
	glTexCoord2f(1.0f, 0.0f); glVertex2f(posX + 25, posY - 25); // Superior Direito
	glTexCoord2f(1.0f, 1.0f); glVertex2f(posX + 25, posY + 25); // Inferior Direito
	glTexCoord2f(0.0f, 1.0f); glVertex2f(posX - 25, posY + 25); // Inferior Esquerdo
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

// Lida com a entrada do jogador
void Player::handleInput()
{
	// Verifica se a tecla [A] foi pressionada para mover para a esquerda
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		posX -= speed;
		std::cout << "O jogador está se movendo para a esquerda. Posição atual: (" << posX << ", " << posY << ")" << std::endl;
	}

	// Verifica se a tecla [D] foi pressionada para mover para a direita
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		posX += speed;
		std::cout << "O jogador está se movendo para a direita. Posição atual: (" << posX << ", " << posY << ")" << std::endl;
	}

	// Verifica se a tecla [ESPAÇO] foi pressionada para pular
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !isJumping)
	{
		isJumping = true;
		verticalVelocity = jumpSpeed;
		std::cout << "O jogador iniciou um pulo." << std::endl;
	}
}

// Atualiza a posição do jogador (inclui lógica de pulo e gravidade)
void Player::update()
{
	if (isJumping)
	{
		// Aplica a gravidade ao jogador
		verticalVelocity -= gravity;
		posY += verticalVelocity;

		// Verifica se o jogador atingiu o chão
		if (posY <= 100.0f) // Supondo que o chão está na posição Y = 100
		{
			posY = 100.0f;
			isJumping = false;
			verticalVelocity = 0.0f;
			std::cout << "O jogador aterrissou no chão." << std::endl;
		}
	}

	// Atualiza a posição da câmera
	updateCameraPosition();
}

// Define a posição inicial do jogador
void Player::setPosition(float x, float y)
{
	posX = x;
	posY = y;
}

// Obtém a posição atual do jogador
void Player::getPosition(float& x, float& y) const
{
	x = posX;
	y = posY;
}

// Atualiza a posição da câmera para seguir o jogador
void Player::updateCameraPosition()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	// Centraliza a câmera na posição do jogador
	cameraX = posX - width / 2.0f;
	cameraY = posY - height / 2.0f;
}

// Obtém a posição atual da câmera
void Player::getCameraPosition(float& x, float& y) const
{
	x = cameraX;
	y = cameraY;
}

// Adiciona a função de checar erros no OpenGL
void checkGLError()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error: " << err << std::endl;
	}
}

// Método para obter a hitbox do jogador
Hitbox Player::getHitbox() const
{
	return Hitbox
	{
		posX - 25, // X do canto superior esquerdo
		posY - 25, // Y do canto superior esquerdo
		50,		   // Largura (50 = 25 * 2)
		50		   // Altura (50 = 25 * 2)
	};
}
