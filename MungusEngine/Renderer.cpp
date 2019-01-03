#include "stdafx.h"
#include "Renderer.h"

Mungus::Renderer::Renderer(GLFWwindow * window, std::vector<std::string> urls) : window(window) {

	while (urls.size() > 0) {
		std::string url = urls.back();
		urls.pop_back();

		if (std::filesystem::is_directory(url)) {
			for (auto subFile : std::filesystem::directory_iterator(url)) {
				urls.push_back(subFile.path().string());
			}
		}
		else {
			if (url.find(".vertexshader") != std::string::npos) {
				if (vertexShaders.find(url) != vertexShaders.end()) {
					MLOG("trying to recompile shader: " + url);
				}
				else {
					vertexShaders.insert(std::make_pair(url, compileShader(url, GL_VERTEX_SHADER)));
				}
			}
			else if (url.find(".fragmentshader") != std::string::npos) {
				if (fragmentShaders.find(url) != fragmentShaders.end()) {
					MLOG("trying to recompile shader: " + url);
				}
				else {
					vertexShaders.insert(std::make_pair(url, compileShader(url, GL_FRAGMENT_SHADER)));
				}
			}
			else {
				MLOG("trying to add unsupported shader type: " + url);
			}
		}
	}
}

Mungus::Renderer::~Renderer() {

}

const unsigned int Mungus::Renderer::compileShader(const std::string& shaderSource, const unsigned int& type) {
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
