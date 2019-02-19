#include "stdafx.h"
#include "Application.h"
#include "Renderer.h"
#include "Actor.h"
#include "Camera.h"
#include "Asset.h"
#include "AABBTree.h"
#include "Shader.h"


//////////// internal method declarations //////////////

void glfwStartup(GLFWwindow*& win);
void glewStartup(void);
inline std::string getFileName(const std::string& url);
const std::string shaderSourceFromUrl(const std::string url);
void compileShaders(std::unordered_map<std::string, Mungus::Shader>& programs);

//////////////end internal method declarations /////////////




////////////////// start member function implementations ///////////////

Mungus::Renderer::Renderer(const Application* owner) :
	owner(owner),
	lastFrameTime(0.0f)
{
	glfwStartup(window);
	glewStartup();
	compileShaders(programs);
}

void inline Mungus::Renderer::setBackground(MungusMath::MVec4 color) {
	glClearColor(color.x, color.y, color.z, color.w);
}

void Mungus::Renderer::renderActors(const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>>& actors, const Camera& camera) {
	MungusMath::MMat4 frameTransformations = camera.perspectiveMatrix() * camera.viewMatrix();

	std::vector<std::shared_ptr<Mungus::Actor>> sortedActors = std::vector<std::shared_ptr<Mungus::Actor>>();

	for (auto actor : actors) {
		if (camera.visible(*actor.second)) {
			sortedActors.push_back(actor.second);
		}
	}

	int lkj = 1 + 1;
	std::cout << sortedActors.size() << "\n";

	std::sort(sortedActors.begin(), sortedActors.end(), [&](const std::shared_ptr<Mungus::Actor> obj1, std::shared_ptr<Mungus::Actor> obj2) {
		int progId1 = obj1->getProgramId();
		int progId2 = obj2->getProgramId();
		if (progId1 != progId2) {
			return progId1 - progId2;
		}

		int vaoId1 = obj1->getVAOId();
		int vaoId2 = obj2->getVAOId();
		if (vaoId1 != vaoId2) {
			return vaoId1 - vaoId2;
		}

		return 0;
	});

	int progId = 0;
	int vaoId = 0;

	for (auto actor : sortedActors) {
		if (actor->getProgramId() != progId) {
			progId = actor->getProgramId();
			glUseProgram(progId);
		}
		if (actor->getVAOId() != vaoId) {
			vaoId = actor->getVAOId();
			glBindVertexArray(vaoId);
		}
		renderActor(*actor, frameTransformations);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void Mungus::Renderer::renderActor(const Mungus::Actor& actor, const MungusMath::MMat4& frameTransformations) {
	int progId = actor.getProgramId();
	int vaoId = actor.getVAOId();
	int numTriangVertices = actor.numTriangleVertices();

	//glUseProgram(progId);
	//glBindVertexArray(vaoId);

	MungusMath::MMat4 modelMatrix = actor.modelMatrix();

	MungusMath::MMat4 transformation = frameTransformations * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(progId, "transformation"), 1, GL_TRUE, (float*)&transformation);

	glDrawElements(
		GL_TRIANGLES,
		numTriangVertices,
		GL_UNSIGNED_INT,
		NULL);

	//glUseProgram(0);
	//glBindVertexArray(0);
}

int Mungus::Renderer::getWindowWidth(void) const {
	int width;
	glfwGetWindowSize(window, &width, nullptr);
	return width;
}

int Mungus::Renderer::getWindowHeight(void) const {
	int height;
	glfwGetWindowSize(window, nullptr, &height);
	return height;
}

//////////// end member function implementations




//////////////// start internal method implementations /////////////////

void glfwStartup(GLFWwindow*& win) {
	if (!glfwInit()) {
		MLOG("error initializing glfw");
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	win = glfwCreateWindow(700, 700, "Application", NULL, NULL);

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
	glDebugMessageCallback([](
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message,
		const void *userParam)
	{	MLOG(message << std::endl)	},
		NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(1.0f, 0.0f);

}

void compileShaders(std::unordered_map<std::string, Mungus::Shader>& programs) {
	std::vector<std::string> urls{ std::filesystem::current_path().string() + "/../resources/assets/shaders" };

	while (urls.size() > 0) {
		std::string url = urls.back();
		urls.pop_back();

		if (std::filesystem::is_directory(url)) {
			for (auto subFile : std::filesystem::directory_iterator(url)) {
				urls.push_back(subFile.path().string());
			}
		}
		else {
			json shaderSource = json::parse(MungusUtil::getTextFromFile(url));
			if (shaderSource["type"].get<std::string>() == "program") {
				programs.insert(std::make_pair(shaderSource["title"], Mungus::Shader(shaderSource)));
			}
		}
	}
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
