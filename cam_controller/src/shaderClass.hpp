#ifndef SHADER_CLASS_HPP
#define SHADER_CLASS_HPP

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <string>
#include "Utils.hpp"

std::string get_file_contents(const char* filename);

class Shader{
	public:
		GLuint ID;
		Shader(const char* vertexFile,const char* fragmentFile);
		
		void Activate();
		void Delete();
	private:
		void compileErrors(unsigned int shader, std::string type);
};

#endif