#ifndef CAMERA_H
#define CAMERA_H

#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//TODO: 1 FPS camera 2 self lookAt
class Camera {
public:

	Camera(glm::vec3 pos, glm:: vec3 up, glm::vec3 front)
	: cameraPos(pos), cameraUp(up), cameraFront(front) {
		yaw_axisy = -90.0f;
		pitch_axisx = 0.0f;
        sensitivity = 0.01f;
		//fov = 45.0f;
	}

	void look() {
		cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		unsigned int shaderViewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(shaderViewLoc, 1, GL_FALSE,
			glm::value_ptr(cameraView));
	}

	void setWindow(GLFWwindow* window) {
		cameraWindow = window;
		//glfwSetCursorPosCallback(cameraWindow, onMouseMove);
		//glfwSetScrollCallback(cameraWindow, onScroll);
	}

	void setShader(Shader s) {
		shader = s;
	}

	void onMouseMove(double xPos, double yPos) {
		float xOffset = xPos - lastX;
		float yOffset = yPos - lastY;

		lastX = xPos;
		lastY = yPos;

		xOffset *= sensitivity;
		yOffset *= sensitivity;

		//xOffset: axis = y
		//yOffset: axis = x
		yaw_axisy += xOffset;
		pitch_axisx += yOffset;

		if (pitch_axisx > 89.0f) {
			pitch_axisx = 89.0f;
		}
		else if (pitch_axisx < -89.0f) {
			pitch_axisx = -89.0f;
		}

		adjustDirection();
	}

	void onScroll(GLFWwindow* window, double xOffset, double yOffset) {

	}

	void adjustDirection() {
		direction.x = cos(glm::radians(yaw_axisy)) * cos(glm::radians(pitch_axisx));
		direction.y = sin(glm::radians(pitch_axisx));
		direction.z = sin(glm::radians(yaw_axisy)) * cos(glm::radians(pitch_axisx));

		//TODO: why need normalize
		cameraFront = glm::normalize(direction);
	}


private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 direction;

	glm::mat4 cameraView;

	//float fov;

	float sensitivity = 0.01f;
	//yaw: axis = y
	//pitch: axis = x
	float yaw_axisy;
	float pitch_axisx;

	float lastX, lastY;

	GLFWwindow* cameraWindow;

	Shader shader;
};

#endif
