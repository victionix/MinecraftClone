#ifndef VERTEX_H
#define VERTEX_H


#include <glm/glm.hpp>
#include <GL/glew.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texturePos;
	GLuint textureID;

	Vertex(float a, float b, float c, float texX, float texY, GLuint texID) { position = glm::vec3(a, b, c); texturePos = glm::vec2(texX, texY); textureID = texID; }
};





#endif