#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

GLuint VAO, VBO, programa;


//Vertex Shader
static const char* vShader = "                             \n\
#version 330                                               \n\
														   \n\
layout(location=0) in vec2 pos;                            \n\
														   \n\
void main(){                                               \n\
   gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);             \n\
}                                                          \n\
														   \n\
                                                            ";
static const char* fShader = "                             \n\
#version 330                                               \n\
														   \n\
out vec4 color;                                            \n\
														   \n\
void main(){                                               \n\
   color = vec4(1.0, 0.0, 0.0, 1.0);                       \n\
}                                                          \n\
														   \n\
                                                            ";

void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y
		0.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};
	
	glGenVertexArrays(1, &VAO); //Cria o VAO
	glBindVertexArray(VAO); //Coloca o VAO em contexto

	glGenBuffers(1, &VBO); //Cria o VBO

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Coloca o VBO em contexto
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Explica o valor do Array
	glV                               ertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); // Explica os valores de x e y
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//Remover do contexto o VBO

	glBindVertexArray(0); //Remover do contexto o VAO
}

void CompilaShader() {
	programa = glCreateProgram(); //Cria programa
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER);//Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER);//Cria um shader

	//Gambiarra para converter Char em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];
	vCode[0] = vShader;//C�digo do vShader
	fCode[0] = vShader;//C�digo do vShader

	glShaderSource(_vShader, 1, vCode, NULL);
	glCompileShader(_vShader);

	glShaderSource(_fShader, 1, fCode, NULL);
	glCompileShader(_fShader);

	glAttachShader(programa, _vShader);
	glAttachShader(programa, _fShader);

	glLinkProgram(programa);

}

int main() {
	if (!glfwInit()) {

		printf("GLFW: N�o pode ser iniciado");
		return 1;
	}

	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

	if (!mainWindow) {
		printf("GLFW: N�o foi possivel criar a janelita");
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

	CriaTriangulos();
	CompilaShader();
	while (!glfwWindowShouldClose(mainWindow)) {
		// Habilitar eventos do usuario
		glfwPollEvents();

		glClearColor((255 / 255), (171 / 255), (255 / 255), (1 / 255));
		glClear(GL_COLOR_BUFFER_BIT);

		//Desenha o triangulo
		glUseProgram(programa);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}