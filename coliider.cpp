#include "collider.h"
#include "coliider.h"


Collider::Collider(glm::vec3 _pos, glm::vec3 _max, glm::vec3 _min, Collider_Type _type) {
	this->maxX = _max.x + 0.5f;
	this->maxY = _max.y + 0.5f;
	this->maxZ = _max.z + 0.5f;
	this->minX = _min.x - 0.5f;
	this->minY = _min.y - 0.5f;
	this->minZ = _min.z - 0.5f;
	this->pos = _pos;

	this->currentType = _type;
	createCollider();
}

void Collider::renderCollider() {

}

void Collider::createCollider() {
	switch(this->currentType){
		case BOX:
			createBox();
			break;
		case SPHERE:
			createSphere();
			break;
		case ELLIPSE:

			break;
	}
}

void Collider::createSphere() {
	radius = max(abs(minX), max(abs(maxX), max(abs(minY), max(abs(maxY), max(abs(minZ), abs(maxZ))))));
}

void Collider::createBox() {
	//top4
	this->vertices.push_back(glm::vec3(minX, maxY, maxZ));
	this->vertices.push_back(glm::vec3(maxX, maxY, maxZ));
	this->vertices.push_back(glm::vec3(minX, maxY, minZ));
	this->vertices.push_back(glm::vec3(maxX, maxY, minZ));
	//bottom 4
	this->vertices.push_back(glm::vec3(minX, minY, maxZ));
	this->vertices.push_back(glm::vec3(maxX, minY, maxZ));
	this->vertices.push_back(glm::vec3(minX, minY, minZ));
	this->vertices.push_back(glm::vec3(maxX, minY, minZ));
}

void Collider::createEllipse() {
	ellipseX = max(abs(minX), abs(maxX));
	ellipseY = max(abs(minY), abs(maxY));
	ellipseZ = max(abs(minZ), abs(maxZ));
}

bool Collider::checkCollision(Collider *_c) {
	if(this->currentType == BOX){
		if(_c->getColliderType() == BOX){
			return boxBox(this->vertices, this->pos, _c->getMin(), _c->getMax(), _c->getPos());
		}else if(_c->getColliderType() == ELLIPSE){
			return boxBox(this->getMin(), this->getMax(), this->pos, _c->getEllipse(), _c->getPos());
		}else if(_c->getColliderType() == SPHERE){
			return boxBox(this->getMin(), this->getMax(), this->pos, _c->getRadius(), _c->getPos());
		}

	}else if(this->currentType == ELLIPSE){
		if(_c->getColliderType() == BOX){
			return boxBox(this->getEllipse(), this->pos, _c->getVertices(), _c->getPos());
		}else if(_c->getColliderType() == ELLIPSE){
			return boxBox(this->getEllipse(), this->pos, _c->getEllipse(), _c->getPos());
		}else if(_c->getColliderType() == SPHERE){
			return boxBox(this->getEllipse(), this->pos, _c->getRadius(), _c->getPos());
		}

	}else if(this->currentType == SPHERE){
		if(_c->getColliderType() == BOX){
			return boxBox(this->radius, this->pos, _c->getVertices(), _c->getPos());
		}else if(_c->getColliderType() == ELLIPSE){
			return boxBox(this->radius, this->pos, _c->getEllipse(), _c->getPos());
		}else if(_c->getColliderType() == SPHERE){
			return boxBox(this->radius, this->pos, _c->getRadius(), _c->getPos());
		}
	}
	return false;
}

Collider_Type Collider::getColliderType() {
	return currentType;
}

std::vector<glm::vec3> Collider::getVertices() {
	return this->vertices;
}
float Collider::getRadius() {
	return this->radius;
}

glm::vec3 Collider::getEllipse() {
	return glm::vec3(this->ellipseX, this->ellipseY, this->ellipseZ);
}

Collider::boxBox(std::vector<glm::vec3> _v1, glm::vec3 _p1, glm::vec3 _min2, glm::vec3 _max2, glm::vec3 _p2) {
	for(int i = 0; i < _v1.size(); i++){
		if (pointBox(_v1.at(i), _min2, _max2, _p2)){
			return true;
		}
	}
	return false;
}
bool Collider::pointEllipse(glm::vec3 _p1, glm::vec3 _e2, glm::vec3 _p2) {
	return false;
}

bool Collider::boxEllipse(glm::vec3 _min1, glm::vec3 _max1, glm::vec3 _p1, glm::vec3 _e2, glm::vec3 _p2) {
	return false;
}

bool Collider::boxSphere(glm::vec3 _min1, glm::vec3 _max1, glm::vec3 _p1, float _r2, glm::vec3 _p2) {
	return false;
}

bool Collider::ellipseEllipse(glm::vec3 _e1, glm::vec3 _p1, glm::vec3 _e2, glm::vec3 _p2) {

}

bool Collider::ellipseSphere(glm::vec3 _e1, glm::vec3 _p1, float _r2, glm::vec3 _p2) {

}

bool Collider::sphereSphere(float _r1, glm::vec3 _p1, float _r2, glm::vec3 _p2) {
	if(sqrt(pow(_p1.x-_p2.x, 2)+pow(_p1.y-_p2.y, 2)+pow(_p1.z-_p2.z, 2)) <= r1+r2){
		return true;
	}else{
		return false;
	}
}

bool Collider::pointBox(glm::vec3 _p1, glm::vec3 _min2, glm::vec3 _max2, glm::vec3 _p2) {
	if(_p2.x - _min2.x <= _p1.x && _p1.x <= _p2.x + _max2.x){
		if(_p2.y - _min2.y <= _p1yx && _p1.y <= _p2.y + _max2.y){
			if(_p2.z - _min2.z <= _p1.z && _p1.z <= _p2.z + _max2.z){
				return true;
			}else{
				returb false;
			}
		}else{
			return false;
		}
	}else{
		return false;
	}
}

glm::vec3 Collider::getMin() {
	return glm::vec3(this->minX, this->minY, this->minZ);
}

glm::vec3 Collider::getMax() {
	return glm::vec3(this->maxX, this->maxZ, this->maxZ);
}
