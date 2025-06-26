#include <GL/glew.h>

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <glad.h>


#include <cmath>

#include "shaderClass.hpp"
#include "Texture.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"

#include "Camera.hpp"

const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=600;

//Triangles
/*GLfloat vertices[]={//Pos				//Colors		//Tex coords
	-0.5f, -0.5f*float(sqrt(3))/3,0.0f, 0.8f,0.3f,0.02f, 0.0f,0.0f,
	0.5f,-0.5f*float(sqrt(3))/3,0.0f, 0.8f,0.6f,0.02f, 0.0f,1.0f,
	0.0f,0.5f*float(sqrt(3))*2/3,0.0f, 0.8f,0.9f,0.02f, 0.0f,1.0f,
	
	-0.5f/2,0.5f*float(sqrt(3))/6,0.0f, 0.8f,0.3f,0.2f, 1.0f,1.0f,
	0.5f/2,0.5f*float(sqrt(3))/6,0.0f, 0.8f,0.3f,0.5f, 1.0f,0.0f,
	0.0f,-0.5f*float(sqrt(3))/3,0.0f, 0.8f,0.3f,0.9f, 1.0f,0.0f,
};
GLuint indices[]={
	0,3,5,
	3,2,4,
	5,4,1
};*/

//Rect
/*GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};*/

//Pyramid
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};
	
Shader* shaderProgram;
Shader* lightShader;
VAO* vao1;
VBO* vbo1;
EBO* ebo1; //Index buffer

VAO* light_vao1;
VBO* light_vbo1;
EBO* light_ebo1; //Index buffer

//GLuint uniID;
GLuint uinTex0;

Texture* texture1;

CameraController* player;

float rotation = 0.0f;
double prevTime = 0.0;

void updateRotation(int value);

// Initialize OpenGL settings
void init() {
	
	
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return;
	}
	glutTimerFunc(0, updateRotation, 0);

	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	prevTime = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	
	shaderProgram=new Shader("./src/imports/shaders/default.vert", "./src/imports/shaders/default.frag");
	vao1=new VAO();
	vbo1 = new VBO(vertices, sizeof(vertices));
	vao1->Bind();
	vbo1->Bind();
	ebo1 = new EBO(indices, sizeof(indices));
	//Pos
	vao1->LinkAttrib(*vbo1,0,3,GL_FLOAT,8*sizeof(float),(void*)0);
	//Color
	vao1->LinkAttrib(*vbo1,1,3,GL_FLOAT,8*sizeof(float),(void*)(3*sizeof(float)));
	//Texture
	vao1->LinkAttrib(*vbo1,2,2,GL_FLOAT,8*sizeof(float),(void*)(6*sizeof(float)));
	
	//Unbind Objects
	vbo1->Unbind();
	vao1->Unbind();
	ebo1->Unbind();
	
	//Light
	lightShader=new Shader("./src/imports/shaders/light.vert", "./src/imports/shaders/light.frag");
	light_vao1=new VAO();
	light_vbo1 = new VBO(lightVertices, sizeof(lightVertices));
	light_vao1->Bind();
	light_vbo1->Bind();
	light_ebo1 = new EBO(lightIndices, sizeof(lightIndices));
	//Light
	light_vao1->LinkAttrib(*vbo1,0,3,GL_FLOAT,3*sizeof(float),(void*)0);
	
	//Unbind Objects
	light_vbo1->Unbind();
	light_vao1->Unbind();
	light_ebo1->Unbind();
	
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos=glm::vec3(0.5f,0.5f,0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel=glm::translate(lightModel,lightPos);
	
	glm::vec3 pyramidPos=glm::vec3(0.0f,0.0f,0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel=glm::translate(pyramidModel,pyramidPos);
	
	//uniID=glGetUniformLocation(shaderProgram->ID,"scale"); //Get scale uniform.
	
	//Texture
	
	//uinTex0=glGetUniformLocation(shaderProgram->ID,"tex0");
	lightShader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//glUniform1i(uinTex0,0);
	texture1=new Texture("./src/imports/textures/bg_start.png",GL_TEXTURE_2D,GL_TEXTURE0,GL_UNSIGNED_BYTE);
	texture1->texUnit(*shaderProgram,"tex0",0);
	
	//Other GL flags
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //RGBA
	//Depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    //glMatrixMode(GL_PROJECTION);
	
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

void updateRotation(int value){ //TODO make this work.
	double curret_time=glutGet(GLUT_ELAPSED_TIME)/1000.0;
	if(curret_time -prevTime>=1.0/60.0){
		rotation+=0.5f;
		prevTime=curret_time;
	}
}
// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->Activate();
	
	rotation+=0.1f; //TODO delta_time
	
	//std::cout << "Rotation: " << rotation << std::endl;
	
	//Model, view and proj. matrix
	/*glm::mat4 model=glm::mat4(1.0f);
	glm::mat4 view=glm::mat4(1.0f);
	glm::mat4 proj=glm::mat4(1.0f);
	
	model=glm::rotate(model,glm::radians(rotation),glm::vec3(0.0f,1.0f,0.0f));
	
	view=glm::translate(view,glm::vec3(0.0f,-0.5f,-2.0f));
	proj=glm::perspective(glm::radians(45.0f),(float)(WINDOW_WIDTH/(float)WINDOW_HEIGHT),0.1f,100.0f); //TODO far and near plane
	
	int model_loc=glGetUniformLocation(shaderProgram->ID,"model");
	glUniformMatrix4fv(model_loc,1,GL_FALSE,glm::value_ptr(model));
	int view_loc=glGetUniformLocation(shaderProgram->ID,"view");
	glUniformMatrix4fv(view_loc,1,GL_FALSE,glm::value_ptr(view));
	int proj_loc=glGetUniformLocation(shaderProgram->ID,"proj");
	glUniformMatrix4fv(proj_loc,1,GL_FALSE,glm::value_ptr(proj));*/
	player->updateMatrix(45.0f,0.1f,100.0f);
	player->Matrix(*shaderProgram,"camMatrix");
	
	
	//glUniform1f(uniID,0.5f);
	
	texture1->Bind();
	vao1->Bind();
	//glDrawArrays(GL_TRIANGLES,0,3);
	glDrawElements(GL_TRIANGLES,sizeof(indices)/sizeof(int),GL_UNSIGNED_INT,0);
	
	lightShader->Activate();
	player->Matrix(*lightShader,"camMatrix");
	light_vao1->Bind();
	glDrawElements(GL_TRIANGLES,sizeof(lightIndices)/sizeof(int),GL_UNSIGNED_INT,0);
    // Draw a red triangle (commented out in the original C code)
   // drawTriangle();

	glutSwapBuffers();
    //glFlush(); // Render the graphics
}

//Callbacks
void Pkeyboard(unsigned char key, int x, int y){
	player->keyboard(key,x,y);
}
void PkeyboardUp(unsigned char key, int x, int y){
	player->keyboardUp(key,x,y);
}
void PspecialKeys(int key, int x, int y){
	player->specialKeys(key,x,y);
}
void PmouseClick(int button, int state, int x, int y){
	player->mouseClick(button,state,x,y);
}
void PmouseMotion(int x, int y){
	player->mouseMotion(x,y);
}
int main(int argc, char** argv) {
    // GLUT setup
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL cameracontroller demo");

    init();
	
	//TODO make a register camera function
	player=new CameraController(WINDOW_WIDTH,WINDOW_HEIGHT,glm::vec3(0.0f,0.0f,2.0f));
	glutKeyboardFunc(Pkeyboard);
	glutKeyboardUpFunc(PkeyboardUp);
	glutSpecialFunc(PspecialKeys);
	glutMouseFunc(PmouseClick);
	glutMotionFunc(PmouseMotion);

    glutDisplayFunc(display);
	glutIdleFunc(display);

    glutMainLoop();

	vao1->Delete();
	vbo1->Delete();
	ebo1->Delete();
	
	texture1->Delete();
	
	shaderProgram->Delete();
	
    return 0;
}