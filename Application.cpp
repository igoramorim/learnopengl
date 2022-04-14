#include <iostream>

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "WindowManager.h"
#include "Constants.h"

#include "camera.h"
#include "demos/clear_color/DemoClearColor.h"
#include "demos/triangles/DemoTriangles.h"
#include "demos/shader_uniform/DemoShaderUniform.h"
#include "demos/shader_class/DemoShaderClass.h"
#include "demos/texture/DemoTexture.h"
#include "demos/texture_class/DemoTextureClass.h"
#include "demos/transformations/DemoTransformations.h"
#include "demos/coordinate_system_plane/DemoCoordinateSystemPlane.h"
#include "demos/coordinate_system_cube/DemoCoordinateSystemCube.h"
#include "demos/camera_class/DemoCameraClass.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// camera
// Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
// float lastX = Constants::LAST_X;
// float lastY = Constants::LAST_Y;

// timing
// float deltaTime = 0.0f; // time between current frame and last frame
// float lastFrame = 0.0f;

int main()
{
	/*glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	wWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Glfw window creation
	GLFWwindow* window = glfwCreateWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}*/

	// glfwMakeContextCurrent(window);

	// ========================================================================
	// TODO: Implementar os callbacks no WindowManager

	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);
	// ========================================================================

	// glfwSetCursorPos(window, lastX, lastY);

	// Capture the mouse cursor
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // GLFW_CURSOR_NORMAL - GLFW_CURSOR_DISABLED

	// Glad load all OpenGL function pointers
	/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << '\n';
		return -1;
	}*/

	auto windowManager = WindowManager::instance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(windowManager->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	demo::Demo* currentDemo = nullptr;
	demo::DemoMenu* menu = new demo::DemoMenu(currentDemo);
	currentDemo = menu;

	menu->RegisterDemo<demo::DemoClearColor>("Clear Color");
	menu->RegisterDemo<demo::DemoTriangles>("Triangles");
	menu->RegisterDemo<demo::DemoShaderUniform>("Shader Uniform");
	menu->RegisterDemo<demo::DemoShaderClass>("Shader Class");
	menu->RegisterDemo<demo::DemoTexture>("Texture");
	menu->RegisterDemo<demo::DemoTextureClass>("Texture Class");
	menu->RegisterDemo<demo::DemoTransformations>("Transformations");
	menu->RegisterDemo<demo::DemoCoordinateSystemPlane>("Coordinate System: Plane");
	menu->RegisterDemo<demo::DemoCoordinateSystemCube>("Coordinate System: Cube");
	menu->RegisterDemo<demo::DemoCameraClass>("Camera Class");

	// Render loop
	while (!windowManager->WindowShouldClose())
	{

		windowManager->CalculateDeltaTime();
		/*
		float time = glfwGetTime();
		// per-frame time logic
		float currentFrame = time;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		*/

		windowManager->ClearScreen();
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Init ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Debug");

		if (currentDemo)
		{
			currentDemo->ProcessInput();
			currentDemo->OnUpdate(windowManager->GetDeltaTime());
			currentDemo->OnRender();
			if (currentDemo != menu && ImGui::Button("Back"))
			{
				delete currentDemo;
				currentDemo = menu;
			}
			currentDemo->OnImGuiRender();
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("General settings");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("ImGui %s", IMGUI_VERSION);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		windowManager->SwapBuffers();
		// glfwSwapBuffers(window); // Swap the front buffer and the back buffer
		windowManager->PollEvents();
		// glfwPollEvents(); // Checks if any events are triggered (like keyboard)
	}

	if (currentDemo != menu)
		delete menu;
	else
		delete currentDemo;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	windowManager->Terminate();
	// glfwTerminate();
	return 0;
}

/*void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}*/

/*void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}*/
