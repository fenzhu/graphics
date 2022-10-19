// Local Headers
#include "glitter.hpp"
#include "shader.hpp"
#include "camera.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera初始参数
Camera camera(glm::vec3(1.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 0.2f, 3.0f);

unsigned int CubeVAO;
unsigned int LightVAO;
unsigned int VBO;

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

void createCubeVAO()
{
    // vertex array object
    glGenVertexArrays(1, &CubeVAO);
    glBindVertexArray(CubeVAO);

    // vertex buffer object
    //  buffer data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*s
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */
    // how to interpret buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    //(void *)3并不是步长 3个float并不是3个字节
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind VAO
    glBindVertexArray(0);
}

void createLightVAO()
{ // vertex array object
    glGenVertexArrays(1, &LightVAO);
    glBindVertexArray(LightVAO);

    // vertex buffer object
    //  buffer data
    // glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */
    // how to interpret buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // unbind VAO
    glBindVertexArray(0);
}
/*
local space: relative to the object origin, share within object
world space: model matrix, local -> world. relative to the world origin, share in all objects in game
view space:  view matrix, world -> view. also camera space or eye space. transform to coordinates that are in front of camera, which is user's view.
clip space: projection matrix, view -> clip. transform coordinates within specified range to normalized device space(NDC (-1.0, 1.0)).
screen space: perspective division is divide xyz by homogeneous component w. performed at the end of shader vertex step. transform 4D clip space to 3D NDC.
*/
int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OPENGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr)
    {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    // glfwSetScrollCallback(mWindow, scroll_callback);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported : " << nrAttributes << std::endl;

    // build and compile shader
    Shader cubeShader = Shader("E:/Glitter/Glitter/Shaders/cube.vert",
                               "E:/Glitter/Glitter/Shaders/material.frag");
    Shader lightShader = Shader("E:/Glitter/Glitter/Shaders/light.vert",
                                "E:/Glitter/Glitter/Shaders/light.frag");

    // keep the order
    createCubeVAO();
    createLightVAO();

    // Rendering Loop
    glEnable(GL_DEPTH_TEST);
    while (glfwWindowShouldClose(mWindow) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(mWindow);
        // Background Fill Color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 objectCenter(0.0f, 0.0f, 0.0f);
        float distance = glm::distance(objectCenter, lightPos);
        float time = glfwGetTime();
        // lightPos.x = distance * cos(time);
        // lightPos.y = distance * sin(time);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

        cubeShader.use();

        cubeShader.setVec3("material.ambient", 0.0f, 0.1f, 0.06f);
        cubeShader.setVec3("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);
        cubeShader.setVec3("material.specular",  0.50196078f, 0.50196078f, 0.50196078f);
        cubeShader.setFloat("material.shininess", 32.0f);

        cubeShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f); // darken diffuse light a bit
        cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        cubeShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        cubeShader.setVec3("lightColor", glm::vec3(1.0f));
        cubeShader.setVec3("lightPos", lightPos);
        cubeShader.setVec3("viewPos", camera.Position);

        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", glm::mat4(1.0f));

        glBindVertexArray(CubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.use();

        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("model", model);

        glBindVertexArray(LightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();

        // unbind VAO, new VAO next frame
        // glBindVertexArray(0);
    }

    glDeleteVertexArrays(1, &CubeVAO);
    glDeleteVertexArrays(1, &LightVAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(static_cast<float>(yoffset));
    // camera.onScroll()
}
