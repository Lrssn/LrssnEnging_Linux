#include "window.h"

void window_resize(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, const char *title, Player *player, Controller *controller){
	m_Width = width;
	m_Height = height;
	m_Title = title;
	m_Player = player;
	m_Controller = controller;
	init();
	screenshotNr = 0;
	for (int i = 0; i < MAX_KEYS; i++) {
		m_Keys[i] = false;
	}
	for (int i = 0; i < MAX_MOUSEBUTTONS; i++) {
		m_MouseButtons[i] = false;
	}
}

Window::~Window(){
	glfwTerminate();
}

bool Window::init() {
	firstMouse = true;
	m_MouseX= m_Width / 2;
	m_MouseY = m_Height / 2;

	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

	if (!m_Window){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	//clamp cursor
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::loadSkybox() {
	GLfloat skyboxVertices[] = {
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};



	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid *)0);
	glBindVertexArray(0);

	//Load skybox

	faces.push_back("res/images/skybox/right.png");
	faces.push_back("res/images/skybox/left.png");
	faces.push_back("res/images/skybox/top.png");
	faces.push_back("res/images/skybox/bottom.png");
	faces.push_back("res/images/skybox/back.png");
	faces.push_back("res/images/skybox/front.png");
	cubeMapTexture = TextureLoading::LoadCubemap(faces);
}

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
}

void Window::update() {
	GLfloat currentFrame = (GLfloat)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	glfwPollEvents();
	m_Controller->setKeys(m_Keys);
	m_Controller->doMovement(deltaTime);
	glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
	glfwSwapBuffers(m_Window);
}

void Window::renderSkybox(Shader skyboxShader, glm::mat4 projection, glm::mat4 view){
	skyboxShader.Use();
	glDepthFunc(GL_LEQUAL);
	view = glm::mat4(glm::mat3(this->m_Player->getCamera()->GetViewMatrix())); //zero view
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glBindVertexArray(skyboxVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void window_resize(GLFWwindow *window, int width, int height){
	glViewport(0, 0, width, height);
}

bool Window::closed() const {
	return glfwWindowShouldClose(m_Window) == 1;
}


void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {

	Window* win = (Window*) glfwGetWindowUserPointer(window);

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (GLFW_KEY_P == key && GLFW_RELEASE == action) {
		win->RenderToFile();
	}
	if (GLFW_KEY_O == key && GLFW_RELEASE == action) {
		win->m_Player->getModel()->checkBounds();
	}

	if (key >= 0 && key < MAX_KEYS){
		if (action == GLFW_PRESS){
			win->m_Keys[key] = true;
		}
		else if (action == GLFW_RELEASE){
			win->m_Keys[key] = false;
		}
		win->keyIsPressed(key);
	}
	else {
		//TODO Log this
		std::cout << "KEYPRESS::ERROR::RECIEVED_KEYPRESS_OUTSIDE_SCOPE" << std::endl;
	}
}

void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mode){
	Window* win = (Window*)glfwGetWindowUserPointer(window);

	if (button >= 0 && button < MAX_MOUSEBUTTONS) {
		if (action == GLFW_PRESS) {
			win->m_MouseButtons[button] = true;
		}
		else if (action == GLFW_RELEASE) {
			win->m_MouseButtons[button] = false;
		}
		win->mouseButtonIsPressed(button);
	}
	else {
		//TODO Log this
		std::cout << "KEYPRESS::ERROR::RECIEVED_MOUSEPRESS_OUTSIDE_SCOPE" << std::endl;
	}
}

void Window::cursor_position_callback(GLFWwindow * window, double xPos, double yPos){
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	if (win->firstMouse)
	{
		win->m_MouseX = xPos;
		win->m_MouseY = yPos;
		win->firstMouse = false;
	}
	GLfloat xOffset = (GLfloat)xPos - (GLfloat)win->m_MouseX;
	GLfloat yOffset = (GLfloat)win->m_MouseY - (GLfloat)yPos;  // Reversed since y-coordinates go from bottom to left

	win->m_MouseX = xPos;
	win->m_MouseY = yPos;
	win->m_Controller->setMousePos(xPos, yPos);
}

void Window::keyIsPressed(int keyCode) {

	if (keyCode >= 0 && keyCode < MAX_KEYS) {
		//std::cout << "You pressed key: " << keyCode << std::endl;
		//for debugging only
		//std::cout << "You pressed key: " << glfwGetKeyName(keyCode, 0) <<std::endl;
	}
	else {
		//TODO put into log
		std::cout << "KEYCODE::ERROR::RECIEVED_KEYCODE_OUTSIDE_SCOPE" << std::endl;
	}
}

void Window::mouseButtonIsPressed(int button){
	if (button >= 0 && button < MAX_MOUSEBUTTONS) {
		std::cout << "You pressed mousebutton: " << button << std::endl;
	}
	else {
		//TODO log this
		std::cout << "KEYCODE::ERROR::RECIEVED_MOUSEBUTTON_OUTSIDE_SCOPE" << std::endl;
	}
}

void Window::getMousePosition(double& x, double& y) {
	x = m_MouseX;
	y = m_MouseY;
}

void Window::RenderToFile() {
	std::ostringstream sstream;
	sstream << this->screenshotNr;
	std::string number = sstream.str();
	std::string name = std::string("Screenshots/screenshot_") + number + ".tga";
	FILE *out = fopen(name.c_str(), "wb");
	char *pixel_data = new char[3 * m_Width*m_Height];
	int TGAhead[] = { 0, 2, 0, 0, 0, 0, m_Width, m_Height, 24 };

	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, m_Width, m_Height, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);

	fwrite(TGAhead, sizeof(TGAhead), 1, out);
	fwrite(pixel_data, 3 * m_Width*m_Height, 1, out);
	fclose(out);
	delete[] pixel_data;
	std::cout << "Rendered file: " << name << std::endl;
	this->screenshotNr++;
}
