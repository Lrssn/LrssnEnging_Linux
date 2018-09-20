#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "player.h"

enum Game_Type{
	FPS, RTS, TPS
};

#define MAX_KEYS 1024
#define MAX_MOUSEBUTTONS 32

class Controller{
public:
    Controller(Camera *_camera, Player *_player, Game_Type _gt);
    void setKeys(bool _keys[MAX_KEYS]);
    void doMovement(GLfloat deltaTime);
    void changeGameType(Game_Type _gt);
    void setMousePos(float _x, float _y);
private:
	void processMouse(float _x, float _y);
    Camera *camera;
    Player *player;
    float mouseX, mouseY;
	Game_Type currentGT;
    bool keys[MAX_KEYS];
	GLfloat xOffset, yOffset;
	bool mouseButtons[MAX_MOUSEBUTTONS];
};