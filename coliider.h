#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

enum Collider_Type{
	BOX, SPHERE, ELLIPSE
};

class Collider{
public:
	Collider(glm::vec3 _pos, glm::vec3 _max, glm::vec3 _min, Collider_Type _type);
	void renderCollider();
	void createCollider();
	void createSphere();
	void createBox();
	void createEllipse();
	bool checkCollision(Collider* _c);
	glm::vec3 getMin();
	glm::vec3 getMax();
	Collider_Type getColliderType();
	std::vector<glm::vec3> getVertices();
	float getRadius();
	glm::vec3 getEllipse();
	glm::vec3 getPos();

private:
	float maxX, maxY, maxZ, minX, minY, minZ;
	glm::vec3 pos;
	Collider_Type currentType;
	bool shouldRender;
	float radius;
	float ellipseX, ellipseY, ellipseZ;
	std::vector<glm::vec3> vertices;

	bool boxBox(std::vector<glm::vec3> _v1, glm::vec3 _p1, glm::vec3 _min2, glm::vec3 _max2, glm::vec3 _p2);
	bool boxEllipse(glm::vec3 _min1, glm::vec3 _max1, glm::vec3 _p1, glm::vec3 _e2, glm::vec3 _p2);
	bool boxSphere(glm::vec3 _min1, glm::vec3 _max1, glm::vec3 _p1, float _r2, glm::vec3 _p2);
	bool ellipseEllipse(glm::vec3 _e1, glm::vec3 _p1, glm::vec3 _e2, glm::vec3 _p2);
	bool ellipseSphere(glm::vec3 _e1, glm::vec3 _p1, float _r2, glm::vec3 _p2);
	bool sphereSphere(float _r1, glm::vec3 _p1, float _r2, glm::vec3 _p2);
	bool pointBox(glm::vec3 _p1, glm::vec3 _min2, glm::vec3 _max2, glm::vec3 _p2);
	bool pointEllipse(glm::vec3 _p1, glm::vec3 _e2, glm::vec3 _p2);
};