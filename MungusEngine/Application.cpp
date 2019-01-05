#include "stdafx.h"
#include "Application.h"

void Mungus::Application::startup(void) {
	MLOG("client didn't override Mungus' startup method");
}

void Mungus::Application::run(void) {
	float clear_color[] = { 0.45f, 0.55f, 0.60f, 1.00f };

	float positions[12] = {
		-1.0f, -0.5f, 1.2f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int buffer;
	unsigned int vao;

	glGenBuffers(1, &buffer);
	glGenVertexArrays(1, &vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBindVertexArray(vao);

	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Main loop
	while (!glfwWindowShouldClose(renderer->getWindow())) {
		glfwPollEvents();


		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(renderer->getWindow());
	}


	glfwDestroyWindow(renderer->getWindow());
	glfwTerminate();

	return;
}

