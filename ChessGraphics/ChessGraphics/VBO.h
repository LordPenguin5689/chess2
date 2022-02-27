//if "VBO_CLASS_H" is not defined, run this header file which defines the VBO class header on the first line
//This makes sure we don't accidentally define the VBO class header twice which would break everything
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

//Need to include glad for OpenGL functions
#include<glad/glad.h>

//public class for Vertex Buffer Object
class VBO
{
	public:
		//Public ID variable
		GLuint ID;
		//Constructor that takes some vertices and their size. See more in the "VBO.cpp" file
		//The size is in GLsizeiptr as that is what GLFW uses for size in bytes.
		VBO(GLfloat* vertices, GLsizeiptr size);

		//Declarations of Bind, Unbind and Delete functions which are in the "VBO.cpp" file
		void Bind();
		void Unbind();
		void Delete();
};

#endif
