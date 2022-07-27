#ifndef INPUT_H
#define INPUT_H
#include "../core.h"

namespace Input
{
	extern ui32* windowWidth;
	extern ui32* windowHeight;
	extern ui32* windowPosX;
	extern ui32* windowPosY;

	enum InputSettingsEnum
	{
		//Enum input collection
		CollectKeyCallback,
		CollectCharacterCallback,
		CollectCursorPositionCallback,
		CollectCursorEnterCallback,
		CollectMouseButtonCallback,
		CollectScrollCallback,
		CollectDropCallback,
		CollectCharModsCallback,
		CollectFramebufferSizeCallback,
		CollectJoystickCallback,
		CollectMonitorCallback,
		CollectWindowContentScaleCallback,
		CollectWindowCloseCallback,
		CollectWindowFocusCallback,
		CollectWindowMaximizeCallback,
		CollectWindowPosCallback,
		CollectWindowRefreshCallback,
		CollectWindowSizeCallback,
		CollectWindowIconifyCallback,
		//Enum handle stuff
		LoadDropedFiles,
	};

	struct InputSettings
	{
	public:
		//Setting input collection
		bool collectKeyCallback;
		bool collectCharacterCallback;
		bool collectCursorPositionCallback;
		bool collectCursorEnterCallback;
		bool collectMouseButtonCallback;
		bool collectScrollCallback;
		bool collectDropCallback;
		bool collectCharModsCallback;
		bool collectFramebufferSizeCallback;
		bool collectJoystickCallback;
		bool collectMonitorCallback;
		bool collectWindowContentScaleCallback;
		bool collectWindowCloseCallback;
		bool collectWindowFocusCallback;
		bool collectWindowMaximizeCallback;
		bool collectWindowPosCallback;
		bool collectWindowRefreshCallback;
		bool collectWindowSizeCallback;
		bool collectWindowIconifyCallback;
		//Settings handle stuff
		bool loadDropedFiles;
	};

	enum State
	{
		NONE = 0,
		PRESSED = 1,
		REPEAT = 2,
		RELEASED = 3,
		ISDOWN = 4
	};

	struct Key
	{
	public:
		State mState = State::NONE;
		ui16 key;

		bool isPressed();
		bool isRepeat();
		bool isReleased();
		bool isDown();
	};

	struct MouseButton
	{
	public:
		State mState = State::NONE;
		ui8 button;

		bool isPressed();
		bool isRepeat();
		bool isReleased();
		bool isDown();
	};

	struct FileDrop
	{
	public:
		const ui64 numDropedFiles					= 0;;
		const ui64 numRejectedFiles					= 0;
		std::vector<FHandle::File> files			= {};
		std::vector<std::string> rejectedFilePaths	= {};
	};

	struct CharacterInput
	{
	public:
		bool hasInput;
		bool hasModifier;
		ui32 character;
		i32 modifierKey;
	};

	void Update();

	void SetSetting(InputSettingsEnum setting, bool value);
	void SetWindowSizePointer(ui32* width, ui32* height);
	void SetWindowPositionPointer(ui32* x, ui32* y);

	bool IsKeyPressed(const int key);
	bool IsKeyDown(const int key);
	bool IsKeyReleased(const int key);
	bool IsKeyState(const State state, const int key);

	bool IsMouseButtonPressed(const int button);
	bool IsMouseButtonDown(const int button);
	bool IsMouseButtonReleased(const int button);
	bool IsMouseButtonState(const State state, const int button);

	bool IsScrollUp();
	bool IsScrollDown();
	bool IsScrollLeft();
	bool IsScrollRight();

	i32 GetMouseX();
	i32 GetMouseY();
	f32 GetMouseXFloat();
	f32 GetMouseYFloat(bool flip = true);

	bool WasWindowResized();
	bool WasWindowMoved();
	bool IsMouseOnMove();

	bool HasCurserEnteredWindow();
	bool HasCursorLeftWindow();

	void SetFileEndingToWhitelist(const char* fileEnding);
	bool HasFileDrop();
	FileDrop getFileDrop();

	bool HasCharInput();
	ui32 GetCharInput();
	bool HasCharInputModifierKey();
	i32 GetCharInputModifierKey();

	bool WasFrameBufferResized();
	i32 GetFrameBufferSizeWidth();
	i32 GetFameBufferSizeHeight();

	bool IsWindowFocused();
	
	bool IsWindowMaximized();
	bool IsWindowMinimized();
	bool IsWindowSeen();

	extern void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);	//
	extern void glfwCharacterCallback(GLFWwindow* window, unsigned int codepoint);					//
	extern void glfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);			//
	extern void glfwCursorEnterCallback(GLFWwindow* window, int entered);							//
	extern void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);		//
	extern void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);				//
	extern void glfwDropCallback(GLFWwindow* window, int count, const char** paths);				//
	extern void glfwCharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);			//
	extern void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);				//
	extern void glfwJoystickCallback(int jid, int event_);
	extern void glfwMonitorCallback(GLFWmonitor* monitor, int event);
	extern void glfwWindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);		//
	extern void glfwWindowCloseCallback(GLFWwindow* window);
	extern void glfwWindowFocusCallback(GLFWwindow* window, int focused);							//
	extern void glfwWindowMaximizeCallback(GLFWwindow* window, int maximized);						//
	extern void glfwWindowPosCallback(GLFWwindow* window, int xpos, int ypos);						//
	extern void glfwWindowRefreshCallback(GLFWwindow* window);
	extern void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);					//
	extern void glfwIconifyCallback(GLFWwindow* window, int iconified);								//
};	

#endif // !INPUT_H
