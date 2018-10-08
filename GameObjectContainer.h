#pragma once
#include "model.h"
#include "coliider.h"

class GameObjectContainer{
public:
	GameObjectContainer();
	~GameObjectContainer();
	Model* getModel();

private:
	Model objectModel = Model((char*)("res/models/cube/cube.obj"));
	Collider collider;


};
