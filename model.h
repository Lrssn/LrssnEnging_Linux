#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"


class Model {
public:
	Model(GLchar *path, glm::vec3 pos, float ang, glm::vec3 rot, glm::vec3 scl);
	Model(GLchar *path, glm::vec3 pos, glm::vec3 scl);
	Model(GLchar *path, glm::vec3 pos);
	Model(GLchar *path);

	void Draw(Shader shader);
	void Render(Shader shader, glm::mat4 view, glm::mat4 projection);
	void setPosition(glm::vec3 pos);
	void initPosition(glm::vec3 pos);
	void setRotation(float ang, glm::vec3 rot);
	void initRotation(float ang, glm::vec3 rot);
	void initScale(glm::vec3 scl);
	void setScale(glm::vec3 scl);
	void setVisible();
	void checkBounds();
	glm::vec3 getCenter();
	void Collision(std::vector<Model>* _m);
	bool inCollider(int _i);

private:
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	glm::mat4 modelMatrix;
	glm::vec3 position, rotation, scale, centerPoint;
	float rotAngle;
	bool isVisible;
	std::vector<int> hasCollided;

	void updatePosition();
	void updateRotation();
	void updateScale();
	float maxX = -100000, maxY = -100000, maxZ = -100000, minX = 100000, minY = 100000, minZ = 100000;
	void loadModel(std::string path);
	void calculateBoundingBox(glm::vec3 _v);
	void processNode(aiNode *node, const aiScene *scene);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	GLint TextureFromFile(const char *path, std::string directory);
};

//GLint TextureFromFile(const char *path, string directory);
