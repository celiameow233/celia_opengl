#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

/* 编码片段着色器 F Shader*/
const char *fragmentShader = "#version 330 core\n"
							 "out vec4 FragColor;\n"
							 "void main()\n"
							 "{\n"
							 "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
							 "}\0";

/* 编码顶点着色器 V Shader*/
const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								 "}\0";

void freambuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	/* GLFW Initiation*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* GLFW Create Window*/
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Create window error" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/* Initialize GLAD*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	/*When user change width & height*/
	glfwSetFramebufferSizeCallback(window, freambuffer_size_callback);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 建立顶点缓存部分
	float verticles[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f};
	/* VBO: 顶点缓存对象，将顶点数组一次性由CPU发送到显卡上*/
	unsigned int VBO;
	/* 创建了一个缓冲*/
	glGenBuffers(1, &VBO);
	/* 把 GL_ARRAY_BUFFER 缓冲区绑定到 VBO 这个实体缓冲上*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* 将 verticles 置于 GL_ARRAY_BUFFER 缓冲区中*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	// 建立着色器程序部分
	/* 编译顶点着色器 V Shader*/
	unsigned int vShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexShaderSource, NULL); // 把着色器源码附加到着色器上面
	glCompileShader(vShader);							   // 编译 V Shader
	/* 编译片段着色器 F shader*/
	unsigned int fShader;
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentShader, NULL);
	glCompileShader(fShader);
	/* 合并 Shader 形成 Shader Object Program*/
	unsigned int shaderObjectProgram;
	shaderObjectProgram = glCreateProgram();
	/* 链接之前编译好的 Shader 到 Shader Object Program*/
	glAttachShader(shaderObjectProgram, vShader); // 附加 vShader
	glAttachShader(shaderObjectProgram, fShader); // 附加 fShader
	glLinkProgram(shaderObjectProgram);			  // 链接它们
	/* 激活着色器程序以使用*/
	glUseProgram(shaderObjectProgram);
	/* 链接后可以删除不再需要的着色器对象*/
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	/* 把顶点数据链接到顶点着色器的顶点属性*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	/*Run*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderObjectProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	/*Terminate*/
	glfwTerminate();
	return 0;
}