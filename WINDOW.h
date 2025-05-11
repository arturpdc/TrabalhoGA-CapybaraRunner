// Arquivo: WINDOW.h
// Vai definir a classe Window, que � respons�vel por criar a janela do jogo	
// Essa classe vai cuidar da cria��o da janela, vai ser respons�vel por definir o tamanho dela e vai providenciar o acesso para o GLFWwindow
#pragma once

/*
	Incluindo as bibliotecas necess�rias
*/
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	// Define o M�todo construtor da classe
	Window();

	// Define o M�todo destrutor da classe
	~Window();

	// Verifica se a janela foi criada corretamente
	bool isInitialized() const;
	
	// Retorna a largura da janela
	int getWidth() const;

	// Retorna a altura da janela
	int getHeight() const;

	// Retorna o ponteiro da janela GLFW
	GLFWwindow* getWindow() const;

	// M�todo para renderizar a janela
	void render() const;

	// Configura a vis�o ortogr�fica
	void setOrthographicView() const;

private:
	GLFWwindow* window; // Ponteiro para a janela GLFW
	int width; // Largura da janela
	int height; // Altura da janela
	const char* title; // Nome da janela
	bool initialized; // Verifica se a janela foi inicializada corretamente
};