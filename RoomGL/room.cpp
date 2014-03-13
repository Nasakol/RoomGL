
#include "header.h"

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

#include "common/loadObject.cpp"
// it needs to be defined somewhere

vector<GLuint> v_vertexbuffer;
vector<GLuint> v_uvbuffer;
vector<GLuint> v_normalbuffer;
vector<GLuint> v_elementbuffer;
vector<GLuint> v_texture;
vector<int> v_indice_size;

GLuint Texture;
void sphere_map();

int main(int argc, char **argv)
{
// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	printf("GLEW version: %s\n", glewGetString(GLEW_VERSION));

	glfwSetWindowTitle( "Room" );

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );
	glfwSetMousePos(1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint depthProgramID = LoadShaders( "DepthRTT.vertexshader", "DepthRTT.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");


	// Load the texture

//	 Texture = loadDDS("uvmap.DDS");


    // -----------------------------------------------------
    // Start adding object
    // Read .obj file and load Texture by TGA file
    // -----------------------------------------------------

//	int width, height;
//	v_texture.push_back(png_texture_load("untitled.png", &width, &height));
    int temp_indice_size = 0;

    
//	v_texture.push_back(loadTGA_glfw("textures/uvmap.tga"));
//    temp_indice_size = loadObject("room_thickwalls.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer);
//    v_indice_size.push_back(temp_indice_size);
//
//	v_texture.push_back(loadTGA_glfw("textures/untitled.tga"));
//    temp_indice_size = loadObject("untitled2.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(7,0,0));
//    v_indice_size.push_back(temp_indice_size);
//
//	v_texture.push_back(loadTGA_glfw("textures/untitled.tga"));
//    temp_indice_size = loadObject("untitled.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(-2,0,0));
//    v_indice_size.push_back(temp_indice_size);
//
//	v_texture.push_back(loadTGA_glfw("textures/Light.tga"));
//    temp_indice_size = loadObject("Light.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(1,1.5,-2));
//    v_indice_size.push_back(temp_indice_size);
//
//	v_texture.push_back(loadTGA_glfw("textures/lamp.tga"));
//    temp_indice_size = loadObject("lamp.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(4, 2, 0));
//    v_indice_size.push_back(temp_indice_size);
//
//	v_texture.push_back(loadTGA_glfw("textures/wall.tga"));
//    temp_indice_size = loadObject("wall.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(-2,0,0));
//    v_indice_size.push_back(temp_indice_size);
//
//	v_texture.push_back(loadTGA_glfw("textures/monkey.tga"));
//    temp_indice_size = loadObject("monkey.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(2.5,1,0));
//    v_indice_size.push_back(temp_indice_size);
    
//    v_texture.push_back(loadTGA_glfw("textures/house.tga"));
//    temp_indice_size = loadObject("houseAfterJoin.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer);
//    v_indice_size.push_back(temp_indice_size);
    
    v_texture.push_back(loadTGA_glfw("UVRoom/LV_sofa.tga"));
    temp_indice_size = loadObject("UVobj/LV_sofa.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(2.5,1,0));
    v_indice_size.push_back(temp_indice_size);

    v_texture.push_back(loadTGA_glfw("UVRoom/LV_sofaTable.tga"));
    temp_indice_size = loadObject("UVobj/LV_sofaTable.obj", v_vertexbuffer, v_uvbuffer, v_normalbuffer, v_elementbuffer, vec3(2.5,1,0));
    v_indice_size.push_back(temp_indice_size);


    // -----------------------------------------------------
    // End adding object
    // -----------------------------------------------------




//    glutDisplayFunc(sphere_map);


	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;


	// The quad's FBO. Used only for visualizing the shadowmap.
	GLuint quad_VertexArrayID;
	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint quad_programID = LoadShaders( "Passthrough.vertexshader", "SimpleTexture.fragmentshader" );
	GLuint texID = glGetUniformLocation(quad_programID, "texture");


	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "ShadowMapping.vertexshader", "ShadowMapping.fragmentshader" );

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	GLuint DepthBiasID = glGetUniformLocation(programID, "DepthBiasMVP");
	GLuint ShadowMapID = glGetUniformLocation(programID, "shadowMap");

	// Get a handle for our "LightPosition" uniform
	GLuint lightInvDirID = glGetUniformLocation(programID, "LightInvDirection_worldspace");


    int cnt = 0;
    float x = -1, delta = 0.01;

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	do{
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

        // change position of light source
        if(cnt == 1) {
            cnt = 0;
            x += delta;
            if(x < -1 || x >= 2) delta *= -1;
        }cnt++;

		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0,0,1024,1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		// We don't use bias in the shader, but instead we draw back faces,
		// which are already separated from the front faces by a small distance
		// (if your geometry is made this way)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(depthProgramID);

        // light source
		glm::vec3 lightInvDir = glm::vec3(x,2,2);

		// Compute the MVP matrix from the light's point of view
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
		// or, for spot light :
		// glm::vec3 lightPos(5, 20, 20);
		// glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
		// glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos-lightInvDir, glm::vec3(0,1,0));

		glm::mat4 depthModelMatrix = glm::mat4(1.0);
		glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform in glsl DepthRTT
		glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

    // map shader into floor
    for(int i=0 ; i<4 ; i++) {
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, v_vertexbuffer[i]);
		glVertexAttribPointer(
			0,  // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);


		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v_elementbuffer[i]);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			v_indice_size[i],    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
    }


		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		//ViewMatrix = glm::lookAt(glm::vec3(14,6,4), glm::vec3(0,1,0), glm::vec3(0,1,0));
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);

		glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);

        // specify position of light source
		glUniform3f(lightInvDirID, lightInvDir.x, lightInvDir.y, lightInvDir.z);


//		// Bind our texture in Texture Unit 0
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, Texture);
//		// Set our "myTextureSampler" sampler to user Texture Unit 0
//		glUniform1i(TextureID, 0);


		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glUniform1i(ShadowMapID, 1);


        // 1rst attribute buffer : vertices
        for(int i=0 ; i<v_indice_size.size() ; i++) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, v_texture[i]);
            glUniform1i(TextureID, 0);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, v_vertexbuffer[i]);
            glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );

            // 2nd attribute buffer : UVs
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, v_uvbuffer[i]);
            glVertexAttribPointer(
                1,                                // attribute
                2,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
            );

            // 3rd attribute buffer : normals
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, v_normalbuffer[i]);
            glVertexAttribPointer(
                2,                                // attribute
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
            );

            // Index buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v_elementbuffer[i]);

            // Draw the triangles !
            glDrawElements(
                GL_TRIANGLES,      // mode
                v_indice_size[i],
                //indices.size(),    // count
                GL_UNSIGNED_SHORT, // type
                (void*)0           // element array buffer offset
            );

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
        }


		// Optionally render the shadowmap (for debug only)

		// Render only on a corner of the window (or we we won't see the real rendering...)
		glViewport(0,0,512,512);

		// Use our shader
		glUseProgram(quad_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		// Set our "renderedTexture" sampler to user Texture Unit 0
		glUniform1i(texID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		// You have to disable GL_COMPARE_R_TO_TEXTURE above in order to see anything !
		//glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles
		glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Cleanup VBO and shader
//	glDeleteBuffers(1, &vertexbuffer);
//	glDeleteBuffers(1, &uvbuffer);
//	glDeleteBuffers(1, &normalbuffer);
//	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteProgram(depthProgramID);
	glDeleteProgram(quad_programID);
//	glDeleteTextures(1, &Texture);

	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &depthTexture);
	glDeleteBuffers(1, &quad_vertexbuffer);
	glDeleteVertexArrays(1, &quad_VertexArrayID);


	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

void sphere_map() {
    //Texture use for automatic coordinate generation
    glBindTexture(GL_TEXTURE_2D, Texture);
    glEnable(GL_TEXTURE_2D);

    //Sphere mapping and enable s & t texture generation
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    //Draw the shapes to apply the texture
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //blend texture with lighting
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glLoadIdentity();
   gluLookAt ( 0, 0, 0, 5, 0, 0, 0, 0, 1 );	//put camera at center of origin
   glScalef ( 1, -1, 1 );			//flip left-right
//   rotate();
//   drawScene();

   //Use current framebuffer image as texture
   glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 500, 500, 0);

   //clear frame buffer to draw sphere with scene
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   //put camera back at the observational point
   gluLookAt ( 5, 0, 0, 0, 0, 0, 0, 0, 1 );
//   rotate();
//   drawScene();
   glutSolidSphere( 1.0, 20, 20 );	// draw a sphere with this sphere map
   glFlush();


    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
}
