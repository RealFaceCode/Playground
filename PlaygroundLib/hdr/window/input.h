#ifndef INPUT_H
#define INPUT_H
#include "../core.h"
#include "../util/buffer/string.h"

namespace Input
{
	extern ui32* windowWidth;
	extern ui32* windowHeight;
	extern ui32* windowPosX;
	extern ui32* windowPosY;

	void InitInput();
	void CleanInput();

	/**@brief Defines all callback collections and handle options*/
	enum InputSettingsEnum
	{
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

	/**@brief Holds all information about the callback collection and handle options*/
	struct InputSettings
	{
	public:
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

	/**@brief Defines all available key states*/
	enum State
	{
		NONE = 0,
		PRESSED = 1,
		REPEAT = 2,
		RELEASED = 3,
		ISDOWN = 4
	};

	/**@brief Holds all information about a Key*/
	struct Key
	{
	public:
		State mState = State::NONE;
		ui16 mKey;

		bool isPressed() const;
		bool isRepeat() const;
		bool isReleased() const;
		bool isDown() const;
	};

	/**@brief Holds all information about a Button*/
	struct MouseButton
	{
	public:
		State mState = State::NONE;
		ui8 mButton;

		bool isPressed() const;
		bool isRepeat() const;
		bool isReleased() const;
		bool isDown() const;
	};

	/**@brief Holds all information about a FileDrop*/
	struct FileDrop
	{
	public:
	    ~FileDrop();
		const ui64 numDropedFiles					= 0;;
		const ui64 numRejectedFiles					= 0;
		std::vector<FHandle::File> files			= {};
		std::vector<String> rejectedFilePaths	= {};
	};

	/**@brief Holds all information about char input*/
	struct CharacterInput
	{
	public:
		bool hasInput;
		bool hasModifier;
		ui32 character;
		i32 modifierKey;
	};

	/**@brief Converts int coords to float coords
	 * @param[in] coord
	 * @param[in] maxLen
	 * @param[in] flip
	 * @returns
	 * Returns a float coordinate depends on the input coord as a int and the max length/width of the window
	 * If flip is set to true the return value is changed to negative/positive
	 */
    float ToFloatCoord(const int& coord, const int& maxLen, const bool& flip = false);

    /**@brief Updates the input buffers
	 * @returns
	 * VOID
	 */
	void Update();

	/**@brief Sets the targeted setting to the given value
	 * @param[in] setting
	 * @param[in] value
	 * @returns
	 * VOID
	 */
	void SetSetting(InputSettingsEnum setting, bool value);
	/**@brief Sets the window size pointers for the input functions
	 * @param[in] width
	 * @param[in] height
	 * @returns
	 * VOID
	 */
	void SetWindowSizePointer(ui32* width, ui32* height);
	/**@brief Sets the window position pointers for the input functions
	 * @param[in] x
	 * @param[in] y
	 * @returns
	 * VOID
	 */
	void SetWindowPositionPointer(ui32* x, ui32* y);

	/**@brief Checks if the key was pressed
	 * @param[in] key
	 * @retval TRUE if the key is pressed
	 * @retval FALSE if the key is not pressed
	 */
	bool IsKeyPressed(const int& key);
	/**@brief checks if the key is down
	 * @param[in] key
	 * @retval TRUE if the key is down
	 * @retval FALSE if the key is not down
	 */
	bool IsKeyDown(const int& key);
	/**@brief Checks if the key was released
	 * @param[in] key
	 * @retval TRUE if the key was released
	 * @retval TRUE if the key was not released
	 */
	bool IsKeyReleased(const int& key);
	/**@brief Converts int coords to float coords
	 * @param[in] state
	 * @param[in] key
	 * @retval TRUE if the given state is valid
	 * @retval FALSE if the given state is not valid
	 */
	bool IsKeyState(const State& state, const int& key);

	/**@brief Checks if the button was pressed
	 * @param[in] button
	 * @retval TRUE if the button was pressed
	 * @retval FALSE if the button was not pressed
	 */
	bool IsMouseButtonPressed(const int& button);
	/**@brief Checks if the button is down
	 * @param[in] button
	 * @retval TRUE if the button is down
	 * @retval FALSE if the button is not down
	 */
	bool IsMouseButtonDown(const int& button);
	/**@brief Checks if the button was released
	 * @param[in] button
	 * @retval TRUE if the button was released
	 * @retval FALSE if the button was not released
	 */
	bool IsMouseButtonReleased(const int& button);
	/**@brief Converts int coords to float coords
	 * @param[in] state
	 * @param[in] button
	 * @retval TRUE if the state is valid
	 * @retval FALSE if the state is not valid
	 */
	bool IsMouseButtonState(const State& state, const int& button);

	/**@brief Checks if is up scrolling
	 * @retval TRUE if is scrolling up
	 * @retval FALSE if is not scrolling up
	 */
	bool IsScrollUp();
	/**@brief Checks if is down scrolling
	 * @retval TRUE if is scrolling down
	 * @retval FALSE if is not scrolling down
	 */
	bool IsScrollDown();
	/**@brief Checks if is left scrolling
	 * @retval TRUE if is scrolling left
	 * @retval FALSE if is not scrolling left
	 */
	bool IsScrollLeft();
	/**@brief Checks if is right scrolling
	 * @retval TRUE if is scrolling right
	 * @retval FALSE if is not scrolling right
	 */
	bool IsScrollRight();

	/**@brief Gets the mouse x position on the window
	 * @returns
	 * Returns the x position of the mouse based on the window as a i32
	 */
	i32 GetMouseX();
	/**@brief Gets the mouse y position on the window
	 * @returns
	 * Returns the y position of the mouse based on the window as a i32
	 */
	i32 GetMouseY();
	/**@brief Gets the mouse x position on the window
	 * @returns
	 * Returns the x position of the mouse based on the window as a f32
	 */
	f32 GetMouseXFloat();
	/**@brief Gets the mouse y position on the window
	 * @returns
	 * Returns the y position of the mouse based on the window as a f32
	 */
	f32 GetMouseYFloat(bool flip = true);

	/**@brief Checks if the window was resized
	 * @retval TRUE if the window was resized
	 * @retval FALSE if the window was not resized
	 */
	bool WasWindowResized();
	/**@brief Checks if the window was moved
	 * @retval TRUE if the window was moved
	 * @retval FALSE if the window was not moved
	 */
	bool WasWindowMoved();
	/**@brief Checks if the window is on move
	 * @retval TRUE if the window in on move
	 * @retval FALSE if the window is not on move
	 */
	bool IsMouseOnMove();

	/**@brief Checks if the mouse entered the window
	 * @retval TRUE if the mouse has entered the window
	 * @retval FALSE if the mouse has not entered the window
	 */
	bool HasCursorEnteredWindow();
	/**@brief Checks if the mouse left the window
	 * @retval TRUE if the mouse has left the window
	 * @retval FALSE if the mouse has not left the window
	 */
	bool HasCursorLeftWindow();

	/**@brief Adds a new file type to the white list for file drops
	 * @param[in] fileEnding
	 * @returns
	 * VOID
	 */
	void SetFileEndingToWhitelist(const char* fileEnding);
	/**@brief Checks if the window has a file drop
	 * @retval TRUE if the window has a file drop
	 * @retval FALSE if the window has not a file drop
	 */
	bool HasFileDrop();
	/**@brief Gets a file drop from the queue
	 * @returns
	 * Returns a FileDrop as a struct
	 */
	FileDrop getFileDrop();

	/**@brief Checks if the window has a char input
	 * @retval TRUE if the window has a char input
	 * @retval FALSE if the window has not a char input
	 */
	bool HasCharInput();
	/**@brief Gets a char input from the queue
	 * @returns
	 * Returns a char input as a ui32
	 */
	ui32 GetCharInput();
	/**@brief Checks if the window has a char input modifier key
	 * @retval TRUE if the window has a char input modifier key
	 * @retval FALSE if the window has not a char input modifier key
	 */
	bool HasCharInputModifierKey();
	/**@brief Gets a char input modifier key from the queue
	 * @returns
	 * Returns char input modifier key from the queue as a i32
	 */
	i32 GetCharInputModifierKey();

	/**@brief Checks if the frame buffer was resized
	 * @retval TRUE if the frame buffer was resized
	 * @retval FALSE if the frame buffer was not resized
	 */
	bool WasFrameBufferResized();
	/**@brief Gets the frame buffer width
	 * @returns
	 * Returns the actual frame buffer with as a i32
	 */
	i32 GetFrameBufferSizeWidth();
	/**@brief Gets the frame buffer height
	 * @returns
	 * Returns the actual frame buffer height as a i32
	 */
	i32 GetFameBufferSizeHeight();

	/**@brief Checks if the window is focused
	 * @retval TRUE if the window is focused
	 * @retval FALSE if the windows is not focused
	 */
	bool IsWindowFocused();

	/**@brief Checks if the window is maximized
	 * @retval TRUE if the window is maximized
	 * @retval FALSE if the window is not maximized
	 */
	bool IsWindowMaximized();
	/**@brief Checks if the window is minimized
	 * @retval TRUE if the window is minimized
	 * @retval FALSE if the window is not minimized
	 */
	bool IsWindowMinimized();
	/**@brief Checks if the window visible
	 * @retval TRUE if the window is visible
	 * @retval FALSE if the window is not visible
	 */
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