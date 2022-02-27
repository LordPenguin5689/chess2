//if "VAO_CLASS_H" is not defined, run this header file which defines the VAO class header on the first line
//This makes sure we don't accidentally define the VAO class header twice which would break everything
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

//include glad for the OpenGL functionality
#include<glad/glad.h>
//Include "VBO.h" as we will need to link the VBO to the VAO.
//Remeber that VAO is the Vertex Array Object and that VBO is the Vertex Buffer Object.
#include"VBO.h"

//Class for VAO
class VAO
{
	public:
		//Public ID for the VAO
		GLuint ID;
		//Constructor with no parameters. This constructor will just generate the object. See "VAO.cpp" for the constructor.
		VAO();

		//Here we link the VBO to the VAO, giving a pointer of VBO and and GL unsigned integer of "layout". See "VAO.cpp"
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		//Functions that Bind, Unbind and Delete the the object. Can be found in "VAO.cpp"
		void Bind();
		void Unbind();
		void Delete();
};

#endif
