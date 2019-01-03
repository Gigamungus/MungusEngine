#include "stdafx.h"
#include "Application.h"

Mungus::Application::Application() {
	GLFWwindow* window;

	glfwStartup(&window);
	glewStartup();

	std::vector<std::string> shaderDirectory = { std::filesystem::current_path().string() + "/../resources/shaders"};
	renderer = Mungus::Renderer(window, shaderDirectory);
}

Mungus::Application::~Application() {

}

void Mungus::Application::glfwStartup(GLFWwindow** win) {
	if (!glfwInit()) {
		MLOG("error initializing glfw");
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	*win = glfwCreateWindow(1200, 740, "Application", NULL, NULL);

	if (*win == NULL) {
		MLOG("error creating glfw window");
	}

	glfwMakeContextCurrent(*win);
	glfwSwapInterval(1);

	glfwSetErrorCallback([](int code, const char* message) { 
		MLOG("glfw error " << code << ": " << message);
	});
}



void Mungus::Application::glewStartup(void) {
	if (glewInit() != GLEW_OK) {
		MLOG("error initializing glew");
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback([](	GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar *message,
								const void *userParam)
							{	std::cout << message << std::endl;	},
		NULL);
	
}

void Mungus::Application::run() {
	std::cin.get();

	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//float positions[9] = {
	//	0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f
	//};

	//unsigned int buffer;
	//unsigned int vao;

	//glGenBuffers(1, &buffer);
	//glGenVertexArrays(1, &vao);

	//glBindBuffer(GL_VERTEX_ARRAY, buffer);
	//glBindVertexArray(vao);

	//glBufferData(GL_VERTEX_ARRAY, sizeof(positions), positions, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3 * sizeof(float), GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);


	//// Main loop
	//while (!glfwWindowShouldClose(window)) {
	//	glfwPollEvents();



	//	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	glDrawElements(GL_TRIANGLES, 3, GL_INT, 0);

	//	glfwSwapBuffers(window);
	//}


	//glfwDestroyWindow(window);
	//glfwTerminate();

	//return;
}

