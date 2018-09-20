#include "player.h"

Player::Player(){

}

Player::~Player(){
}

glm::vec3 Player::getPos(){
    return this->pos;
}

void Player::ProcessKeyboard(Player_Movement direction, GLfloat deltaTime) {
	GLfloat velocity = this->movementSpeed * deltaTime;

	if (pFORWARD == direction) {
		this->pos += this->front * velocity;
		//std::cout << "xpos is:" << this->pos.x << "   ypos is:" << this->pos.y << "   zpos is:" << this->pos.z << std::endl;
	}
	if (pBACKWARD == direction) {
		this->pos -= this->front * velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (pRIGHT == direction) {
		this->pos += this->right*velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}
	if (pLEFT == direction) {
		this->pos -= this->right*velocity;
		//std::cout << "xpos is:" << this->position.x << "   ypos is:" << this->position.y << "   zpos is:" << this->position.z << std::endl;
	}

}

void Player::setFront(glm::vec3 _front) {
	this->front = _front;
	this->front.y = 0.0f;
}

void Player::setUp(glm::vec3 _up) {
	this->up = _up;
}

void Player::setRight(glm::vec3 _right) {
	this->right = _right;
}
void Player::setRotation(float _angle) {
	this->rotation = _angle / 60.0f;
}
float Player::getRotation() {
	return this->rotation;
}