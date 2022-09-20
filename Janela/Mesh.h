#include "GL/glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void CreateMesh(GLfloat* vertices, unsigned int numOfVertice, GLuint* indices, unsigned int numOfIndices);
	void RenderMesh();

private:
	GLuint VAO, VBO, VBI;
	GLuint numOfIndices;

};



