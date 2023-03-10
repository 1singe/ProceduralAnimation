#include "viewer.h"
#include "drawbuffer.h"
#include "renderapi.h"
#include "cloth.h"

#include <time.h>
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include "utils.h"

#define COUNTOF(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

constexpr char const* viewerName = "MyViewer";
constexpr glm::vec4 white = { 1.f, 1.f, 1.f, 1.f };

struct MyViewer : Viewer {

	glm::vec3 jointPosition;
	glm::vec3 cubePosition;
	float boneAngle;

	glm::vec2 mousePos;
	bool leftMouseButtonPressed;
	bool altKeyPressed;

    Particle* particle;
    std::shared_ptr<Cloth> cloth;

    float sphereAngle = 0.0;

    std::vector<std::shared_ptr<Entity>> entities;



	MyViewer() : Viewer(viewerName, 1280, 720) {}

	void init() override {

        cloth = std::make_shared<Cloth>(glm::vec3{-1.2, 0.1, 1.2}, 2, 2, 25, 25);
//        cloth->getParticle(2, 24)->movable = false;
        cloth->getParticle(21, 24)->movable = false;
        cloth->getParticle(21, 0)->addForce({0.f, 0.f, 10.f});

        particle = new Particle(glm::vec3(0.f, 0.f, 0.f), 1.f, 0.035f);
		cubePosition = glm::vec3(1.f, 0.25f, -1.f);
		jointPosition = glm::vec3(-1.f, 2.f, -1.f);
		boneAngle = 0.f;
		mousePos = {0.f, 0.f};
		leftMouseButtonPressed = false;
		altKeyPressed = false;

        // Add entities
        entities.emplace_back(new Cloth(glm::vec3{1, 1.5, 0.5}));
        entities.emplace_back(particle);
        particle->AddForce(glm::vec3{0, 100, 0});

        for(auto& entity : entities) {
            entity->init();
        }
	}

	void update(double elapsedTime) override {

		boneAngle = (float) elapsedTime;
		sphereAngle = (float) elapsedTime;

		leftMouseButtonPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		altKeyPressed = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		mousePos = { float(mouseX), viewportHeight - float(mouseY) };


        for(auto& entity : entities) {
            entity->update(elapsedTime);
        }

        glm::quat q = glm::angleAxis(boneAngle, glm::vec3(0.f, 1.f, 0.f));
        cloth->ballCollision(glm::vec3(-1.f, 0.5f, 1.f) * q, 0.5f);

	}

	void render3D(const RenderApi3D& api) const override {
		api.grid(10.f, 10, glm::vec4(0.5f, 0.5f, 0.5f, 1.f), nullptr);

		api.axisXYZ(nullptr);
		
		constexpr float cubeSize = 0.5f;
		glm::mat4 cubeModelMatrix = glm::translate(glm::identity<glm::mat4>(), cubePosition);
		api.solidCube(cubeSize, white, &cubeModelMatrix);

		{
			glm::vec3 vertices[] = {
				{0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize},
				{0.f, cubeSize, 0.f},
				{0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize},
				{0.f, cubeSize, 0.f},
				{-0.5f * cubeSize, 0.5f * cubeSize, 0.5f * cubeSize},
				{0.f, cubeSize, 0.f},
				{-0.5f * cubeSize, 0.5f * cubeSize, -0.5f * cubeSize},
				{0.f, cubeSize, 0.f},
			};
			api.lines(vertices, COUNTOF(vertices), white, &cubeModelMatrix);
		}

		{
			glm::quat q = glm::angleAxis(boneAngle, glm::vec3(0.f, 1.f, 0.f));
			glm::vec3 childRelPos = { 1.f, 1.f, 0.f };
			api.bone(childRelPos, white, q, glm::vec3(0.f, 0.f, 0.f));
			glm::vec3 childAbsPos = q * childRelPos;
			api.solidSphere(childAbsPos, 0.05f, 10, 10, white);
		}

        glm::quat q = glm::angleAxis(boneAngle, glm::vec3(0.f, 1.f, 0.f));
		api.solidSphere(glm::vec3(-1.f, 0.5f, 1.f) * q, 0.5f, 100, 100, white);

        for(auto& entity : entities) {
            entity->render3D(api);
        }
	}

	void render2D(const RenderApi2D& api) const override {
		
		constexpr float padding = 50.f;

		if (altKeyPressed) {
			if (leftMouseButtonPressed) {
				api.circleFill(mousePos, padding, 10, white);
			} else {
				api.circleContour(mousePos, padding, 10, white);
			}
				
		} else {
			const glm::vec2 min = mousePos + glm::vec2(padding, padding);
			const glm::vec2 max = mousePos + glm::vec2(-padding, -padding);
			if (leftMouseButtonPressed) {
				api.quadFill(min, max, white);
			}
			else {
				api.quadContour(min, max, white);
			}
		}

		{
			const glm::vec2 from = { viewportWidth * 0.5f, padding };
			const glm::vec2 to = { viewportWidth * 0.5f, 2.f * padding };
			constexpr float thickness = padding * 0.25f;
			constexpr float hatRatio = 0.3f;
			api.arrow(from, to, thickness, hatRatio, white);
		}

		{
			glm::vec2 vertices[] = {
				{ padding, viewportHeight - padding },
				{ viewportWidth * 0.5f, viewportHeight - 2.f * padding },
				{ viewportWidth * 0.5f, viewportHeight - 2.f * padding },
				{ viewportWidth - padding, viewportHeight - padding },
			};
			api.lines(vertices, COUNTOF(vertices), white);
		}
	}

	void drawGUI() override {
		static bool showDemoWindow = false;

		ImGui::Begin("3D Sandbox");

		ImGui::Checkbox("Show demo window", &showDemoWindow);

		ImGui::ColorEdit4("Background color", (float*)&backgroundColor, ImGuiColorEditFlags_NoInputs);

		ImGui::SliderFloat("Point size", &pointSize, 0.1f, 10.f);
		ImGui::SliderFloat("Line Width", &lineWidth, 0.1f, 10.f);

		ImGui::SliderFloat3("Light Position", (float(&)[3])lightPosition, -10.f, 10.f);
		ImGui::SliderFloat("Line Ambient", &lightAmbient, 0.f, 10.f);

		float fovDegrees = glm::degrees(camera.fov);
		if (ImGui::SliderFloat("Camera field of fiew (degrees)", &fovDegrees, 15, 180)) {
			camera.fov = glm::radians(fovDegrees);
		}

		ImGui::SliderFloat3("Cube Position", (float(&)[3])cubePosition, -1.f, 1.f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::End();

		if (showDemoWindow) {
			// Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			ImGui::ShowDemoWindow(&showDemoWindow);
		}
	}
};

int main(int argc, char** argv) {
	MyViewer v;
	return v.run();
}
