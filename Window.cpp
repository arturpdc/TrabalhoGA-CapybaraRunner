// Arquivo : Window.cpp
// Implementa os m�todos da classe Window que � respons�vel por criar a janela do jogo
// e vai providenciar o acesso as suas propriedades

/*
	Definindo as bibliotecas necess�rias
*/
#include "WINDOW.h"
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// M�todo construtor da classe
Window::Window() : window(nullptr), width(390), height(844), title("Capybara Runner"), initialized(false)
{
	// Inicia o GLFW
	if (!glfwInit())
	{
		// Se falhar imprime a mensagem de erro
		std::cout << "Falha ao iniciar o GLFW" << std::endl;
		return;
	}

	// Configura o OpenGL para a vers�o 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Configura o framebuffer para suportar RGBA
	glfwWindowHint(GLFW_RED_BITS, 8); // 8 bits para o canal vermelho
	glfwWindowHint(GLFW_GREEN_BITS, 8); //8 bits para o canal verde
	glfwWindowHint(GLFW_BLUE_BITS, 8); // 8 bits para o canal azul
	glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits para o canal alfa

	// Cria uma janela em modo janela
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window)
	{
		// Se falhar imprime a mensagem de erro
		std::cout << "Falha ao criar a janela" << std::endl;
		glfwTerminate();
		return;
	}

	// Torna a janela atual
	glfwMakeContextCurrent(window);

	// Inicia o GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// Se falhar imprime a mensagem de erro
		std::cout << "Falha ao inicializar o GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	// Marca a janela como inicializada
	initialized = true;

	// Configura o OpenGL para usar RGBA
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Mensagem de Debug
	std::cout << "Janela criada com sucesso com suporte a RGBA!" << std::endl;
}

// M�todo destrutor da classe
Window::~Window()
{
	if (window)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

// Verifica se a janela foi criada corretamente
bool Window::isInitialized() const
{
	return initialized;
}

// Retorna a largura da janela
int Window::getWidth() const
{
	return width;
}

// Retorna a altura da janela
int Window::getHeight() const
{
	return height;
}

// Retorna o ponteiro da janela GLFW
GLFWwindow* Window::getWindow() const
{
	return window;
}

// M�otdo para renderizar a Janela
void Window::render() const
{
	// Limpa o buffer de cor e profundidade
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Troca os buffers para exibir o conte�do renderizado
	glfwSwapBuffers(window);

	// Processa os eventos da janela
	glfwPollEvents();

	// Mensagem de Debug
	std::cout << "[Window::render] Tela renderizada com sucesso!" << std::endl;
}

// Configura a vis�o ortogr�fica
void Window::setOrthographicView() const
{
	// Define a matriz de proje��o ortogr�fica
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1); // Define a vis�o ortogr�fica com origem no canto superior esquerdo

	// Retorna para a matriz de modelagem
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Mensagem de Debug
	std::cout << "[Window::setOrthographicView] Vis�o ortogr�fica configurada!" << std::endl;
}
