#include "stdafx.h"
#include "Application.h"

void Mungus::Application::run() {

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

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBindVertexArray(vao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Main loop
	while (!glfwWindowShouldClose(renderer.getWindow())) {
		glfwPollEvents();


		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(renderer.getWindow());
	}


	glfwDestroyWindow(renderer.getWindow());
	glfwTerminate();

	return;
}

