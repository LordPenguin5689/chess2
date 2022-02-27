//Includes the EBO class header
#include"EBO.h"

//Constructor declared in "EBO.h" class header file
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	//Generates the buffer. First parameter is number of objects, second is specifying array in which the generated buffer object names are stored.
	glGenBuffers(1, &ID);
	//Bind the EBO and specify it is a GL_ARRAY_ BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	//Introduce the vertices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	//Bind the EBO and specify it is a GL_ARRAY_ BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	//Unbind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	//Delete the EBO
	glDeleteBuffers(1, &ID);
}