
#include "header.h"

//#include "loadObject.hpp"
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

inline int loadObject(char *str, vector<GLuint> &v_vertexbuffer, vector<GLuint> &v_uvbuffer,
    vector<GLuint> &v_normalbuffer, vector<GLuint> &v_elementbuffer, glm::vec3 changePos = vec3(0,0,0)) {

    std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ(str, vertices, uvs, normals);

    // change position by vec3-changePos
	for(int i=0 ; i<vertices.size() ; i++) {
        vertices[i] += changePos;
	}


	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

    GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	v_vertexbuffer  .push_back(vertexbuffer);
	v_uvbuffer      .push_back(uvbuffer);
	v_normalbuffer  .push_back(normalbuffer);
	v_elementbuffer .push_back(elementbuffer);

	return indices.size();
}


