#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const float verticle1[] = {
    // first triangle
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

const float verticle2[] = {
    // second triangle
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.0f, -0.5f, 0.0f};

void freamwork_buffer_sizeback(GLFWwindow *window, int weight, int height)
{
    glViewport(0, 0, weight, height);
}

const char *vShaderSource = "#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                            "}\0";

const char *fShaderSource1 = "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "void main()\n"
                             "{\n"
                             "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                             "}\0";

const char *fShaderSource2 = "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "void main(){\n"
                             "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);}\0";

void setWindowShouldClose(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

using namespace std;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "HelloOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Create Window ERROR" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to load GLAD." << endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticle1), verticle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticle2), verticle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int vShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);

    unsigned int fShader1;
    fShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader1, 1, &fShaderSource1, NULL);
    glCompileShader(fShader1);

    unsigned int fShader2;
    fShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader2, 1, &fShaderSource2, NULL);
    glCompileShader(fShader2);

    unsigned int shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vShader);
    glAttachShader(shaderProgram1, fShader1);
    glLinkProgram(shaderProgram1);
    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vShader);
    glAttachShader(shaderProgram2, fShader2);
    glLinkProgram(shaderProgram2);

    glUseProgram(shaderProgram1);
    glUseProgram(shaderProgram2);
    glDeleteShader(vShader);
    glDeleteShader(fShader1);
    glDeleteShader(fShader2);

    while (!glfwWindowShouldClose(window))
    {
        setWindowShouldClose(window);
        glfwSetFramebufferSizeCallback(window, freamwork_buffer_sizeback);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glfwTerminate();
    return 0;
}