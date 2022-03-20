//includes the "shaderClass.h" header file. See that for more info file for more info.
#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
//The function above is dark magic. I have no idea how it works, but it does what the comment above says it does.

//Below we have the shader constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//This uses the black magic function above to get the contents of the vertex and fragment files, which are the source code for the shader.
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Cast them into character arrays.
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();


	//GLuint is the OPENGL unsigned integer data type. Our vertexShader will contain a positive integer from glCreateShader function.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Tells the computer where the source of our shader is.
	//The parameters are as follows: reference value, specifying amount of strings for shader, point to source code, ignore last just NULL.
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//We have to compile it straight to machine code
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "Vertex");

	//Same as for the vertexShader but for the fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	//Reference value for the shaderProgram
	ID = glCreateProgram();

	//Attaching the shaders to the ShaderProgram
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	compileErrors(ID, "PROGRAM");


	//Deleting the shaders since they are already in the program so we don't need them anymore.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//Just functions that will activate and delete the shader program. Pretty self explanatory.
void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

//function that gives us an error message when there is an error. Makes debugging a little easier
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}