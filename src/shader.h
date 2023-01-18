#pragma once

#include <glad.h>

struct ShaderProgram {
	GLuint vertShaderId;
	GLuint fragShaderId;
	GLuint programId;
};

struct CreateShaderProgramParams {
	char const* szVertFilepath;
	char const* szFragFilepath;
};

bool createShaderProgram(ShaderProgram& program, const CreateShaderProgramParams& params);

struct ShaderProgram3D : ShaderProgram {
	GLuint modelLocation;
	GLuint viewLocation;
	GLuint projectionLocation;
	GLuint lightLocation;
	GLuint ambientLocation;
	GLuint lightingEnabledLocation;
};

bool createShaderProgram3D(ShaderProgram3D& program);

struct ShaderProgram2D : ShaderProgram {
	GLuint viewportSizeLocation;
};

bool createShaderProgram2D(ShaderProgram2D& program);

