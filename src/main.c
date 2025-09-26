#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <utils.h>

#include "GFXAPI.h"
#include <renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "GAME"

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error : %s", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

static void setInceremnt(float value,float* inc, float bound) {
	if (value <= 0 || value >= bound) {
		*inc = -(*inc);
	}
}

int main(void) {
	if (!glfwInit()) {
		fprintf(stderr,"Couldn't initialize GLFW");
		return 1;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr,"Couldn't create GLFW window");
		glfwTerminate();
		return 1;
	}

	glfwSetKeyCallback(window, key_callback);
	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(glfwGetProcAddress);
	glfwSwapInterval(1);

	float vertices[] = {
		//   x      y       r     g     b
		 0.0f,  0.6f,    1.0f, 0.0f, 0.0f, // 0 top
		 0.52f, 0.3f,    0.0f, 1.0f, 0.0f, // 1 top-right
		 0.52f,-0.3f,    0.0f, 0.0f, 1.0f, // 2 bottom-right
		 0.0f, -0.6f,    1.0f, 1.0f, 0.0f, // 3 bottom
		-0.52f,-0.3f,    1.0f, 0.0f, 1.0f, // 4 bottom-left
		-0.52f, 0.3f,    0.0f, 1.0f, 1.0f  // 5 top-left
	};

	unsigned int indices[] = {
		0,1,5,
		1,2,4,
		4,5,1,
		2,3,4
	};


	VertexBuffer v_buff = VertexBufferCreate(vertices, sizeof(vertices));
	VertexBufferBind(v_buff);

	VertexArray vao = VertexArrayCreate();
	VertexArrayBind(vao);

	VertexLayout layout = VertexLayoutCreate();
	VertexLayoutPush(&layout, GFX_FLOAT, 2, false); /// POSITION DATA 0
	VertexLayoutPush(&layout, GFX_FLOAT, 3, false); /// COLOR DATA 1

	VertexArrayApplyLayout(vao, &layout);

	VertexLayoutDelete(&layout);
	
	IndexBuffer i_buff= IndexBufferCreate(indices, sizeof(indices) / sizeof(int));
	IndexBufferBind(i_buff);

	Shader shader_program = ShaderCreate(RESOURCES_PATH "shaders/vertex.glsl", RESOURCES_PATH "shaders/fragment.glsl");
	ShaderUse(shader_program);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		GLCALL(glViewport(0, 0, width, height));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		IndexBufferBind(i_buff);
		GLCALL(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, NULL));
		
		glfwSwapBuffers(window);
	}

	VertexBufferDestroy(v_buff);
	IndexBufferDestroy(i_buff);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}