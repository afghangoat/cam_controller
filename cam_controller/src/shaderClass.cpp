#include "shaderClass.hpp"

std::string get_file_contents(const char* filename){
	std::ifstream in(filename, std::ios::binary);
	if (in){
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw std::runtime_error("Failed to load file: "+std::string(filename));
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	if(debug==true){
		compileErrors(vertexShader,"VERTEX");
	}
	

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	if(debug==true){
		compileErrors(fragmentShader,"FRAGMENT");
	}
	

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	if(debug==true){
		compileErrors(ID,"PROGRAM");
	}

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, std::string type){
	GLint hasCompiled;
	char infoLog[1024];
	if(type != "PROGRAM"){
		glGetShaderiv(shader,GL_COMPILE_STATUS,&hasCompiled);
		if(hasCompiled==GL_FALSE){
			glGetShaderInfoLog(shader,1024,NULL,infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " <<type << "\n" << std::endl;
		}
	} else {
		glGetProgramiv(shader,GL_LINK_STATUS,&hasCompiled);
		if(hasCompiled==GL_FALSE){
			glGetProgramInfoLog(shader,1024,NULL,infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " <<type << "\n" << std::endl;
		}
	}
}