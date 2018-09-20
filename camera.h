#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


enum Camera_Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	TURNR,
	TURNL
};


//TODO: make config file
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat yaw = YAW,
		GLfloat pitch = PITCH):
		front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movementSpeed(SPEED),
		mouseSensitivity(SENSITIVITY),
		zoom(ZOOM)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->UpdateCameraVectors();
	}

	Camera(GLfloat posX,
		GLfloat posY,
		GLfloat posZ,
		GLfloat upX,
		GLfloat upY,
		GLfloat upZ,
		GLfloat yaw,
		GLfloat pitch):
		front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movementSpeed(SPEED),
		mouseSensitivity(SENSITIVITY),
		zoom(ZOOM)
	{
		this->position = glm::vec3(posX, posY, posZ);
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		this->UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset);

	void ProcessMouseScroll(GLfloat xOffset, GLfloat yOffset) {
	}
	void setPosition(glm::vec3 _pos);

	GLfloat getYaw();
	GLfloat GetZoom();
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetRight();

	void setFront(const glm::vec3 &front);
	void setUp(const glm::vec3 &up);
	void setRight(const glm::vec3 &right);
	void setWorldUp(const glm::vec3 &worldUp);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat zoom;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;

	GLboolean constrainPitch = true;

	void UpdateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};
