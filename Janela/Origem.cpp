#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include<vector>
#include "Mesh.h"
#include "Shader.h"



std::vector<Mesh*> listMesh;
std::vector<Shader*> listShader;


//Vertex Array
static const char* vShader = "                        \n\
#version 330                                          \n\
                                                      \n\
layout(location = 0) in vec3 pos;                     \n\
uniform mat4 model;                                   \n\
uniform mat4 projection;                              \n\
out vec4 vColor;                                      \n\
                                                      \n\
                                                      \n\
void main(){										  \n\
	gl_Position = projection * model * vec4(pos, 1.0); \n\
	vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);                   \n\
}                                                     \n\
                                                      ";



static const char* fShader = "                        \n\
#version 330                                          \n\
                                                      \n\
out vec4 color;                                       \n\
in vec4 vColor;                                        \n\
uniform vec3 triangleColor;                           \n\
                                                       \n\
void main() {                          \n\
	                                    \n\
		color = vColor;                \n\
}                                                     \n\
                                                      ";


void CriaTriangulos() {
	GLfloat vertices[] = {
		//x , y
		0.0f, 1.0f, 0.0f, //vertice 0 (verde)
		-1.0f, -1.0f, 0.0f, //vertice 1 (preto)
		1.0f, -1.0f, 0.0f, //vertice 2 (vermelho)
		0.0f, -1.0f, 1.0f //vertice 3 (azul)
	};

	GLuint indice[] = {
		0, 1, 3,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//CreateMesh
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, sizeof(vertices), indice, sizeof(indice));
	listMesh.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, sizeof(vertices), indice, sizeof(indice));
	listMesh.push_back(obj2);

}

void CriaShader() {
	Shader* shader = new Shader();
	shader->CreateFromString(vShader, fShader);
	listShader.push_back(shader);
}

int main() {
	if (!glfwInit()) {
		printf("GLFW: Não pode ser iniciado");
		return 1;
	};

	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Ola Mundo!", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW: Não foi possível criar janela");
		glfwTerminate;
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	if (glewInit() != GLEW_OK) {
		printf("Glew: Não pode ser iniciado!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
		;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	CriaTriangulos();
	CriaShader();

	float triangleOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.005f;
	bool direction = true;

	float rotationOffset = 0.0f, maxRotation = 360.0f, minRotation = -0.1f, incRotation = 0.005f;
	bool rotation = true;

	float scaleOffset = 0.4f, maxScale = 0.7f, minScale = 0.3f, incScale = 0.005f;
	bool scale = true;

	while (!glfwWindowShouldClose(mainWindow)) {

		//Habilitar os eventos do usuario
		glfwPollEvents();

		glClearColor(1.0f, 0.75f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Desenha o triangulo
		Shader* shader = listShader[0];
		shader->UseProgram();
		shader->UseProgram();

		//Mover o triangulo
		triangleOffset += direction ? incOffset : incOffset * -1;
		if (triangleOffset >= maxOffset || triangleOffset <= minOffset) direction = !direction;

		//Rotacao do triangulo
		rotationOffset += rotation ? incRotation : incRotation * -1;
		if (rotationOffset >= maxRotation || rotationOffset <= minRotation)
			rotation = !rotation;

		//Scale do triangulo
		scaleOffset += scale ? incScale : incScale * -1;
		if (scaleOffset >= maxScale || scaleOffset <= minScale)
			scale = !scale;

		//Triangulo 1
		listMesh[0]->RenderMesh();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f , -11.1f));
		model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

		//Triangulo 2
		listMesh[1]->RenderMesh();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f , -10.0f));
		model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, -0.4f));

		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
		

		//Projecção de pesperctiva 3D
		glm::mat4 projection = glm::perspective(1.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);
		glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));


		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}

