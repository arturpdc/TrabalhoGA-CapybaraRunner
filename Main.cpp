// Arquivo : Main.cpp
// Implementa o método principal do jogo
// Esse é o arquivo pai de todos (ODIN)

/*
	Incluindo as Variáveis
*/
#include "WINDOW.h"
#include "LEVEL.h"
#include "UTILITY.h"
#include "VECTOR3F.h"
#include "MATRIX4f.h"
#include "ROTATION.h"

/*
	Incluindo as Bibliotecas necessárias
*/
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

int Main()
{
	// Cria a janela utilizando a classe Window
	Window window;

	// Verifica se a janela foi criada corretamente
	if (!window.isInitialized())
	{
		cout << "Falha ao criar a janela" << endl;
		return -1;
	}

	// Configura a visão ortográfica
	window.setOrthographicView();

	// Compila e linka os shaders
	unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

	// Cria o nível utilizando a janela existente
	Level level(window.getWindow());

	// Loop Principal do Jogo
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		// Limpa a tela
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Usa o programa de shader
		glUseProgram(shaderProgram);

		// Renderiza o nível
		level.render();

		// Lida com a entrada do jogador
		level.handleInput();

		// Renderiza a janela
		window.render();
	}

	// Finaliza o GLFW
	glfwTerminate();
	return 0;
}
