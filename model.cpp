#include "model.h"
/*
Model::Model(GLchar *path = nullptr, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float ang = 0.0f, glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scl = glm::vec3(1.0f, 1.0f, 1.0f),
							std::vector<Mesh> _m = nullptr, std::vector<Texture> _t = nullptr) {
	this->loadModel(path);
	initPosition(pos);
	initRotation(ang, rot);
	initScale(scl);
	isVisible = true;
	this->meshes = _m;
	this->textures_loaded = _t;
}
*/
//pos, rot, scl
Model::Model(GLchar *path, glm::vec3 pos, float ang, glm::vec3 rot, glm::vec3 scl) {
	this->loadModel(path);
	initPosition(pos);
	initRotation(ang, rot);
	initScale(scl);
	isVisible = true;
}
//pos, scl
Model::Model(GLchar * path, glm::vec3 pos, glm::vec3 scl)
{
	this->loadModel(path);
	initPosition(pos);
	initRotation(0, glm::vec3(1.0f, 1.0f, 1.0f));
	initScale(scl);
	isVisible = true;
}
//pos
Model::Model(GLchar * path, glm::vec3 pos)
{
	this->loadModel(path);
	initPosition(pos);
	initRotation(0, glm::vec3(1.0f, 1.0f, 1.0f));
	initScale(glm::vec3(1.0f, 1.0f, 1.0f));
	isVisible = true;
}

Model::Model(GLchar * path)
{
	this->loadModel(path);
	initPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	initRotation(0, glm::vec3(1.0f, 1.0f, 1.0f));
	initScale(glm::vec3(1.0f, 1.0f, 1.0f));
	isVisible = true;
}

void Model::Draw(Shader shader) {
	for (GLuint i = 0; i < this->meshes.size(); i++) {
		this->meshes[i].Draw(shader);
	}
}

void Model::Render(Shader shader, glm::mat4 view, glm::mat4 projection)
{
	if (isVisible) {
		shader.Use();
		this->modelMatrix = glm::mat4(1.0f);

		//this->modelMatrix[1] = glm::vec4(0, 1, 0, 0);
		//this->modelMatrix[2] = glm::vec4(0, 0, 1, 0);
		//this->modelMatrix[3] = glm::vec4(0, 0, 0, 1);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		// Draw the loaded model
		updatePosition();
		updateRotation();
		updateScale();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
		this->Draw(shader);
		//std::cout << "isvisible=" << this->isVisible << std::endl;
	}
}

void Model::initPosition(glm::vec3 pos)
{
	this->position = pos;
}

void Model::initRotation(float ang, glm::vec3 rot)
{
	this->rotAngle = ang;
	this->rotation =  rot;
}

void Model::initScale(glm::vec3 scl)
{
	this->scale = scl;
}

void Model::setPosition(glm::vec3 pos){
	this->position = pos;
	this->centerPoint.x = pos.x + (maxX-minX);
	this->centerPoint.y = pos.y + (maxY-minY);
	this->centerPoint.z = pos.z + (maxZ-minZ);
}

void Model::setRotation(float ang,glm::vec3 rot){
	this->rotAngle = ang;
	this->rotation = rot;
}

void Model::setScale(glm::vec3 scl){
	this->scale = scl;
}

void Model::updatePosition(){
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

void Model::updateRotation(){
	this->modelMatrix = glm::rotate(modelMatrix, rotAngle, rotation);
}

void Model::updateScale() {
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
}

void Model::checkBounds(){
	std::cout << "X-bounds are " << minX << ", " << maxX << std::endl;
	std::cout << "Y-bounds are " << minY << ", " << maxY << std::endl;
	std::cout << "Z-bounds are " << minZ << ", " << maxZ << std::endl;
}

void Model::setVisible(){
	this->isVisible = !this->isVisible;
}

GLint Model::TextureFromFile(const char *path, std::string directory) {
	std::string filename = std::string(path);
	filename = directory + "/" + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;

	unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(image);

	return textureID;
}

void Model::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;

		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
	this->centerPoint.x = maxX-minX;
	this->centerPoint.y = maxY-minY;
	this->centerPoint.z = maxZ-minZ;
}

void Model::processNode(aiNode *node, const aiScene *scene) {
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		calculateBoundingBox(vector);
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		GLboolean skip = false;

		for (GLuint j = 0; j < textures_loaded.size(); j++) {
			if (textures_loaded[j].path == str) {
				textures.push_back(textures_loaded[j]);
				skip = true;

				break;
			}
		}
		if (!skip) {
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);

			this->textures_loaded.push_back(texture);
		}
	}
	return textures;
}

void Model::Collision(std::vector<Model>* _m){
	for(int i = 0; i < _m->size(); i++) {
		if ((sqrt(pow(abs(this->centerPoint.x - _m->at(i).getCenter().x), 2) +
				  pow(abs(this->centerPoint.y - _m->at(i).getCenter().y), 2) +
				  pow(abs(this->centerPoint.z - _m->at(i).getCenter().z), 2)) < 2) && !inCollider(i)) {
			std::cout << "Collision Detected with object " << i << std::endl;
			hasCollided.push_back(i);
		} else if (!(sqrt(pow(abs(this->centerPoint.x - _m->at(i).getCenter().x), 2) +
						  pow(abs(this->centerPoint.y - _m->at(i).getCenter().y), 2) +
						  pow(abs(this->centerPoint.z - _m->at(i).getCenter().z), 2)) < 2) && inCollider(i)) {
			std::cout << "stopped colliding with object " << i << std::endl;
			for(int j = 0; j < hasCollided.size(); j++){
				if(hasCollided.at(j) == i){
					hasCollided.erase(hasCollided.begin()+j);
				}
			}
		}
	}
}
bool Model::inCollider(int _i){
	return std::find(hasCollided.begin(), hasCollided.end(), _i) != hasCollided.end();
}
void Model::calculateBoundingBox(glm::vec3 _v){
	if(_v.x > this->maxX){
		this->maxX = _v.x;
	}
	if(_v.x < this->minX){
		this->minX = _v.x;
	}
	if(_v.y > this->maxY){
		this->maxY = _v.y;
	}
	if(_v.y < this->minY){
		this->minY = _v.y;
	}
	if(_v.z > this->maxZ){
		this->maxZ = _v.z;
	}
	if(_v.x < this->minZ){
		this->minZ = _v.z;
	}
}

glm::vec3 Model::getCenter(){
	return this->centerPoint;
}