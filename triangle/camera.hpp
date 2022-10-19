#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
//TODO:
//1 true FPS camera, solution: on xz plane, y = 0
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
		cameraPos.y = 0;
		
		cameraView = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		
		glUniformMatrix4fv(shaderViewLoc, 1, GL_FALSE,
			glm::value_ptr(cameraView));
	}

	glm::mat4 lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
		glm::vec3 dirAxis = glm::normalize(pos - target);

		glm::vec3 rightAxis = glm::normalize(glm::cross(up, dirAxis));

		//parameter up(cameraUp in object) is actually
		//world up, it can determine cameraRight
		//but it's not upAxis in camera Axis
		//eg: when dot(dirAxis, up) != 0
		glm::vec3 upAxis = glm::normalize(glm::cross(dirAxis, rightAxis));

		glm::mat4 translation = glm::mat4(1.0f);

		translation[3][0] = -cameraPos.x;
		translation[3][1] = -cameraPos.y;
		translation[3][2] = -cameraPos.z;

		glm::mat4 rotation = glm::mat4(1.0f);

		rotation[0][0] = rightAxis.x;
		rotation[1][0] = rightAxis.y;
		rotation[2][0] = rightAxis.z;

		rotation[0][1] = upAxis.x;
		rotation[1][1] = upAxis.y;
		rotation[2][1] = upAxis.z;

		rotation[0][2] = dirAxis.x;
		rotation[1][2] = dirAxis.y;
		rotation[2][2] = dirAxis.z;

		//first translation, then rotation
		//can't combine to 1 matrix, since that would cause to first rotation then translation
		//TODO: why does this matrix transform vertex to view coordinates
		return rotation * translation;
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
