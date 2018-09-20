#pragma once

#include <GL/glew.h>
#include <vector>
#include <SOIL/SOIL.h>

class TextureLoading
{
public:
	static GLuint LoadTexture(GLchar *path);
	static GLuint LoadCubemap(std::vector<const GLchar * > faces);

};
