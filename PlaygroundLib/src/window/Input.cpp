#include "../../hdr/core.h"
#include "../../hdr/window/input.h"
#include "../../hdr/util/memory.h"

namespace Input
{
	ui32* windowWidth	= nullptr;
	ui32* windowHeight	= nullptr;
	ui32* windowPosX	= nullptr;
	ui32* windowPosY	= nullptr;

	struct InputData
	{
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
	    std::vector<String> whitelistedFileEndings              = {};
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
	};

	InputData* inputData;

	void InitInput()
	{
	    inputData = (InputData*)MemReg(new InputData);
	}

	void CleanInput()
	{
	    for(String& str : inputData->whitelistedFileEndings)
	    {
	        str.destroy();
	    }
	    Free(inputData);
	}

	float ToFloatCoord(const int& coord, const int& maxLen, const bool& flip)
	{
		return flip
			? ((float)((float)(coord * 2) / (float)maxLen) - 1.0f) * -1.0f
			: (float)((float)(coord * 2) / (float)maxLen) - 1.0f;
	}

	void Update()
	{
		for (ui32 i = 0; i < GLFW_KEY_LAST; i++)
		{
		    if (inputData->keys[i].mState == State::PRESSED)
			{
		        inputData->keys[i].mState = State::ISDOWN;
			}
		    if (inputData->keys[i].mState == State::RELEASED)
			{
		        inputData->keys[i].mState = State::NONE;
			}
		}

		for (ui32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
		    if (inputData->buttons[i].mState == State::PRESSED)
			{
		        inputData->buttons[i].mState = State::ISDOWN;
			}
		    if (inputData->buttons[i].mState == State::RELEASED)
			{
		        inputData->buttons[i].mState = State::NONE;
			}
		}

		inputData->scrollHorizontal = 0;
		inputData->scrollVertical = 0;
		inputData->windowEnterLeave = -1;

		inputData->onWindowResize = false;
		inputData->onMouseMove = false;
		inputData->onWindowMove = false;
		inputData->frameBufferResized = false;

		inputData->charInput.hasInput = false;
		inputData->charInput.hasModifier = false;
		inputData->charInput.character = 0;
		inputData->charInput.modifierKey = 0;
	}

	bool Key::isPressed() const
	{
		return (mState == State::PRESSED);
	}

	bool Key::isRepeat() const
	{
		return (mState == State::REPEAT);
	}

	bool Key::isReleased() const
	{
		return (mState == State::RELEASED);
	}

	bool Key::isDown() const
	{
		return (mState == State::ISDOWN);
	}

	bool MouseButton::isPressed() const
	{
		return (mState == State::PRESSED);
	}

	bool MouseButton::isRepeat() const
	{
		return (mState == State::REPEAT);
	}

	bool MouseButton::isReleased() const
	{
		return (mState == State::RELEASED);
	}

	bool MouseButton::isDown() const
	{
		return (mState == State::ISDOWN);
	}

	void SetSetting(InputSettingsEnum setting, bool value)
	{
		switch (setting)
		{
		case Input::CollectKeyCallback:
		    inputData->settings.collectKeyCallback = value;
			break;
		case Input::CollectCharacterCallback:
		    inputData->settings.collectCharacterCallback = value;
			break;
		case Input::CollectCursorPositionCallback:
		    inputData->settings.collectCursorPositionCallback = value;
			break;
		case Input::CollectCursorEnterCallback:
		    inputData->settings.collectCursorEnterCallback = value;
			break;
		case Input::CollectMouseButtonCallback:
		    inputData->settings.collectMouseButtonCallback = value;
			break;
		case Input::CollectScrollCallback:
		    inputData->settings.collectScrollCallback = value;
			break;
		case Input::CollectDropCallback:
		    inputData->settings.collectDropCallback = value;
			break;
		case Input::CollectCharModsCallback:
		    inputData->settings.collectCharModsCallback = value;
			break;
		case Input::CollectFramebufferSizeCallback:
		    inputData->settings.collectFramebufferSizeCallback = value;
			break;
		case Input::CollectJoystickCallback:
		    inputData->settings.collectJoystickCallback = value;
			break;
		case Input::CollectMonitorCallback:
		    inputData->settings.collectMonitorCallback = value;
			break;
		case Input::CollectWindowContentScaleCallback:
		    inputData->settings.collectWindowContentScaleCallback = value;
			break;
		case Input::CollectWindowCloseCallback:
		    inputData->settings.collectWindowCloseCallback = value;
			break;
		case Input::CollectWindowFocusCallback:
		    inputData->settings.collectWindowFocusCallback = value;
			break;
		case Input::CollectWindowMaximizeCallback:
		    inputData->settings.collectWindowMaximizeCallback = value;
			break;
		case Input::CollectWindowPosCallback:
		    inputData->settings.collectWindowPosCallback = value;
			break;
		case Input::CollectWindowRefreshCallback:
		    inputData->settings.collectWindowRefreshCallback = value;
			break;
		case Input::CollectWindowSizeCallback:
		    inputData->settings.collectWindowSizeCallback = value;
			break;
		case Input::CollectWindowIconifyCallback:
		    inputData->settings.collectWindowIconifyCallback = value;
		case Input::LoadDropedFiles:
		    inputData->settings.loadDropedFiles = value;
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

	bool IsKeyPressed(const int& key)
	{
	    return inputData->keys[key].isPressed();
	}

	bool IsKeyDown(const int& key)
	{
	    return inputData->keys[key].isDown();
	}

	bool IsKeyReleased(const int& key)
	{
	    return inputData->keys[key].isReleased();
	}

	bool IsKeyState(const State& state, const int& key)
	{
		switch (state)
		{
		case Input::NONE:
		    return inputData->keys[key].mState == State::NONE;
			break;
		case Input::PRESSED:
			return IsKeyPressed(key);
			break;
		case Input::REPEAT:
		    return inputData->keys[key].isRepeat();
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

	bool IsMouseButtonPressed(const int& button)
	{
	    return inputData->buttons[button].isPressed();
	}

	bool IsMouseButtonDown(const int& button)
	{
	    return inputData->buttons[button].isDown();
	}

	bool IsMouseButtonReleased(const int& button)
	{
	    return inputData->buttons[button].isReleased();
	}

	bool IsMouseButtonState(const State& state, const int& button)
	{
		switch (state)
		{
		case Input::NONE:
		    return inputData->buttons[button].mState == State::NONE;
			break;
		case Input::PRESSED:
			return IsMouseButtonPressed(button);
			break;
		case Input::REPEAT:
		    return inputData->buttons[button].isRepeat();
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
	    return (inputData->scrollHorizontal == 1);
	}

	bool IsScrollDown()
	{
	    return (inputData->scrollHorizontal == -1);
	}

	bool IsScrollLeft()
	{
	    return (inputData->scrollVertical == -1);
	}

	bool IsScrollRight()
	{
	    return (inputData->scrollVertical == 1);
	}

	i32 GetMouseX()
	{
	    return (i32)inputData->mouseX;
	}

	i32 GetMouseY()
	{
	    return (i32)inputData->mouseY;
	}

	f32 GetMouseXFloat()
	{
	    return ToFloatCoord(inputData->mouseX, *windowWidth);
	}

	f32 GetMouseYFloat(bool flip)
	{
	    return ToFloatCoord(inputData->mouseY, *windowHeight, flip);
	}

	bool WasWindowResized()
	{
	    return inputData->onWindowResize;
	}

	bool WasWindowMoved()
	{
	    return inputData->onWindowMove;
	}

	bool IsMouseOnMove()
	{
	    return inputData->onMouseMove;
	}

	bool HasCursorEnteredWindow()
	{
	    return (inputData->windowEnterLeave == 1);
	}

	bool HasCursorLeftWindow()
	{
	    return (inputData->windowEnterLeave == 0);
	}

	bool HasFileDrop()
	{
	    return !inputData->drops.empty();
	}

	void SetFileEndingToWhitelist(const char* fileEnding)
	{
	    inputData->whitelistedFileEndings.emplace_back(fileEnding);
	}

	FileDrop getFileDrop()
	{
	    FileDrop drop = inputData->drops.front();
	    inputData->drops.pop();
		return drop;
	}

	bool HasCharInput()
	{
	    return inputData->charInput.hasInput;
	}

	ui32 GetCharInput()
	{
	    return inputData->charInput.character;
	}

	bool HasCharInputModifierKey()
	{
	    return inputData->charInput.hasModifier;
	}

	i32 GetCharInputModifierKey()
	{
	    return inputData->charInput.modifierKey;
	}

	bool WasFrameBufferResized()
	{
	    return inputData->frameBufferResized;
	}

	i32 GetFrameBufferSizeWidth()
	{
	    return inputData->frameBufferWidth;
	}

	i32 GetFameBufferSizeHeight()
	{
	    return inputData->frameBufferHeight;
	}

	bool IsWindowFocused()
	{
	    return inputData->hasWindowFocus == 1;
	}

	bool IsWindowMaximized()
	{
	    return inputData->isWindowMaximized;
	}

	bool IsWindowMinimized()
	{
	    return inputData->isWindowMinimized;
	}

	bool IsWindowSeen()
	{
	    return inputData->isWindowSeen;
	}

	void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	    if (inputData->settings.collectKeyCallback)
		{
			if (action == GLFW_PRESS)
			{
			    inputData->keys[key].mState = State::PRESSED;
			}
			if (action == GLFW_REPEAT)
			{
				//keys[key].mState = State::REPEAT;
			}
			if (action == GLFW_RELEASE)
			{
			    inputData->keys[key].mState = State::RELEASED;
			}
		}
	}

	void glfwCharacterCallback(GLFWwindow* window, unsigned int codepoint)
	{
	    if (inputData->settings.collectCharacterCallback)
		{
	        inputData->charInput.hasModifier = true;
	        inputData->charInput.hasInput = true;
	        inputData->charInput.character = codepoint;
		}
	}

	void glfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
	    if (inputData->settings.collectCursorPositionCallback)
		{
			inputData->onMouseMove = true;
			inputData->mouseX = (ui32)xpos;
			inputData->mouseY = (ui32)ypos;
		}
	}

	void glfwCursorEnterCallback(GLFWwindow* window, int entered)
	{
	    if (inputData->settings.collectCursorEnterCallback)
		{
	        inputData->windowEnterLeave = entered;
		}
	}

	void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
	    if (inputData->settings.collectMouseButtonCallback)
		{
			if (action == GLFW_PRESS)
			{
			    inputData->buttons[button].mState = State::PRESSED;
			}
			if (action == GLFW_REPEAT)
			{
			    inputData->buttons[button].mState = State::REPEAT;
			}
			if (action == GLFW_RELEASE)
			{
			    inputData->buttons[button].mState = State::RELEASED;
			}
		}
	}

	void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
	    if (inputData->settings.collectScrollCallback)
		{
			inputData->scrollHorizontal = yoffset;
			inputData->scrollVertical = xoffset;
		}
	}

	void glfwDropCallback(GLFWwindow* window, int count, const char** paths)
	{
	    if (inputData->settings.collectDropCallback)
		{
			std::vector<String> path;
			std::vector<String> rejectedPath;
			bool accepted = false;
			for (int i = 0; i < count; i++)
			{
			    for (const auto& ending : inputData->whitelistedFileEndings)
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
			    if (inputData->settings.loadDropedFiles)
				{
			        drop.files.emplace_back(FHandle::File(p.c_str(), FILE_GET_SIZE & FILE_CHECK_EXIST & FILE_READ));
				}
				else
				{
				    drop.files.emplace_back(FHandle::File(p.c_str(), FILE_GET_SIZE & FILE_CHECK_EXIST));
				}
			}
			inputData->drops.push(drop);
		}
	}

	void glfwCharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
	{
	    if (inputData->settings.collectCharModsCallback)
		{
	        inputData->charInput.hasInput = true;
			inputData->charInput.character = codepoint;
			inputData->charInput.modifierKey = mods;
		}
	}

	void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
	    if (inputData->settings.collectFramebufferSizeCallback)
		{
			inputData->frameBufferResized = true;
			inputData->frameBufferWidth = width;
			inputData->frameBufferHeight = height;
		}
	}

	void glfwJoystickCallback(int jid, int event_)
	{
	    if (inputData->settings.collectJoystickCallback)
		{
		}
	}

	void glfwMonitorCallback(GLFWmonitor* monitor, int event)
	{
	    if (inputData->settings.collectMonitorCallback)
		{
		}
	}

	void glfwWindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
	{
	    if (inputData->settings.collectWindowContentScaleCallback)
		{
			inputData->windowContextScaleX = xscale;
			inputData->windowContextScaleY = yscale;
		}
	}

	void glfwWindowCloseCallback(GLFWwindow* window)
	{
	    if (inputData->settings.collectWindowCloseCallback)
		{
		}
	}

	void glfwWindowFocusCallback(GLFWwindow* window, int focused)
	{
	    if (inputData->settings.collectWindowFocusCallback)
		{
	        inputData->hasWindowFocus = focused;
		}
	}

	void glfwWindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
	    if (inputData->settings.collectWindowMaximizeCallback)
		{
			if (maximized)
			{
				inputData->isWindowMaximized = true;
				inputData->isWindowMinimized = false;
			}
			else
			{
			    inputData->isWindowMaximized = false;
			}
		}
	}

	void glfwWindowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
	    if (inputData->settings.collectWindowPosCallback)
		{
	        inputData->onWindowMove = true;
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
	    if (inputData->settings.collectWindowRefreshCallback)
		{
		}
	}

	void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
	    if (inputData->settings.collectWindowSizeCallback)
		{
	        inputData->onWindowResize = true;
			*windowWidth = width;
			*windowHeight = height;
		}
	}

	void glfwIconifyCallback(GLFWwindow* window, int iconified)
	{
	    if (inputData->settings.collectWindowIconifyCallback)
		{
			if (!iconified)
			{
			    inputData->isWindowSeen = true;
			    inputData->isWindowMinimized = false;
			}
			else
			{
			    inputData->isWindowSeen = false;
			    inputData->isWindowMinimized = true;
			    if (inputData->isWindowMaximized)
				{
			        inputData->wasMaximizedBMinimized = true;
				}
			}

			if (!inputData->isWindowMinimized && inputData->wasMaximizedBMinimized)
			{
			    inputData->isWindowMaximized = true;
			    inputData->wasMaximizedBMinimized = false;
			}
			else
			{
			    inputData->isWindowMaximized = false;
			}
		}
	}

    FileDrop::~FileDrop()
    {
        for(String& s : rejectedFilePaths)
        {
            s.destroy();
        }
    }
}