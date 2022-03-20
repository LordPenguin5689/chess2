#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}


void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	//see https://www.khronos.org/registry/OpenGL-Refpages/gl4/
	//Layout is a variable that specifies the index of the generic vertex attribute to be modified.
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	//Bind the VAO
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	//Unbind the VAO
	glBindVertexArray(0);
}

void VAO::Delete()
{
	//Delete the VAO
	glDeleteVertexArrays(1, &ID);
}