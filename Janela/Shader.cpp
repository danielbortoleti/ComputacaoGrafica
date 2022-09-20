#include "Shader.h"

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	Compile(vertexCode, fragmentCode);
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode) {
	shaderId = glCreateProgram(); //Cria um programa
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); //Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); //Cria um shader

	//Gambiarra para converter Char em GLChar
	const GLchar* vCode[1];
	const GLchar* fCode[1];
	vCode[0] = vertexCode; //Código do vShader
	fCode[0] = fragmentCode; //Código do fShader

	glShaderSource(_vShader, 1, vCode, NULL); //Associa o shader ao código
	glCompileShader(_vShader); //Compila o shader

	glShaderSource(_fShader, 1, fCode, NULL); //Associa o shader ao código
	glCompileShader(_fShader); //Compila o shader

	glAttachShader(shaderId, _vShader); //Adiciona o shader ao programa
	glAttachShader(shaderId, _fShader); //Adiciona o shader ao programa

	glLinkProgram(shaderId); //Adiciona o programa
	uniformModel = glGetUniformLocation(shaderId, "model");
	uniformProjection = glGetUniformLocation(shaderId, "projection");

}

void Shader::UseProgram() {
	glUseProgram(shaderId);
}

Shader::Shader() {

}

Shader::~Shader() {

}
