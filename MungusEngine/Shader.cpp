#include "stdafx.h"
#include "Shader.h"
#include "VLO.h"

Mungus::Shader::Shader(const json & source) :
	id(0),
	layout(std::make_shared<VLO>(source["vertexAttributes"])) {
	
	id = glCreateProgram();

	int i = 0;
	for (Mungus::VertexAttribute attrib : *layout->GetAttributes()) {
		glBindAttribLocation(id, i, attrib.name.c_str());
		i++;
	}

	std::string vertexShaderSource = source["vertexShader"].get<std::string>();
	std::string fragmentShaderSource = source["fragmentShader"].get<std::string>();

	const char* vertexShader = vertexShaderSource.c_str();
	const char* fragmentShader = fragmentShaderSource.c_str();

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vertexShader, NULL);
	glShaderSource(fs, 1, &fragmentShader, NULL);

	glCompileShader(vs);
	glCompileShader(fs);

	int compileStatus;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE) {
		int length;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);

		char* status = new char[length];

		glGetShaderInfoLog(vs, length, &length, status);

		MLOG("failed to compile shader!\n" << status << "\s");
		delete[] status;
		glDeleteShader(vs);
	}
	else {
		glAttachShader(id, vs);
	}

	glGetShaderiv(fs, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE) {
		int length;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);

		char* status = new char[length];

		glGetShaderInfoLog(fs, length, &length, status);

		MLOG("failed to compile shader!\n" << status << "\s");
		delete[] status;
		glDeleteShader(fs);
	}
	else {
		glAttachShader(id, fs);
	}

	glLinkProgram(id);

	int programLinked;
	glGetProgramiv(id, GL_LINK_STATUS, &programLinked);
	if (programLinked != GL_TRUE)
	{
		int log_length = 0;
		char message[1024];
		glGetProgramInfoLog(id, 1024, &log_length, message);
		MLOG(message)
	}
}

Mungus::Shader::~Shader() {

}
