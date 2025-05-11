// Arquivo : Level.cpp
// Implementa os m�todos da classe Level para gerenciar o estado do jogo e renderizar o jogador

/*
	Incluindo as bibliotecas necess�rias
*/
#include "LEVEL.h"
#include "COLLISIONS.h"
#include "PLAYER.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib> // Para gerar n�meros aleat�rios
#include <ctime>   // Para inicializar o gerador de n�meros aleat�rios

// Construtor da classe Obstacle
Obstacle::Obstacle(float x, float y, float width, float height)
	: posX(x), posY(y), width(width), height(height) {
}

// Renderiza o obst�culo
void Obstacle::render() const
{
	glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha para o obst�culo
	glBegin(GL_QUADS);
	glVertex2f(posX, posY);               // Inferior Esquerdo
	glVertex2f(posX + width, posY);       // Inferior Direito
	glVertex2f(posX + width, posY + height); // Superior Direito
	glVertex2f(posX, posY + height);      // Superior Esquerdo
	glEnd();
}

// Retorna a hitbox do obst�culo
Hitbox Obstacle::getHitbox() const
{
	return Hitbox{ posX, posY, width, height };
}

// M�todo de Inicializa��o
void Level::initialize()
{
	// Mensagem de Debug
	std::cout << "[Level::initialize] Inicializando recursos do Level..." << std::endl;

	// Define a posi��o do ch�o (10% da altura da janela)
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	floorY = height * 0.9f;

	// Inicializa o gerador de n�meros aleat�rios
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Define a posi��o inicial para gera��o de obst�culos
	lastGeneratedX = 0.0f;
	isFirstObstacle = true; // O primeiro obst�culo ser� gerado com regras especiais

	// Gera obst�culos iniciais
	generateObstacles();
}

// Gera novos obst�culos dinamicamente
void Level::generateObstacles()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	// Define a �rea vis�vel da c�mera
	float cameraX, cameraY;
	player.getCameraPosition(cameraX, cameraY);
	float visibleAreaEndX = cameraX + width;

	// Obt�m as dimens�es do jogador
	float playerWidth = 50.0f; // Largura do jogador (assumindo 50x50)
	float playerJumpHeight = 15.0f * 15.0f / (2.0f * 0.8f); // Altura m�xima do pulo (f�rmula de f�sica)

	// Gera obst�culos enquanto a �rea vis�vel n�o estiver preenchida
	while (lastGeneratedX < visibleAreaEndX + 200.0f) // Gera um pouco al�m da �rea vis�vel
	{
		float obstacleWidth = playerWidth; // Largura do obst�culo � igual � largura do jogador
		float obstacleHeight = playerJumpHeight / 2.0f; // Altura do obst�culo � metade da altura do pulo

		float obstacleX;
		if (isFirstObstacle)
		{
			// O primeiro obst�culo est� a 6x a largura do jogador
			obstacleX = lastGeneratedX + 6.0f * playerWidth;
			isFirstObstacle = false; // Ap�s o primeiro, segue as regras normais
		}
		else
		{
			// Espa�amento aleat�rio entre 1x e 4x a largura do jogador
			float spacing = static_cast<float>(std::rand() % 4 + 1) * playerWidth;
			obstacleX = lastGeneratedX + spacing;
		}

		float obstacleY = floorY - obstacleHeight; // Obst�culos logo acima do ch�o
		addObstacle(Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight)); // Adiciona o obst�culo
		lastGeneratedX = obstacleX;
	}
}

// Remove obst�culos que sa�ram da �rea vis�vel
void Level::removeOffscreenObstacles()
{
	float cameraX, cameraY;
	player.getCameraPosition(cameraX, cameraY);

	// Remove obst�culos que est�o fora da �rea vis�vel
	obstacles.erase(
		std::remove_if(obstacles.begin(), obstacles.end(), [cameraX](const Obstacle& obstacle) {
			return obstacle.getX() < cameraX - 200.0f; // Remove obst�culos 200 unidades antes da c�mera
			}),
		obstacles.end()
	);
}

// Renderiza o ch�o
void Level::renderFloor()
{
	// Define a cor do ch�o (cinza claro)
	glColor3f(0.8f, 0.8f, 0.8f);

	// Renderiza o ch�o como um ret�ngulo
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glBegin(GL_QUADS);
	glVertex2f(0, floorY);         // Inferior Esquerdo
	glVertex2f(width, floorY);    // Inferior Direito
	glVertex2f(width, height);    // Superior Direito
	glVertex2f(0, height);        // Superior Esquerdo
	glEnd();
}

// Verifica se o jogador est� sobre o ch�o
void Level::checkPlayerOnFloor()
{
	float playerX, playerY;
	player.getPosition(playerX, playerY);

	// Verifica se o jogador est� abaixo do ch�o
	if (playerY + 25 < floorY) // 25 � metade da altura do jogador
	{
		// Reposiciona o jogador no ch�o
		player.setPosition(playerX, floorY - 25);
		std::cout << "[Level::checkPlayerOnFloor] Jogador reposicionado no ch�o." << std::endl;
	}
}

// Renderiza os obst�culos
void Level::renderObstacles()
{
	for (const auto& obstacle : obstacles)
	{
		obstacle.render();
	}
}

// Adiciona obst�culos ao n�vel
void Level::addObstacle(const Obstacle& obstacle)
{
	obstacles.push_back(obstacle);
}

// Verifica colis�es entre o jogador e os obst�culos
void Level::handleObstacleCollisions()
{
	Hitbox playerHitbox = player.getHitbox();

	for (const auto& obstacle : obstacles)
	{
		Hitbox obstacleHitbox = obstacle.getHitbox();
		if (checkCollision(playerHitbox, obstacleHitbox))
		{
			// Mensagem de Debug
			std::cout << "[Level::handleObstacleCollisions] Colis�o detectada! O jogo ser� encerrado." << std::endl;
			glfwSetWindowShouldClose(window, GLFW_TRUE); // Fecha a janela do jogo
			break;
		}
	}
}

// Renderiza o n�vel
void Level::render()
{
#if DEBUG_LEVEL 
	std::cout << "[Level::render] Renderizando o Level..." << std::endl;
#endif

	// Limpa a tela
	glClear(GL_COLOR_BUFFER_BIT);

	// Renderiza o ch�o
	renderFloor();

	// Renderiza o jogador
	player.render();

	// Renderiza os obst�culos
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

	// Verifica se o jogador pressionou [ESC] para sair do n�vel
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		active = false; // Define o Level como inativo
	}

	// Verifica se o jogador est� sobre o ch�o
	checkPlayerOnFloor();

	// Gera novos obst�culos dinamicamente
	generateObstacles();

	// Remove obst�culos fora da �rea vis�vel
	removeOffscreenObstacles();

	// Verifica as colis�es com obst�culos
	handleObstacleCollisions();
}

// Limpa quando n�o � mais necess�rio
void Level::cleanup()
{
	// Mensagem de Debug
	std::cout << "[Level::cleanup] Limpando recursos do Level..." << std::endl;
	// Aqui pode ser adicionada uma l�gica de limpeza no futuro
}

// Verifica se o n�vel est� ativo
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

// M�todo construtor que aceita uma janela existente
Level::Level(GLFWwindow* existingWindow) : window(existingWindow), player(existingWindow), active(true)
{
	// Chama o m�todo de inicializa��o
	initialize();

	// Aguarda o movimento do jogador antes de iniciar o jogo
	waitForPlayerInput();

	// Define o n�vel como ativo
	active = true;
	// Mensagem de Debug
	std::cout << "Level foi iniciado com sucesso!" << std::endl;
}

// M�todo destrutor
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
