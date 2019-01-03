#include "Application.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"

Mungus::Application::Application() {

}

Mungus::Application::~Application() {

}

void Mungus::Application::run() {
	glfwSetErrorCallback([](int error, const char* description) {fprintf(stderr, "Glfw Error %d: %s\n", error, description); });

	if (!glfwInit()) {
		std::cout << "glfw initialization error\n";
		return;
	}

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
	if (window == NULL) {
		std::cout << "error making window\n";
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "error initializing glew\n";
		return;
	}

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	float positions[9] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	unsigned int buffer;
	unsigned int vao;

	glGenBuffers(1, &buffer);
	glGenVertexArrays(1, &vao);

	glBindBuffer(GL_VERTEX_ARRAY, buffer);
	glBindVertexArray(vao);

	glBufferData(GL_VERTEX_ARRAY, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3 * sizeof(float), GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	// Main loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();



		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 3, GL_INT, 0);

		glfwSwapBuffers(window);
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	return;
}

