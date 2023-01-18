#pragma once

#include <glad.h>

#include "shader.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct RenderApi3D;
struct RenderApi2D;
struct Camera;
struct RenderParams;
struct Buffer3D;
struct Buffer2D;

struct RenderEngine {
	ShaderProgram3D shader3D;
	ShaderProgram2D shader2D;
};

bool createRenderEngine(RenderEngine& engine);

using Render3DCallback = void (const RenderApi3D& api, void* pUserData);
using Render2DCallback = void (const RenderApi2D& api, void* pUserData);

struct RenderParams {
	Render3DCallback* render3DCallback;
	void* pRender3DCallbackUserData;

	Render2DCallback* render2DCallback;
	void* pRender2DCallbackUserData;

	Camera const* pCamera;

	GLint viewportWidth;
	GLint viewportHeight;

	float pointSize;
	float lineWidth;

	glm::vec4 backgroundColor;

	glm::vec4 lightPosition;
	float lightAmbient;
};

void renderEngineFrame(const RenderEngine& engine, const RenderParams& params);