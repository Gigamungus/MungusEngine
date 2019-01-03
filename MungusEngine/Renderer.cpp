#include "Renderer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"



const unsigned int Mungus::Renderer::compileShader(const std::string shaderSource, const unsigned int type) {
	unsigned int shader = glCreateShader(type);
	const char* shaderSourceString = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourceString, NULL);
	glCompileShader(shader);

	int compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {
		int log_length = 0;
		char message[1024];
		glGetShaderInfoLog(shader, 1024, &log_length, message);
		std::cout << "failed to compile shader " << "\n" << message << "\n";
	}

	return shader;
}

const std::string Mungus::Renderer::shaderSourceFromUrl(const std::string url) const {
	std::ifstream file(url);
	std::string line;
	std::stringstream source;

	if (!file.is_open()) {
		MLOG("error opening file " + url);
	}

	while (getline(file, line)) {
		source << line;
	}

	return source.str();
}
