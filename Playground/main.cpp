#include "hdr/core.h"
#include "hdr/window/window.h"
#include "hdr/window/input.h"
#include "hdr/gfx/gfx.h"
#include "hdr/gfx/shader.h"
#include "hdr/gfx/batch.h"
#include "hdr/util/time.h"


//namespace GFX
//{
//	struct BatchVertex
//	{
//		glm::vec2 mPosition;
//		glm::vec4 mColor;
//	};
//
//	struct Batch
//	{
//	public:
//		ui64 mMaxVertices;
//		ui64 mUsedVertices;
//		ui32 mVao;
//		ui32 mVbo;
//		ui32 mTexture;
//		ui32 mDrawMode;
//		glm::mat4 mTransform;
//
//	public:
//		Batch(ui64 maxVertices, ui32 mDrawMode)
//			: mMaxVertices(maxVertices), mUsedVertices(0), mVao(0), mVbo(0), mTexture(UINT64_MAX), mDrawMode(mDrawMode), mTransform(glm::mat4(1.0f))
//		{
//			glGenVertexArrays(1, &mVao);
//			glBindVertexArray(mVao);
//
//			glGenBuffers(1, &mVbo);
//			glBindBuffer(GL_ARRAY_BUFFER, mVbo);
//			glBufferData(GL_ARRAY_BUFFER, mMaxVertices * sizeof(BatchVertex), nullptr, GL_DYNAMIC_DRAW);
//
//			glEnableVertexAttribArray(0);
//			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), 0);
//			glEnableVertexAttribArray(1);
//			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(BatchVertex), (void*)offsetof(BatchVertex, mColor));
//
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//			glBindVertexArray(0);
//		}
//
//		void add(BatchVertex vertex)
//		{
//			if (mUsedVertices >= mMaxVertices)
//			{
//				return;
//			}
//
//			glBindVertexArray(mVao);
//			glBindBuffer(GL_ARRAY_BUFFER, mVbo);
//			glBufferSubData(GL_ARRAY_BUFFER, mUsedVertices * sizeof(BatchVertex), sizeof(BatchVertex), &vertex);
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//			mUsedVertices++;
//		}
//
//		bool hasSpace()
//		{
//			return (mMaxVertices > mUsedVertices);
//		}
//
//		bool hasSpace(ui64 elements)
//		{
//			return (mMaxVertices > (mUsedVertices + elements));
//		}
//
//		void render(Shader& shader)
//		{
//			if (mUsedVertices == 0)
//			{
//				return;
//			}
//
//			shader.setUniformMat4("uModel", mTransform);
//
//			glBindVertexArray(mVao);
//			glBindBuffer(GL_ARRAY_BUFFER, mVbo);
//			glDrawArrays(GL_TRIANGLES, 0, mUsedVertices);
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//			glBindVertexArray(0);
//			mUsedVertices = 0;
//		}
//
//		void clear()
//		{
//
//		}
//
//	};
//
//}


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