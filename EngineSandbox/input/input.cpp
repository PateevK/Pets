#include"input.hpp"
#include <glm/glm.hpp>
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

bool fullScreen_on = false;
int size_X, size_Y, pos_X, pos_Y;
bool keyPressed = false;

void ShowMouse(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void setFullScreen(GLFWwindow* window, int key, int action) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (key == GLFW_KEY_F11) {
        if (action == GLFW_PRESS && !keyPressed) {
            keyPressed = true;
            if (!fullScreen_on) {
                glfwGetWindowSize(window, &size_X, &size_Y);
                glfwGetWindowPos(window, &pos_X, &pos_Y);
                glfwSetWindowSize(window, mode->width, mode->height);
                glfwSetWindowPos(window, 0, 0);
                fullScreen_on = true;
            }
            else if (fullScreen_on) { 
                glfwSetWindowSize(window, size_X, size_Y);
                glfwSetWindowPos(window, pos_X, pos_Y);
                fullScreen_on = false;
            }
        }
        if (action == GLFW_RELEASE) {
            keyPressed = false;
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    setFullScreen(window, key, action);
}

float lastFrame = 0.0f;
float deltaTime() {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return deltaTime;
}

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

void cursor_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
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

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }
    else firstMouse = true; 
}

float offset_Y = 0.0f;
void processKeyboard(GLFWwindow* window) {

    const float speed = 8.5f * deltaTime();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += speed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= speed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        offset_Y -= speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        offset_Y += speed;
    cameraPos.y = 0.0f + offset_Y;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};


