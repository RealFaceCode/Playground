#include "../../hdr/core.h"
#include "../../hdr/window/input.h"

namespace Input
{
	ui32* windowWidth	= nullptr;
	ui32* windowHeight	= nullptr;
	ui32* windowPosX	= nullptr;
	ui32* windowPosY	= nullptr;

	InputSettings settings
	{
		.collectKeyCallback					= false,
		.collectCharacterCallback			= false,
		.collectCursorPositionCallback		= false,
		.collectCursorEnterCallback			= false,
		.collectMouseButtonCallback			= false,
		.collectScrollCallback				= false,
		.collectDropCallback				= false,
		.collectCharModsCallback			= false,
		.collectFramebufferSizeCallback		= false,
		.collectJoystickCallback			= false,
		.collectMonitorCallback				= false,
		.collectWindowContentScaleCallback	= false,
		.collectWindowCloseCallback			= false,
		.collectWindowFocusCallback			= false,
		.collectWindowMaximizeCallback		= false,
		.collectWindowPosCallback			= false,
		.collectWindowRefreshCallback		= false,
		.collectWindowSizeCallback			= false,
		.collectWindowIconifyCallback		= false,
		.loadDropedFiles					= false,
	};

	Key keys[GLFW_KEY_LAST]									= {};
	MouseButton buttons[GLFW_MOUSE_BUTTON_LAST]				= {};
	i8 scrollHorizontal										= 0;
	i8 scrollVertical										= 0;
	extern std::vector<std::string> whitelistedFileEndings	= {};
	std::queue<FileDrop> drops								= {};
	ui32 mouseX												= 0;
	ui32 mouseY												= 0;
	bool onMouseMove										= false;
	bool onWindowMove										= false;
	bool onWindowResize										= false;
	i8 windowEnterLeave										= 0;
	CharacterInput charInput								= { .hasInput = false, .hasModifier = false, .character = 0, .modifierKey = 0, };
	bool frameBufferResized									= false;
	i32 frameBufferWidth									= 0;
	i32 frameBufferHeight									= 0;
	f32 windowContextScaleX									= 0.0f;
	f32 windowContextScaleY									= 0.0f;
	i32 hasWindowFocus										= 0;
	bool isWindowMaximized									= false;
	bool isWindowMinimized									= false;
	bool isWindowSeen										= true;

	bool wasMaximizedBMinimized								= false;

	float ToFloatCoord(const int coord, const int maxLen, const bool flip)
	{
		return flip == true
			? ((float)((float)(coord * 2) / (float)maxLen) - 1.0f) * -1.0f
			: (float)((float)(coord * 2) / (float)maxLen) - 1.0f;
	}

	void Update()
	{
		for (ui32 i = 0; i < GLFW_KEY_LAST; i++)
		{
			if (keys[i].mState == State::PRESSED)
			{
				keys[i].mState = State::ISDOWN;
			}
			if (keys[i].mState == State::RELEASED)
			{
				keys[i].mState = State::NONE;
			}
		}

		for (ui32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
			if (buttons[i].mState == State::PRESSED)
			{
				buttons[i].mState = State::ISDOWN;
			}
			if (buttons[i].mState == State::RELEASED)
			{
				buttons[i].mState = State::NONE;
			}
		}

		scrollHorizontal = 0;
		scrollVertical = 0;
		windowEnterLeave = -1;

		onWindowResize = false;
		onMouseMove = false;
		onWindowMove = false;
		frameBufferResized = false;

		charInput.hasInput = false;
		charInput.hasModifier = false;
		charInput.character = 0;
		charInput.modifierKey = 0;
	}

	bool Key::isPressed()
	{
		return (mState == State::PRESSED);
	}

	bool Key::isRepeat()
	{
		return (mState == State::REPEAT);
	}

	bool Key::isReleased()
	{
		return (mState == State::RELEASED);
	}

	bool Key::isDown()
	{
		return (mState == State::ISDOWN);
	}

	bool MouseButton::isPressed()
	{
		return (mState == State::PRESSED);
	}

	bool MouseButton::isRepeat()
	{
		return (mState == State::REPEAT);
	}

	bool MouseButton::isReleased()
	{
		return (mState == State::RELEASED);
	}

	bool MouseButton::isDown()
	{
		return (mState == State::ISDOWN);
	}

	void SetSetting(InputSettingsEnum setting, bool value)
	{
		switch (setting)
		{
		case Input::CollectKeyCallback:
			settings.collectKeyCallback = value;
			break;
		case Input::CollectCharacterCallback:
			settings.collectCharacterCallback = value;
			break;
		case Input::CollectCursorPositionCallback:
			settings.collectCursorPositionCallback = value;
			break;
		case Input::CollectCursorEnterCallback:
			settings.collectCursorEnterCallback = value;
			break;
		case Input::CollectMouseButtonCallback:
			settings.collectMouseButtonCallback = value;
			break;
		case Input::CollectScrollCallback:
			settings.collectScrollCallback = value;
			break;
		case Input::CollectDropCallback:
			settings.collectDropCallback = value;
			break;
		case Input::CollectCharModsCallback:
			settings.collectCharModsCallback = value;
			break;
		case Input::CollectFramebufferSizeCallback:
			settings.collectFramebufferSizeCallback = value;
			break;
		case Input::CollectJoystickCallback:
			settings.collectJoystickCallback = value;
			break;
		case Input::CollectMonitorCallback:
			settings.collectMonitorCallback = value;
			break;
		case Input::CollectWindowContentScaleCallback:
			settings.collectWindowContentScaleCallback = value;
			break;
		case Input::CollectWindowCloseCallback:
			settings.collectWindowCloseCallback = value;
			break;
		case Input::CollectWindowFocusCallback:
			settings.collectWindowFocusCallback = value;
			break;
		case Input::CollectWindowMaximizeCallback:
			settings.collectWindowMaximizeCallback = value;
			break;
		case Input::CollectWindowPosCallback:
			settings.collectWindowPosCallback = value;
			break;
		case Input::CollectWindowRefreshCallback:
			settings.collectWindowRefreshCallback = value;
			break;
		case Input::CollectWindowSizeCallback:
			settings.collectWindowSizeCallback = value;
			break;
		case Input::CollectWindowIconifyCallback:
			settings.collectWindowIconifyCallback = value;
		case Input::LoadDropedFiles:
			settings.loadDropedFiles = value;
		default:
			break;
		}
	}

	void SetWindowSizePointer(ui32* width, ui32* height)
	{
		windowWidth = width;
		windowHeight = height;
	}

	void SetWindowPositionPointer(ui32* x, ui32* y)
	{
		windowPosX = x;
		windowPosY = y;
	}

	bool IsKeyPressed(const int key)
	{
		return keys[key].isPressed();
	}

	bool IsKeyDown(const int key)
	{
		return keys[key].isDown();
	}

	bool IsKeyReleased(const int key)
	{
		return keys[key].isReleased();
	}

	bool IsKeyState(const State state, const int key)
	{
		switch (state)
		{
		case Input::NONE:
			return keys[key].mState == State::NONE;
			break;
		case Input::PRESSED:
			return IsKeyPressed(key);
			break;
		case Input::REPEAT:
			return keys[key].isRepeat();
			break;
		case Input::RELEASED:
			return IsKeyReleased(key);
			break;
		case Input::ISDOWN:
			return IsKeyDown(key);
			break;
		default:
			return false;
			break;
		}
		return false;
	}

	bool IsMouseButtonPressed(const int button)
	{
		return buttons[button].isPressed();
	}

	bool IsMouseButtonDown(const int button)
	{
		return buttons[button].isDown();
	}

	bool IsMouseButtonReleased(const int button)
	{
		return buttons[button].isReleased();
	}

	bool IsMouseButtonState(const State state, const int button)
	{
		switch (state)
		{
		case Input::NONE:
			return buttons[button].mState == State::NONE;
			break;
		case Input::PRESSED:
			return IsMouseButtonPressed(button);
			break;
		case Input::REPEAT:
			return buttons[button].isRepeat();
			break;
		case Input::RELEASED:
			return IsMouseButtonReleased(button);
			break;
		case Input::ISDOWN:
			return IsMouseButtonDown(button);
			break;
		default:
			return false;
			break;
		}
		return false;
	}

	bool IsScrollUp()
	{
		return (scrollHorizontal == 1);
	}

	bool IsScrollDown()
	{
		return (scrollHorizontal == -1);
	}

	bool IsScrollLeft()
	{
		return (scrollVertical == -1);
	}

	bool IsScrollRight()
	{
		return (scrollVertical == 1);
	}

	i32 GetMouseX()
	{
		return mouseX;
	}

	i32 GetMouseY()
	{
		return mouseY;
	}

	f32 GetMouseXFloat()
	{
		return ToFloatCoord(mouseX, *windowWidth);
	}

	f32 GetMouseYFloat(bool flip)
	{
		return ToFloatCoord(mouseY, *windowHeight, flip);
	}

	bool WasWindowResized()
	{
		return onWindowResize;
	}

	bool WasWindowMoved()
	{
		return onWindowMove;
	}

	bool IsMouseOnMove()
	{
		return onMouseMove;
	}

	bool HasCursorEnteredWindow()
	{
		return (windowEnterLeave == 1);
	}

	bool HasCursorLeftWindow()
	{
		return (windowEnterLeave == 0);
	}

	bool HasFileDrop()
	{
		return !drops.empty();
	}

	void SetFileEndingToWhitelist(const char* fileEnding)
	{
		whitelistedFileEndings.emplace_back(std::string(fileEnding));
	}

	FileDrop getFileDrop()
	{
		FileDrop drop = drops.front();
		drops.pop();
		return drop;
	}

	bool HasCharInput()
	{
		return charInput.hasInput;
	}

	ui32 GetCharInput()
	{
		return charInput.character;
	}

	bool HasCharInputModifierKey()
	{
		return charInput.hasModifier;
	}

	i32 GetCharInputModifierKey()
	{
		return charInput.modifierKey;
	}

	bool WasFrameBufferResized()
	{
		return frameBufferResized;
	}

	i32 GetFrameBufferSizeWidth()
	{
		return frameBufferWidth;
	}

	i32 GetFameBufferSizeHeight()
	{
		return frameBufferHeight;
	}

	bool IsWindowFocused()
	{
		return hasWindowFocus == 1;
	}

	bool IsWindowMaximized()
	{
		return isWindowMaximized;
	}

	bool IsWindowMinimized()
	{
		return isWindowMinimized;
	}

	bool IsWindowSeen()
	{
		return isWindowSeen;
	}

	void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (settings.collectKeyCallback)
		{
			if (action == GLFW_PRESS)
			{
				keys[key].mState = State::PRESSED;
			}
			if (action == GLFW_REPEAT)
			{
				//keys[key].mState = State::REPEAT;
			}
			if (action == GLFW_RELEASE)
			{
				keys[key].mState = State::RELEASED;
			}
		}
	}

	void glfwCharacterCallback(GLFWwindow* window, unsigned int codepoint)
	{
		if (settings.collectCharacterCallback)
		{
			charInput.hasModifier = true;
			charInput.hasInput = true;
			charInput.character = codepoint;
		}
	}

	void glfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (settings.collectCursorPositionCallback)
		{
			onMouseMove = true;
			mouseX = (ui32)xpos;
			mouseY = (ui32)ypos;
		}
	}

	void glfwCursorEnterCallback(GLFWwindow* window, int entered)
	{
		if (settings.collectCursorEnterCallback)
		{
			windowEnterLeave = entered;
		}
	}

	void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (settings.collectMouseButtonCallback)
		{
			if (action == GLFW_PRESS)
			{
				buttons[button].mState = State::PRESSED;
			}
			if (action == GLFW_REPEAT)
			{
				buttons[button].mState = State::REPEAT;
			}
			if (action == GLFW_RELEASE)
			{
				buttons[button].mState = State::RELEASED;
			}
		}
	}

	void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		if (settings.collectScrollCallback)
		{
			scrollHorizontal = yoffset;
			scrollVertical = xoffset;
		}
	}

	void glfwDropCallback(GLFWwindow* window, int count, const char** paths)
	{
		if (settings.collectDropCallback)
		{
			std::vector<std::string> path;
			std::vector<std::string> rejectedPath;
			bool accepted = false;
			for (int i = 0; i < count; i++)
			{
				for (auto ending : whitelistedFileEndings)
				{
					if (EndsWith(paths[i], ending.c_str()))
					{
						accepted = true;
						path.emplace_back(paths[i]);
						continue;
					}
				}
				if (!accepted)
				{
					rejectedPath.emplace_back(paths[i]);
				}
				else
				{
					accepted = false;
				}
			}

			FileDrop drop{
				.numDropedFiles		= (ui64)count,
				.numRejectedFiles	= rejectedPath.size(),
				.rejectedFilePaths	= rejectedPath,
			};
			for (auto p : path)
			{
				if (settings.loadDropedFiles)
				{
					drop.files.emplace_back(FHandle::File(p.c_str(), FILE_GET_SIZE & FILE_CHECK_EXIST & FILE_READ));
				}
				else
				{
					drop.files.emplace_back(FHandle::File(p.c_str(), FILE_GET_SIZE & FILE_CHECK_EXIST));
				}
			}
			drops.push(drop);
		}
	}

	void glfwCharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
	{
		if (settings.collectCharModsCallback)
		{
			charInput.hasInput = true;
			charInput.character = codepoint;
			charInput.modifierKey = mods;
		}
	}

	void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		if (settings.collectFramebufferSizeCallback)
		{
			frameBufferResized = true;
			frameBufferWidth = width;
			frameBufferHeight = height;
		}
	}

	void glfwJoystickCallback(int jid, int event_)
	{
		if (settings.collectJoystickCallback)
		{
		}
	}

	void glfwMonitorCallback(GLFWmonitor* monitor, int event)
	{
		if (settings.collectMonitorCallback)
		{
		}
	}

	void glfwWindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
	{
		if (settings.collectWindowContentScaleCallback)
		{
			windowContextScaleX = xscale;
			windowContextScaleY = yscale;
		}
	}

	void glfwWindowCloseCallback(GLFWwindow* window)
	{
		if (settings.collectWindowCloseCallback)
		{
		}
	}

	void glfwWindowFocusCallback(GLFWwindow* window, int focused)
	{
		if (settings.collectWindowFocusCallback)
		{
			hasWindowFocus = focused;
		}
	}

	void glfwWindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
		if (settings.collectWindowMaximizeCallback)
		{
			if (maximized)
			{
				isWindowMaximized = true;
				isWindowMinimized = false;
			}
			else
			{
				isWindowMaximized = false;
			}
		}
	}

	void glfwWindowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
		if (settings.collectWindowPosCallback)
		{
			onWindowMove = true;
			if (windowPosX)
			{
				*windowPosX = xpos;
			}
			if (windowPosY)
			{
				*windowPosY = ypos;
			}
		}
	}

	void glfwWindowRefreshCallback(GLFWwindow* window)
	{
		if (settings.collectWindowRefreshCallback)
		{
		}
	}

	void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		if (settings.collectWindowSizeCallback)
		{
			onWindowResize = true;
			*windowWidth = width;
			*windowHeight = height;
		}
	}

	void glfwIconifyCallback(GLFWwindow* window, int iconified)
	{
		if (settings.collectWindowIconifyCallback)
		{
			if (!iconified)
			{
				isWindowSeen = true;
				isWindowMinimized = false;
			}
			else
			{
				isWindowSeen = false;
				isWindowMinimized = true;
				if (isWindowMaximized)
				{
					wasMaximizedBMinimized = true;
				}
			}

			if (!isWindowMinimized && wasMaximizedBMinimized)
			{
				isWindowMaximized = true;
				wasMaximizedBMinimized = false;
			}
			else
			{
				isWindowMaximized = false;
			}
		}
	}
}