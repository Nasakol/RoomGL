
#ifdef __APPLE__
    #include "GL/glew.h"
    #include "GL/glfw.h"
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>

#else
#ifdef _WIN32
    #include <windows.h>
    //#define GLEW_BUILD
    #define GLEW_STATIC
    #include <GL/glew.h>
    #include <GL/glfw.h>
    #include <GL/glut.h>
#endif
#endif

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;


extern int global_x;

void print_global_x();

