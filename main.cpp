#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "model.h"
#include "terrainCreator.h"
#include "player.h"
#include "controller.h"

int main(int argc, char** argv) {
	int width = 800, height = 600;
	//Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));

	Player player1 = Player();
	Controller controller(&player1, FPS);
	Window window(width, height, "Lrssn!", &player1, &controller);
	double lastFrame = 0.0f, deltaTime = 0.0f, x, y;
	//print windowsize
	std::cout << "The window is " << window.getWidth() << "x" << window.getHeight() << std::endl;
	//print mouseposition
	window.getMousePosition(x, y);
	std::cout << "Mouseposition is: " << x << "," << y << std::endl;

	// Setup and compile our shaders
	Shader modelShader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");
	Shader skyboxShader("res/shaders/skybox.vs", "res/shaders/skybox.frag");

	//TODO: make iterative

	//create terrain
	// 0 = testscene with just a floor
	// 1 = testscene with floor and walls
	TerrainCreator tC(1);
	//Model playerModel("res/models/nano/nanosuit.obj");
	Model playerModel((char*)("res/models/cube/cube.obj"));
	player1.setModel(&playerModel);
	//load models
	std::vector<Model> terrain;

	//add terrain to renderer
	terrain = tC.getObjects();

	//load skybox
	window.loadSkybox();

	// Draw in wireframe
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//turn on backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//create projection matrix
	glm::mat4 projection = glm::perspective(player1.getCamera()->GetZoom(), (float)width / (float)height, 0.1f, 1000.0f);
	//GAME LOOP
	while (!window.closed()) {
		//update deltatime
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//calculate collision
		player1.getModel()->Collision(&terrain);

		//clear window
		window.clear();
		glEnable(GL_DEPTH_TEST);					//enable depth testing
		glm::mat4 view = player1.getCamera()->GetViewMatrix();	//create viewmatrix

		//render skybox
		window.renderSkybox(skyboxShader, projection, view);

		view = player1.getCamera()->GetViewMatrix(); //unzero the viewmatrix
		//Draw models
		for(int i  = 0; i < terrain.size();i++){
			terrain.at(i).Render(modelShader, view, projection);
		}
		player1.getModel()->Render(modelShader, view, projection);
		window.update();
	}
	return 0;
}
