#pragma once
#include "model.h"
#include "camera.h"

enum Player_Movement{
	pFORWARD,
	pBACKWARD,
	pLEFT,
	pRIGHT
};

class Player{
public:
  Player();
  ~Player();
  glm::vec3 getPos();

	void setFront(glm::vec3 _front);

	void setUp(glm::vec3 _up);
	Camera* getCamera();
	void setModel(Model* _model);
	void setRight(glm::vec3 _right);
	void setRotation(float _angle);
	void ProcessKeyboard(Player_Movement direction, GLfloat deltaTime);
	void processPlayerTransforms();
	Model* getModel();
	float getRotation();
private:
	float rotation = 0.0f;
	glm::vec3 pos = glm::vec3(0.0f, 2.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera cam = Camera(pos);
	Model* playermodel;
	float movementSpeed = 6.0;
};
