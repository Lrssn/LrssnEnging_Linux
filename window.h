#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "player.h"
#include "texture.h"
#include "shader.h"
#include "controller.h"



#define MAX_KEYS 1024
#define MAX_MOUSEBUTTONS 32

class Window
{
public:
	Window(int width, int height, const char *title, Player *player, Controller *controller);
	~Window();
	void clear() const;
	void update();
	bool closed() const;
	void loadSkybox();
	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	void renderSkybox(Shader skyboxShader, glm::mat4 projection, glm::mat4 view);
	void keyIsPressed(int keyCode);
	void mouseButtonIsPressed(int button);
	void getMousePosition(double& x, double& y);
	void RenderToFile();
private:
	friend struct GLFWwindow;
	//members
	std::vector<const GLchar *> faces;
	int m_Width, m_Height, screenshotNr;
	const char *m_Title;
	GLFWwindow *m_Window;
	Player *m_Player;
	Controller *m_Controller;
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	bool m_Closed;
	bool firstMouse;
	//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	GLuint skyboxVAO, skyboxVBO, cubeMapTexture;
	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_MOUSEBUTTONS];
	double m_MouseX, m_MouseY;
	//functions
	bool init();
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void mouse_button_callback(GLFWwindow *window, int button, int action, int mode);
	static void cursor_position_callback(GLFWwindow *window, double xPos, double yPos);

};
