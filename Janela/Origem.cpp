#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main() {
	if (!glfwInit()) {

		printf("GLFW: Não pode ser iniciado");
		return 1;
	}

	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

	if (!mainWindow) {
		printf("GLFW: Não foi possivel criar a janelita");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK) {
		printf("Deu erro ao iniciar o GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	while (!glfwWindowShouldClose(mainWindow)) {
		// Habilitar eventos do usuario
		glfwPollEvents();

		glClearColor((255 / 255), (171 / 255), (255 / 255), (1 / 255));
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}