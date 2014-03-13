#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>
class Shaders{
private:
	GLuint compileShaders(const char * vertex_file_path,const char * fragment_file_path);
	int checkSum(std::string);
public:
	//vertexShader
	std::vector <const char*> vertexShaders;
	std::vector <int> vertexShadersSum;

	//fragmentShader
	std::vector <const char*> fragmentShaders;
	std::vector <int> fragmentShadersSum;

	std::vector <GLuint*> pids;
	void loadShaders(GLuint *pid, const char * vertex_file_path,const char * fragment_file_path);
	void reloadShaders();
	bool detectChange();
};

#endif
