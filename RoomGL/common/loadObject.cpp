
#include "header.h"

//#include "loadObject.hpp"
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

inline int loadObject2(char *str, vector<GLuint> &v_vertexbuffer, vector<GLuint> &v_uvbuffer,
    vector<GLuint> &v_normalbuffer, vector<GLuint> &v_elementbuffer, glm::vec3 changePos = vec3(0,0,0)) {

    std::vector<glm::vec3> vertices_untitled;
	std::vector<glm::vec2> uvs_untitled;
	std::vector<glm::vec3> normals_untitled;
	bool res = loadOBJ(str, vertices_untitled, uvs_untitled, normals_untitled);

    // change position by vec3-changePos
	for(int i=0 ; i<vertices_untitled.size() ; i++) {
        vertices_untitled[i] += changePos;
	}


	std::vector<unsigned short> indices_untitled;
	std::vector<glm::vec3> indexed_vertices_untitled;
	std::vector<glm::vec2> indexed_uvs_untitled;
	std::vector<glm::vec3> indexed_normals_untitled;
	indexVBO(vertices_untitled, uvs_untitled, normals_untitled, indices_untitled, indexed_vertices_untitled, indexed_uvs_untitled, indexed_normals_untitled);

    GLuint vertexbuffer_untitled;
	glGenBuffers(1, &vertexbuffer_untitled);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_untitled);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices_untitled.size() * sizeof(glm::vec3), &indexed_vertices_untitled[0], GL_STATIC_DRAW);

	GLuint uvbuffer_untitled;
	glGenBuffers(1, &uvbuffer_untitled);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_untitled);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs_untitled.size() * sizeof(glm::vec2), &indexed_uvs_untitled[0], GL_STATIC_DRAW);

	GLuint normalbuffer_untitled;
	glGenBuffers(1, &normalbuffer_untitled);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_untitled);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals_untitled.size() * sizeof(glm::vec3), &indexed_normals_untitled[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer_untitled;
	glGenBuffers(1, &elementbuffer_untitled);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer_untitled);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_untitled.size() * sizeof(unsigned short), &indices_untitled[0], GL_STATIC_DRAW);

	v_vertexbuffer  .push_back(vertexbuffer_untitled);
	v_uvbuffer      .push_back(uvbuffer_untitled);
	v_normalbuffer  .push_back(normalbuffer_untitled);
	v_elementbuffer .push_back(elementbuffer_untitled);

	return indices_untitled.size();
}


