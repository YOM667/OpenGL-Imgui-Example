#include "GameEngine.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
GameEngine::GameEngine(Mode mode, ImVec4 backgroundColor, ImVec4 shapeColor) : mode(mode), backgroundColor(backgroundColor), shapeColor(shapeColor)
{
	this->window = initGLFW("Imgui-OpenGL", DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
	initImgui(this->window);
	initGLEW();
	Shader* shader = new Shader("Assets/vertex.txt", "Assets/fragment.txt");
	this->ourShader = shader;
	initEngine();
}
GameEngine::~GameEngine()
{
	if (this->window != NULL)
	{
		delete this->window;
		this->window = NULL;
	}
	if (this->ourShader != NULL)
	{
		delete this->ourShader;
		this->ourShader = NULL;
	}
}


void GameEngine::initEngine()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}


void GameEngine::render()
{

	while (!glfwWindowShouldClose(this->window))
	{
		glfwPollEvents();
		if (this->mode == DEV)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			auto callback = [=]()->void {
				//render imgui
				ImGui::Begin(u8"menu");
				ImGui::Text(u8"color changer");
				ImGui::Indent();
				ImGui::ColorEdit3("BackgroundColor", (float*)&this->backgroundColor);
				ImGui::ColorEdit3("ShapeColor", (float*)&this->shapeColor);
			};
			createFrame(0, 0, 200, 300, callback);
		}
		// input
		processInput(this->window);

		// render
		glClearColor(
			this->backgroundColor.x * this->backgroundColor.w,
			this->backgroundColor.y * this->backgroundColor.w,
			this->backgroundColor.z * this->backgroundColor.w,
			this->backgroundColor.w
		);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw our first triangle
		this->ourShader->use();
		glBindVertexArray(this->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0); // no need to unbind it every time 
		this->ourShader->setUniformf("color", { this->shapeColor.x,this->shapeColor.y,this->shapeColor.z });
		if (this->mode == DEV) {
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		//swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwMakeContextCurrent(this->window);
		glfwSwapBuffers(this->window);
	}
	
}

void GameEngine::shutdown()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);

	//terminate, clearing all previously allocated GLFW resources.
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(this->window);
	glfwTerminate();
}
