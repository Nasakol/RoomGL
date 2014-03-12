#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>
using namespace std;
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Load a .TGA file using GLFW's own loader
GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

GLuint png_texture_load(const char * file_name, int * width, int * height);

#endif
