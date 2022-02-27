#include<iostream>
#include <string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>


//




//




//




//




//Below is where graphics programming starts.



//Including all the class header files created for the shader, VAO, VBO and EBO.
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Declaring the vertices of our shape.
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};


//indices which define the order in which OpenGL should render the vertices above.
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main()
{
	//Initializing GLFW
	glfwInit();

	//Defining versions we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Only interested in the basic modern functions of GLFW so we use the Core Profile.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	


	//The datatype of a window object. The attributes are as follows: width of window, height of window, name of the window, whether it should be fullscreen, idk what the last one is.
	GLFWwindow* window = glfwCreateWindow(800, 800, "Chess Graphics", NULL, NULL);

	//If the window fails to initialize, we output a message and terminate GLFW.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//GLFW is dumb so we have to tell it to use the window we just made
	glfwMakeContextCurrent(window);

	//Load glad into our program
	gladLoadGL();


	//We need to tell it where the window starts and ends, from the bottom left corner (0, 0) to the top right corner (800, 800)
	glViewport(0, 0, 800, 800);

	

	Shader shaderProgram("default.vert", "default.frag");

	//Generating the VAO and binding it.
	VAO VAO1;
	VAO1.Bind();

	//Generate Vertex Buffer and links it to vertices.
	VBO VBO1(vertices, sizeof(vertices));

	//Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	//Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	
	//Unbind all Vertex Array Object, Vertex Buffer Object and Element Buffer Object so we don't destroy everything accidentally.
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	//This prepares the colour value we want to use. First 3 values are decimal, normalised RGB values.
	//Last value is the alpha value (how transparent it is).
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	//The next line tells the computer to use the colour we prepared on the back buffer (effectively the background here).
	glClear(GL_COLOR_BUFFER_BIT);
	//This line swaps the window from the front buffer which uses the default colour to the back buffer with the colour we have defined.
	glfwSwapBuffers(window);

	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("512_512_chessboard.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	//This next while loop stops GLFW from terminating until after the window has been closed.
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);


		


		//This processes all the events. Idk what really happens but if you don't include this the window won't respond.
		glfwPollEvents();
	}

	//Deleting the vertex array, vertex buffer and element buffer objects as well as shaderprogram to save memory.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glad_glDeleteTextures(1, &texture);

	//Destroying the window and GLFW before we end the program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}