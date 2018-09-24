#include "controller.h"
Controller::Controller(Player *_player, Game_Type _gt) {
    this->player = _player;
	this->camera = player ->getCamera();
    this->currentGT = _gt;
}

void Controller::doMovement(GLfloat deltaTime) {
    switch(currentGT) {
		case RTS:
			// Camera controls
			if (this->keys[GLFW_KEY_W] || this->keys[GLFW_KEY_UP]) {
				this->camera->ProcessKeyboard(FORWARD, deltaTime);
			}

			if (this->keys[GLFW_KEY_S] || this->keys[GLFW_KEY_DOWN]) {
				this->camera->ProcessKeyboard(BACKWARD, deltaTime);
			}

			if (this->keys[GLFW_KEY_A] || this->keys[GLFW_KEY_LEFT]) {
				this->camera->ProcessKeyboard(LEFT, deltaTime);
			}

			if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT]) {
				this->camera->ProcessKeyboard(RIGHT, deltaTime);
			}
			if (this->keys[GLFW_KEY_R]) {
				this->camera->ProcessKeyboard(UP, deltaTime);
			}
			if (this->keys[GLFW_KEY_F]) {
				this->camera->ProcessKeyboard(DOWN, deltaTime);
			}
			if (this->keys[GLFW_KEY_E]) {
				this->camera->ProcessKeyboard(TURNR, deltaTime);
			}
			if (this->keys[GLFW_KEY_Q]) {
				this->camera->ProcessKeyboard(TURNL, deltaTime);
			}
			//player

			if (this->keys[GLFW_KEY_I]) {
				this->player->ProcessKeyboard(pFORWARD, deltaTime);
			}
			if (this->keys[GLFW_KEY_K]) {
				this->player->ProcessKeyboard(pBACKWARD, deltaTime);
			}
			if (this->keys[GLFW_KEY_J]) {
				this->player->ProcessKeyboard(pLEFT, deltaTime);
			}
			if (this->keys[GLFW_KEY_L]) {
				this->player->ProcessKeyboard(pRIGHT, deltaTime);
			}
			this->camera->ProcessMouseMovement(this->xOffset, this->yOffset);
			this->xOffset = 0.0f;
			this->yOffset = 0.0f;
			break;
    	case FPS:
    		this->camera->setPosition(glm::vec3(player->getPos().x+3.0f,player->getPos().y+5.0f, player->getPos().z ));
    		this->player->setFront(this->camera->GetFront());
    		this->player->setRight(this->camera->GetRight());
			if (this->keys[GLFW_KEY_W]) {
				this->player->ProcessKeyboard(pFORWARD, deltaTime);
			}
			if (this->keys[GLFW_KEY_S]) {
				this->player->ProcessKeyboard(pBACKWARD, deltaTime);
			}
			if (this->keys[GLFW_KEY_A]) {
				this->player->ProcessKeyboard(pLEFT, deltaTime);
			}
			if (this->keys[GLFW_KEY_D]) {
				this->player->ProcessKeyboard(pRIGHT, deltaTime);
			}
			this->player->setRotation(this->camera->getYaw());
			break;
	}
}

void Controller::changeGameType(Game_Type _gt) {
	currentGT = _gt;
}
void Controller::setKeys(bool _keys[1024]) {
    for(int i = 0; i < 1024; i++){
        keys[i] = _keys[i];
    }
}

void Controller::setMousePos(float _x, float _y) {
	processMouse(_x, _y);
	this->mouseX = _x;
	this->mouseY = _y;
}
void Controller::processMouse(float _x, float _y){
	xOffset = (GLfloat)_x - (GLfloat)this->mouseX;
	yOffset = (GLfloat)this->mouseY - (GLfloat)_y;  // Reversed since y-coordinates go from bottom to left
	this->camera->ProcessMouseMovement(this->xOffset, this->yOffset);
	this->xOffset = 0.0f;
	this->yOffset = 0.0f;
}