// Local Headers
#include "glitter.hpp"
#include "../../Build/shader.hpp"
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


float vertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};

float verticesRect[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

float verticesTexture[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};


float verticesCube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int TriVAO;
unsigned int RectVAO;

void createVAO() {
    glGenVertexArrays(1, &TriVAO);
    glBindVertexArray(TriVAO);

    //buffer data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);

    /*
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */
    //how to interpret buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
        5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //unbind VAO
    glBindVertexArray(0);
}
/*
local space: relative to the object origin, share within object
world space: model matrix local -> world. relative to the world origin, share in all objects in game
view space:  view matrix world -> view. also camera space or eye space. transform to coordinates that are in front of camera, which is user's view.
clip space: projection matrix view -> clip. transform coordinates within specified range to normalized device space(NDC (-1.0, 1.0)).
screen space: perspective division is divide xyz by homogeneous component w. performed at the end of shader vertex step. transform 4D clip space to 3D NDC.
*/
int main(int argc, char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported : " << nrAttributes << std::endl;
    
    //build and compile shader
    Shader shader = Shader("G:/Glitter/CustomShader/vertex.vert", 
        "G:/Glitter/CustomShader/fragment.frag");
    

    //laod texture
    int width, height, numChannels;
    stbi_set_flip_vertically_on_load(true);
    //texture wrapping parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //texture filtering parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    unsigned char* data = stbi_load("G:/Glitter/Assets/Texture/container.jpg",
        &width, &height, &numChannels, 0);
    if (data) {
        /*
        paremeter
        1: texture target
        2: mipmap level
        3: format
        4 5: width and height
        6: always 0 legacy stuff
        7 8: format and datatype of source image
        9: image data
        */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
            GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Load texture " << "container " << "failed" << std::endl;
    }
    stbi_image_free(data);


    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //texture wrapping parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //texture filtering parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    data = stbi_load("G:/Glitter/Assets/Texture/face.png",
        &width, &height, &numChannels, 0);

    if (data) {
        /*
        paremeter
        1: texture target
        2: mipmap level
        3: format
        4 5: width and height
        6: always 0 legacy stuff
        7 8: format and datatype of source image
        9: image data
        */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Load texture " << "face " << "failed" << std::endl;
    }
    stbi_image_free(data);

    createVAO();
    shader.use();
    glUniform1i(glGetUniformLocation(shader.ID, "ourTexture"), 0);
    shader.setInt("ourTexture2", 1);

    glm::mat4 view = glm::mat4(1.0f);
    //parameter: matrix translation
    view = glm::translate(view, glm::vec3(-2.0f, 0.0f, -3.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f),
        800.0f / 600.0f, 0.1f, 100.0f);

    unsigned int transformLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));
    transformLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    bool tri = true;
    unsigned int i = 0;
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // Rendering Loop
    glEnable(GL_DEPTH_TEST);
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);
        // Background Fill Color
        glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(TriVAO);
        //default active texture unit
        glActiveTexture(GL_TEXTURE0);
        //bind texture to the currently active texture unit
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
    
        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i + 1) * glfwGetTime();
            //parameter: matrix angle axis
            model = glm::rotate(model, glm::radians(angle),
                glm::vec3(1.0f, 0.3f, 0.5f));
            unsigned int transformLoc = glGetUniformLocation(shader.ID, 
                "model");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                glm::value_ptr(model));
        
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();

        //unbind VAO, new VAO next frame
        glBindVertexArray(0);
    } 
    
    glDeleteVertexArrays(1, &TriVAO);
   
    glfwTerminate();
    return EXIT_SUCCESS;
}
