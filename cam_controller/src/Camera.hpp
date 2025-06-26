#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.hpp"
class CameraController{
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f,0.0f,-1.0f);
		glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);
		
		int width;
		int height;
		
		float speed=0.1f;
		float sensitivity=1.0f;
		
		CameraController(int width,int height, glm::vec3 position);
		
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		
		void keyboard(unsigned char key, int x, int y);
		void keyboardUp(unsigned char key, int x, int y);
		void specialKeys(int key, int x, int y);
		void mouseClick(int button, int state, int x, int y);
		void mouseMotion(int x, int y);

};
#endif