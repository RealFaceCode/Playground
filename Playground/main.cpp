#include "hdr/core.h"
#include "hdr/window/window.h"
#include "hdr/window/input.h"
#include "hdr/gfx/gfx.h"
#include "hdr/gfx/shader.h"
#include "hdr/gfx/batch.h"

int main()
{
	Window::Init();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window::Window win = Window::WindowBuilder
		.setSize(900, 600)
		.setRGBBufferSize(8, 8, 8)
		.setOpacity(1.0f)
		.setRefreshRate(60)
		.centerWindowOnScreen()
		.setStandartCursor(Window::CrosshairCursor)
		.build("playground");

	win.init();

	//input settings
	{
		Input::SetSetting(Input::CollectKeyCallback, true);
		Input::SetSetting(Input::CollectCharacterCallback, true);
		Input::SetSetting(Input::CollectCursorPositionCallback, true);
		Input::SetSetting(Input::CollectCursorEnterCallback, true);
		Input::SetSetting(Input::CollectMouseButtonCallback, true);
		Input::SetSetting(Input::CollectScrollCallback, true);
		Input::SetSetting(Input::CollectDropCallback, true);
		Input::SetSetting(Input::CollectCharModsCallback, true);
		Input::SetSetting(Input::CollectFramebufferSizeCallback, true);
		Input::SetSetting(Input::CollectJoystickCallback, true);
		Input::SetSetting(Input::CollectMonitorCallback, true);
		Input::SetSetting(Input::CollectWindowContentScaleCallback, true);
		Input::SetSetting(Input::CollectWindowCloseCallback, true);
		Input::SetSetting(Input::CollectWindowFocusCallback, true);
		Input::SetSetting(Input::CollectWindowMaximizeCallback, true);
		Input::SetSetting(Input::CollectWindowPosCallback, true);
		Input::SetSetting(Input::CollectWindowRefreshCallback, true);
		Input::SetSetting(Input::CollectWindowSizeCallback, true);
		Input::SetSetting(Input::CollectWindowIconifyCallback, true);
		Input::SetSetting(Input::LoadDropedFiles, true);

		Input::SetFileEndingToWhitelist(".txt");
		Input::SetFileEndingToWhitelist(".node");
	}

	GFX::Init();

	GFX::Shader shader;
	shader.compile("../assets/shader/shader.vert", GL_VERTEX_SHADER);
	shader.compile("../assets/shader/shader.frag", GL_FRAGMENT_SHADER);
	shader.build();
	shader.bind();

	GFX::BatchHandler::SetDefaultValuesBatch(1000, GL_TRIANGLES);
	GFX::BatchHandler::AddImage(GFX::Image("../assets/images/bricks.png"));

	float scale = 1.5f;
	float aspect = (float)win.mSettings.width / (float)win.mSettings.height;

	glm::mat4 proj = glm::ortho(-aspect * scale, aspect * scale, -1.0f * scale, 1.0f * scale, -1.0f, 1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
	shader.setUniformMat4("uProj", proj);
	shader.setUniformMat4("uView", view);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	GFX::BatchVertex vertices[6] = {
		GFX::BatchVertex{ {-0.5,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, 1.0f },
		GFX::BatchVertex{ {-0.5, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, 1.0f },
		GFX::BatchVertex{ { 0.5,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, 1.0f },
																				 
		GFX::BatchVertex{ { 0.5,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, 1.0f },
		GFX::BatchVertex{ { 0.5, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, 1.0f },
		GFX::BatchVertex{ {-0.5, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, 1.0f }
	};

	while (win.isWindowValid())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			win.close();
		}

		GFX::BatchHandler::AddToBatch(vertices, 6);
		GFX::BatchHandler::RenderBatches(shader);

		Input::Update();
		win.swapBuffers();
		Window::pollEvents();
	}

	GFX::BatchHandler::Clear();
	win.clear();

	return 0;
}