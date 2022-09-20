#include <GL/glew.h>
#include <iostream>

class Shader
{
public:	
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile();
	void UseProgram();
	GLuint GetUniformModel() {return uniformModel;  };
	GLuint GetUniformProjection() {return uniformProjection;  };

private:
	GLuint shaderId;
	GLuint uniformModel, uniformProjection;
	void Compile(const char* vertexCode, const char* fragmentCode);
};

