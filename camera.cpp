#include "camera.h"

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
	GLfloat velocity = this->movementSpeed * deltaTime;
	GLfloat turnVelocity = this->mouseSensitivity * deltaTime;
	//std::cout << turnVelocity << std::endl;

	if (FORWARD == direction) {
		this->position += this->front * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (BACKWARD == direction) {
		this->position -= this->front * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (RIGHT == direction) {
		this->position += this->right * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (LEFT == direction) {
		this->position -= this->right * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (UP == direction) {
		this->position += this->up * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (DOWN == direction) {
		this->position -= this->up * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (TURNR == direction) {
		std::cout << "yaw is:" << this->yaw << std::endl;
		ProcessMouseMovement(turnVelocity*1000.0f, 0);
	}
	if (TURNL == direction) {
		std::cout << "yaw is:" << this->yaw << std::endl;
		ProcessMouseMovement(-turnVelocity * 1000.0f, 0);
	}
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset) {
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	if (constrainPitch) {
		if (this->pitch > 89.0f) {
			this->pitch = 89.0f;
		}
		if (this->pitch < -89.0f) {
			this->pitch = -89.0f;
		}
	}
	this->UpdateCameraVectors();
}

void Camera::setPosition(glm::vec3 _pos){
	this->position = _pos;
}

GLfloat Camera::GetZoom() {
	return this->zoom;
}

glm::vec3 Camera::GetPosition() {
	return this->position;
}

glm::vec3 Camera::GetFront() {
	return this->front;
}

void Camera::setFront(const glm::vec3 &front) {
	Camera::front = front;
}

void Camera::setUp(const glm::vec3 &up) {
	Camera::up = up;
}

void Camera::setRight(const glm::vec3 &right) {
	Camera::right = right;
}

void Camera::setWorldUp(const glm::vec3 &worldUp) {
	Camera::worldUp = worldUp;
}

glm::vec3 Camera::GetRight() {
	return this->right;
}

GLfloat Camera::getYaw() {
	return this->yaw;
}
