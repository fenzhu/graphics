#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//TODO:
//1 true FPS camera 
//2 self lookAt
//3 fov support
class Camera {
public:

	Camera(glm::vec3 pos, glm:: vec3 up, glm::vec3 front)
	: cameraPos(pos), cameraUp(up), cameraFront(front) {
		yaw_axisy = -90.0f;
		pitch_axisx = 0.0f;
		
		lastX = 600;
		lastY = 400;
		//fov = 45.0f;
	}

	void look() {
		if (glfwGetKey(cameraWindow, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(cameraWindow, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(cameraWindow, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(cameraWindow, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		// cameraPos + cameraFront
	
		cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//unsigned int shaderViewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(shaderViewLoc, 1, GL_FALSE,
			glm::value_ptr(cameraView));
	}

	void setWindow(GLFWwindow* window) {
		cameraWindow = window;
		//glfwSetCursorPosCallback(cameraWindow, onMouseMove);
		//glfwSetScrollCallback(cameraWindow, onScroll);
	}

	void setSpeed(float speed) {
		cameraSpeed = speed;
	}

	 void setViewLoc(unsigned int loc) {
		shaderViewLoc = loc;
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
		//std::cout << "x :  " << cameraFront.x << std::endl;
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
	unsigned int shaderViewLoc;
	GLFWwindow* cameraWindow;
	float cameraSpeed;
};

#endif
