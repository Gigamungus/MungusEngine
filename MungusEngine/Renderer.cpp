#include "stdafx.h"
#include "Renderer.h"


//////////// internal method declarations //////////////

void glfwStartup(GLFWwindow*& win);
void glewStartup(void);
inline std::string getFileName(const std::string& url);
const std::string shaderSourceFromUrl(const std::string url);
const unsigned int compileShader(const std::string shaderSource, const unsigned int& type);
void compileShaders(std::unordered_map<std::string, const unsigned int>& vertexShaders,
	std::unordered_map<std::string, const unsigned int>& fragmentShaders);

//////////////end internal method declarations /////////////




////////////////// start member function implementations ///////////////

Mungus::Renderer::Renderer(const Application& owner) : owner(owner) {
	glfwStartup(window);
	glewStartup();
	compileShaders(vertexShaders, fragmentShaders);
};

//////////// end member function implementations




//////////////// start internal method implementations /////////////////

void glfwStartup(GLFWwindow*& win) {
	if (!glfwInit()) {
		MLOG("error initializing glfw");
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	win = glfwCreateWindow(1200, 740, "Application", NULL, NULL);

	if (win == NULL) {
		MLOG("error creating glfw window");
	}

	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	glfwSetErrorCallback([](int code, const char* message) {
		MLOG("glfw error " << code << ": " << message);
	});
}


void glewStartup(void) {
	if (glewInit() != GLEW_OK) {
		MLOG("error initializing glew");
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback([](GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message,
		const void *userParam)
	{	std::cout << message << std::endl;	},
		NULL);
}

void compileShaders(	std::unordered_map<std::string, const unsigned int>& vertexShaders,
						std::unordered_map<std::string, const unsigned int>& fragmentShaders) {
	std::vector<std::string> urls{ std::filesystem::current_path().string() + "/../resources/shaders" };

	while (urls.size() > 0) {
		std::string url = urls.back();
		urls.pop_back();

		if (std::filesystem::is_directory(url)) {
			for (auto subFile : std::filesystem::directory_iterator(url)) {
				urls.push_back(subFile.path().string());
			}
		}
		else if (url.find(".shader") != std::string::npos) {
			std::string fileName = getFileName(std::filesystem::path(url).filename().string());
			if (url.find(".vertexshader") != std::string::npos) {
				if (vertexShaders.find(fileName) != vertexShaders.end()) {
					MLOG("trying to recompile shader: " + fileName);
				}
				else {
					vertexShaders.insert(std::make_pair(fileName, compileShader(shaderSourceFromUrl(url), GL_VERTEX_SHADER)));
				}
			}
			else if (url.find(".fragmentshader") != std::string::npos) {
				if (fragmentShaders.find(fileName) != fragmentShaders.end()) {
					MLOG("trying to recompile shader: " + fileName);
				}
				else {
					fragmentShaders.insert(std::make_pair(fileName, compileShader(shaderSourceFromUrl(url), GL_FRAGMENT_SHADER)));
				}
			}
			else {
				MLOG("trying to add unsupported shader type: " + url);
			}
		}
	}
}

const unsigned int compileShader(const std::string shaderSource, const unsigned int& type) {
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
		MLOG("failed to compile shader: " << message);
		MLOG(shaderSource);
	} 

	return shader;
}

const std::string shaderSourceFromUrl(const std::string url) {
	std::ifstream file(url);
	std::string line;
	std::stringstream source;

	if (!file.is_open()) {
		MLOG("error opening file " + url);
	}

	while (getline(file, line)) {
		source << line << "\n";
	}

	return source.str();
}

inline std::string getFileName(const std::string& url) {
	std::stringstream name;

	for (int i = 0; i < url.size() && url[i] != '.'; i++) {
		name << url[i];
	}

	return name.str();
}

//////////////// end internal method implementations /////////////////