#include "Camera.hpp"

CameraController::CameraController(int width,int height, glm::vec3 position){
	CameraController::width=width;
	CameraController::height=height;
	Position=position;
}

void CameraController::updateMatrix(float FOVdeg, float nearPlane, float farPlane){
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	view = glm::lookAt(Position,Position+Orientation,Up);
	projection = glm::perspective(glm::radians(FOVdeg),(float)width/(float)height,nearPlane,farPlane);
	
	cameraMatrix=projection*view;
}

void CameraController::Matrix(Shader& shader, const char* uniform){
	glUniformMatrix4fv(glGetUniformLocation(shader.ID,uniform),1,GL_FALSE,glm::value_ptr(cameraMatrix));
}

void CameraController::keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:  // ESC key
			exit(0);
			break;
		case 'w':
			//std::cout << "W key pressed" << std::endl;
			Position+= speed*Orientation;
			break;
		case 'a':
			Position+= speed*-glm::normalize(glm::cross(Orientation,Up));
			//std::cout << "A key pressed" << std::endl;
			break;
		case 's':
			Position+= speed*-Orientation;
			break;
		case 'd':
			Position+= speed*glm::normalize(glm::cross(Orientation,Up));
			break;
		
		case ' ':
			Position+= speed*Up;
			break;
		case 'q':
			Position+= speed*-Up;
			break;
	}
}

void CameraController::keyboardUp(unsigned char key, int x, int y) {
	std::cout << "Key released: " << key << std::endl;
}
void CameraController::specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			std::cout << "Up Arrow Pressed" << std::endl;
			break;
		case GLUT_KEY_DOWN:
			std::cout << "Down Arrow Pressed" << std::endl;
			break;
	}
}
void CameraController::mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN)
			std::cout << "Left button clicked at (" << x << ", " << y << ")" << std::endl;
	} else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN)
			std::cout << "Right button clicked" << std::endl;
	}
}
void CameraController::mouseMotion(int x, int y) {
	//std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
	double mouseX=x;
	double mouseY=y;
	float roty=sensitivity*(float)(mouseX-(height/2))/height;
	float rotx=sensitivity*(float)(mouseY-(height/2))/height;
	
	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx),glm::normalize(glm::cross(Orientation,Up)));
	if(!(glm::angle(newOrientation,Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation,Up) <= glm::radians(5.0f))){
		Orientation=newOrientation;
	}
	
	Orientation = glm::rotate(Orientation,glm::radians(-roty),Up);

}