//if "EBO_CLASS_H" is not defined, run this header file which defines the EBO class header on the first line
//This makes sure we don't accidentally define the EBO class header twice which would break everything
//EBO stands for Element Buffer Object
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

//include glad for OpenGL functionality
#include<glad/glad.h>

//Declare EBO class
class EBO
{
public:
	//Make ID a public variable
	GLuint ID;
	//Declare constructor that takes indices and size(?) of the vertices.
	EBO(GLuint* indices, GLsizeiptr size);

	//Declarations of Bind, Unbind and Delete functions which are in the "EBO.cpp" file
	void Bind();
	void Unbind();
	void Delete();
};

#endif
