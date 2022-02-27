//if "SHADER_CLASS_H" is not defined, run this header file which defines the shader class header on the first line
//This makes sure we don't accidentally define the Shader class header twice which would break everything
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

//Have to inclue all these libraries. string and iostream are generic c++ ones. Glad is a library essential for our shaders.
//I have literally 0 idea what the rest are, but they are needed in the "shaderClass.cpp" so we include them here.
//we will include "shaderClass.h" in the "shaderClass.cpp" so all of these are automatically included in "shaderClass.cpp"
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>>
#include<cerrno>

//Simply get the contents of the shader text files.
std::string get_file_contents(const char* filename);

//Declaring the Shader class. This is an OpenGL shader program.
class Shader
{
	public:
		//ID is public so it can be referenced
		GLuint ID;
		//Constructor that takes the shader source code from the text files.
		Shader(const char* vertexFile, const char* fragmentFile);

		//Functions to activate and Delete the Shader program which are written in the "shaderClass.cpp"
		void Activate();
		void Delete();
		//private function that outputs the type of error when an error occurs.
	private:
		void compileErrors(unsigned int shader, const char* type);
};

#endif