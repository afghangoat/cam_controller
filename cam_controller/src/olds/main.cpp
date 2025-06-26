#include <GL/glew.h>

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <glad.h>


#include <cmath>

#include "shaderClass.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"

//https://www.youtube.com/watch?v=45MIykWJ-C4&t=80s
//38:00

const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=600;

GLfloat vertices[]={
	-0.5f, -0.5f*float(sqrt(3))/3,0.0f,
	0.5f,-0.5f*float(sqrt(3))/3,0.0f,
	0.0f,0.5f*float(sqrt(3))*2/3,0.0f,
	
	-0.5f/2,0.5f*float(sqrt(3))/6,0.0f,
	0.5f/2,0.5f*float(sqrt(3))/6,0.0f,
	0.0f,-0.5f*float(sqrt(3))/3,0.0f,
};
GLuint indices[]={
	0,3,5,
	3,2,4,
	5,4,1
};
	
Shader* shaderProgram;
VAO* vao1;
VBO* vbo1;
EBO* ebo1; //Index buffer

// Initialize OpenGL settings
void init() {
	
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return;
	}

	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	
	shaderProgram=new Shader("./src/imports/shaders/default.vert", "./src/imports/shaders/default.frag");
	
	vao1=new VAO();
	vbo1 = new VBO(vertices, sizeof(vertices));
	
	
	vao1->Bind();
	
	vbo1->Bind();
	
	ebo1 = new EBO(indices, sizeof(indices));
	
	vao1->LinkVBO(*vbo1,0);
	
	//Unbind Objects
	vbo1->Unbind();
	vao1->Unbind();
	ebo1->Unbind();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //RGBA

    glMatrixMode(GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT);
	
    //glLoadIdentity();
    //glOrtho(0.0, 2.0, -1.0, 8.0, -1.0, 1.0);  // Adjust the visible range
    //glMatrixMode(GL_MODELVIEW);
}

void drawTriangle() {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
        glVertex2f(0.5f, 0.0f); // First vertex
        glVertex2f(0.5f, 0.5f); // Second vertex
        glVertex2f(0.0f, 0.5f); // Third vertex
    glEnd();
}
// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

	shaderProgram->Activate();
	vao1->Bind();
	//glDrawArrays(GL_TRIANGLES,0,3);
	glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
    // Draw a red triangle (commented out in the original C code)
   // drawTriangle();

    glFlush(); // Render the graphics
}


int main(int argc, char** argv) {
    // GLUT setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Test");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

	vao1->Delete();
	vbo1->Delete();
	ebo1->Delete();
	shaderProgram->Delete();
	
    return 0;
}