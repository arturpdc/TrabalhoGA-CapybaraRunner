// Arquivo : Level.cpp
// Implementa os métodos da classe Level para gerenciar o estado do jogo e renderizar o jogador

/*
	Incluindo as bibliotecas necessárias
*/
#include "LEVEL.h"
#include "COLLISIONS.h"
#include "PLAYER.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib> // Para gerar números aleatórios
#include <ctime>   // Para inicializar o gerador de números aleatórios

// Construtor da classe Obstacle
Obstacle::Obstacle(float x, float y, float width, float height)
	: posX(x), posY(y), width(width), height(height) {
}

// Renderiza o obstáculo
void Obstacle::render() const
{
	glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha para o obstáculo
	glBegin(GL_QUADS);
	glVertex2f(posX, posY);               // Inferior Esquerdo
	glVertex2f(posX + width, posY);       // Inferior Direito
	glVertex2f(posX + width, posY + height); // Superior Direito
	glVertex2f(posX, posY + height);      // Superior Esquerdo
	glEnd();
}

// Retorna a hitbox do obstáculo
Hitbox Obstacle::getHitbox() const
{
	return Hitbox{ posX, posY, width, height };
}

// Método de Inicialização
void Level::initialize()
{
	// Mensagem de Debug
	std::cout << "[Level::initialize] Inicializando recursos do Level..." << std::endl;

	// Define a posição do chão (10% da altura da janela)
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	floorY = height * 0.9f;

	// Inicializa o gerador de números aleatórios
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Define a posição inicial para geração de obstáculos
	lastGeneratedX = 0.0f;
	isFirstObstacle = true; // O primeiro obstáculo será gerado com regras especiais

	// Gera obstáculos iniciais
	generateObstacles();
}

// Gera novos obstáculos dinamicamente
void Level::generateObstacles()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	// Define a área visível da câmera
	float cameraX, cameraY;
	player.getCameraPosition(cameraX, cameraY);
	float visibleAreaEndX = cameraX + width;

	// Obtém as dimensões do jogador
	float playerWidth = 50.0f; // Largura do jogador (assumindo 50x50)
	float playerJumpHeight = 15.0f * 15.0f / (2.0f * 0.8f); // Altura máxima do pulo (fórmula de física)

	// Gera obstáculos enquanto a área visível não estiver preenchida
	while (lastGeneratedX < visibleAreaEndX + 200.0f) // Gera um pouco além da área visível
	{
		float obstacleWidth = playerWidth; // Largura do obstáculo é igual à largura do jogador
		float obstacleHeight = playerJumpHeight / 2.0f; // Altura do obstáculo é metade da altura do pulo

		float obstacleX;
		if (isFirstObstacle)
		{
			// O primeiro obstáculo está a 6x a largura do jogador
			obstacleX = lastGeneratedX + 6.0f * playerWidth;
			isFirstObstacle = false; // Após o primeiro, segue as regras normais
		}
		else
		{
			// Espaçamento aleatório entre 1x e 4x a largura do jogador
			float spacing = static_cast<float>(std::rand() % 4 + 1) * playerWidth;
			obstacleX = lastGeneratedX + spacing;
		}

		float obstacleY = floorY - obstacleHeight; // Obstáculos logo acima do chão
		addObstacle(Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight)); // Adiciona o obstáculo
		lastGeneratedX = obstacleX;
	}
}

// Remove obstáculos que saíram da área visível
void Level::removeOffscreenObstacles()
{
	float cameraX, cameraY;
	player.getCameraPosition(cameraX, cameraY);

	// Remove obstáculos que estão fora da área visível
	obstacles.erase(
		std::remove_if(obstacles.begin(), obstacles.end(), [cameraX](const Obstacle& obstacle) {
			return obstacle.getX() < cameraX - 200.0f; // Remove obstáculos 200 unidades antes da câmera
			}),
		obstacles.end()
	);
}

// Renderiza o chão
void Level::renderFloor()
{
	// Define a cor do chão (cinza claro)
	glColor3f(0.8f, 0.8f, 0.8f);

	// Renderiza o chão como um retângulo
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glBegin(GL_QUADS);
	glVertex2f(0, floorY);         // Inferior Esquerdo
	glVertex2f(width, floorY);    // Inferior Direito
	glVertex2f(width, height);    // Superior Direito
	glVertex2f(0, height);        // Superior Esquerdo
	glEnd();
}

// Verifica se o jogador está sobre o chão
void Level::checkPlayerOnFloor()
{
	float playerX, playerY;
	player.getPosition(playerX, playerY);

	// Verifica se o jogador está abaixo do chão
	if (playerY + 25 < floorY) // 25 é metade da altura do jogador
	{
		// Reposiciona o jogador no chão
		player.setPosition(playerX, floorY - 25);
		std::cout << "[Level::checkPlayerOnFloor] Jogador reposicionado no chão." << std::endl;
	}
}

// Renderiza os obstáculos
void Level::renderObstacles()
{
	for (const auto& obstacle : obstacles)
	{
		obstacle.render();
	}
}

// Adiciona obstáculos ao nível
void Level::addObstacle(const Obstacle& obstacle)
{
	obstacles.push_back(obstacle);
}

// Verifica colisões entre o jogador e os obstáculos
void Level::handleObstacleCollisions()
{
	Hitbox playerHitbox = player.getHitbox();

	for (const auto& obstacle : obstacles)
	{
		Hitbox obstacleHitbox = obstacle.getHitbox();
		if (checkCollision(playerHitbox, obstacleHitbox))
		{
			// Mensagem de Debug
			std::cout << "[Level::handleObstacleCollisions] Colisão detectada! O jogo será encerrado." << std::endl;
			glfwSetWindowShouldClose(window, GLFW_TRUE); // Fecha a janela do jogo
			break;
		}
	}
}

// Renderiza o nível
void Level::render()
{
#if DEBUG_LEVEL 
	std::cout << "[Level::render] Renderizando o Level..." << std::endl;
#endif

	// Limpa a tela
	glClear(GL_COLOR_BUFFER_BIT);

	// Renderiza o chão
	renderFloor();

	// Renderiza o jogador
	player.render();

	// Renderiza os obstáculos
	renderObstacles();

	// Verifica erros do OpenGL
	checkGLError("Level::render");

#if DEBUG_LEVEL 
	std::cout << "[Level::render] Level renderizado com sucesso" << std::endl;
#endif
}

// Lida com a entrada do jogador
void Level::handleInput()
{
	// Lida com a entrada do jogador
	player.handleInput();

	// Verifica se o jogador pressionou [ESC] para sair do nível
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		active = false; // Define o Level como inativo
	}

	// Verifica se o jogador está sobre o chão
	checkPlayerOnFloor();

	// Gera novos obstáculos dinamicamente
	generateObstacles();

	// Remove obstáculos fora da área visível
	removeOffscreenObstacles();

	// Verifica as colisões com obstáculos
	handleObstacleCollisions();
}

// Limpa quando não é mais necessário
void Level::cleanup()
{
	// Mensagem de Debug
	std::cout << "[Level::cleanup] Limpando recursos do Level..." << std::endl;
	// Aqui pode ser adicionada uma lógica de limpeza no futuro
}

// Verifica se o nível está ativo
bool Level::isActive() const
{
#if DEBUG_LEVEL
	static bool lastState = !active;
	if (lastState != active)
	{
		// Mensagem de Debug
		std::cout << "[Level::isActive] Estado do Level mudou para: " << (active ? "ativo" : "inativo") << std::endl;
		lastState = active;
	}
#endif
	return active;
}

// Método construtor que aceita uma janela existente
Level::Level(GLFWwindow* existingWindow) : window(existingWindow), player(existingWindow), active(true)
{
	// Chama o método de inicialização
	initialize();

	// Aguarda o movimento do jogador antes de iniciar o jogo
	waitForPlayerInput();

	// Define o nível como ativo
	active = true;
	// Mensagem de Debug
	std::cout << "Level foi iniciado com sucesso!" << std::endl;
}

// Método destrutor
Level::~Level()
{
	// Chama o limpador
	cleanup();
	// Mensagem de debug
	std::cout << "[Level::~Level] O nivel foi destruido." << std::endl;

	// Confere erros do OpenGL
	checkGLError("Level::~Level");
}

// Verifica erros no OpenGL com contexto
void checkGLError(const std::string& context)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "[OpenGL Error] Context:" << context << ", Error:" << err << std::endl;
	}
}
