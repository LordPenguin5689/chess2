//include "VBO.h" header file, see that file for more info.
#include"VBO.h"

//Just incase you forget, VBO stands for Vertex Buffer Object.

//This is the constructor declared in the header file ("VBO.h").
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	//Generate the VBO. First parameter declares number of objects, second is specifying array in which the generated buffer object names are stored.
	glGenBuffers(1, &ID);
	//Bind the VBO and specify it is a GL_ARRAY_ BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Introduce the vertices
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	//Bind the VBO and specify it is a GL_ARRAY_ BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	//Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	//Delete the VBO
	glDeleteBuffers(1, &ID);
}