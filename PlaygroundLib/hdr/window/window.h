#ifndef WINDOW_H
#define WINDOW_H
#include "../core.h"

namespace Window
{
    /**@brief Sets the save path for the window settings
    * @param[in] dirPath
    * @returns
    * VOID
    */
    void SetSavePathDir(const char* dirPath);
    /**@brief Initialize all window related functions
     * @returns
     * VOID
     */
	void Init();
	/**@brief Cleans the window namespace
    * @returns
    * VOID
    */
    void Cleanup();
    /**@brief Polls all window events
    * @returns
    * VOID
    */
	void pollEvents();

	/**@brief Holds all window settings information*/
	struct Settings
	{
		ui32 width;
		ui32 height;
		bool fullscreen;
		ui32 monitor;
		ui32 videoMode;
		ui32 redBit;
		ui32 greenBit;
		ui32 blueBit;
		f32 opacity;
		ui32 refreshRate;
		ui32 winPosX;
		ui32 winPosY;
		ui32 openGLMajor;
		ui32 openGLMinor;
		const char* fileName;
	};

	/**@brief Holds all information of a monitor*/
	struct Monitor
	{
		ui32 maxWidth;
		ui32 MaxHeight;
		GLFWmonitor* monitor;
		ui8 countVidModes;
		const GLFWvidmode* vidModes;
	};

	/**@brief Defines all supported standard cursor forms*/
	enum CursorForm
	{
		StandardCursor,
		CrosshairCursor,
		HandCursor,
		HResizeCursor,
		VResizeCursor,
		IBeamCursor,
	};

	/**@brief Defines all supported custom cursor types*/
	enum CustomCursorForm
	{
		None,
		Cursor16,
		Cursor32,
		Cursor64
	};

	/**@brief Holds all information of the window and handles it*/
	struct Window
	{
	public:
		GLFWwindow* mHandle = nullptr;
		Settings mSettings	= {};
		std::vector<Monitor> mMonitors;
		GLFWimage mImageCursor{ .width = 0, .height = 0, .pixels = nullptr };
		GLFWcursor* mCursor = nullptr;
	public:
	    /**@brief Initialized the current window
         * @returns
         * VOID
         */
		void init();
		/**@brief Clears the windows and set all values to 0
         * @returns
         * VOID
         */
		void clear();

		//save & load
		/**@brief Saves the settings to the settings file
         * @returns
         * VOID
         */
		void saveSettings();
		/**@brief Loads the settings from the settings file
         * @returns
         * VOID
         */
		void loadSettings();

		//set
		/**@brief Sets the title of the windows
         * @param[in] title
         * @returns
         * VOID
         */
		void setTitle(const char* title);
		/**@brief Sets the size of the windows
         * @param[in] width
         * @param[in] height
         * @returns
         * VOID
         */
		void setSize(const ui32& width, const ui32& height);
		/**@brief Sets the monitor for the window
         * @param[in] monitor
         * @returns
         * VOID
         */
		void setMonitor(const ui32& monitor);
		/**@brief Sets the the video mode for the monitor
         * @param[in] videoMode
         * @returns
         * VOID
         */
		void setVideoMode(const ui32 &videoMode);
		/**@brief Sets the opacity of the window
         * @param[in] opacity
         * @returns
         * VOID
         */
		void setOpacity(const f32& opacity);
		/**@brief Sets the refresh rate of the window
         * @param[in] refreshRate
         * @returns
         * VOID
         */
		void setRefreshrate(const ui32& refreshRate);
		/**@brief Sets the position of the windows
         * @param[in] x
         * @param[in] y
         * @returns
         * VOID
         */
		void setPosition(const ui32& x, const ui32& y);
		/**@brief Sets the cursor position
         * @param[in] x
         * @param[in] y
         * @returns
         * VOID
         */
		void setCursorPosition(const ui32& x, const ui32& y);
		/**@brief Sets the size limits of the windows
         * @param[in] minWidth
         * @param[in] minHeight
         * @param[in] maxWidth
         * @param[in] maxHeight
         * @returns
         * VOID
         */
		void setSizeLimits(const ui32& minWidth, const ui32& minHeight, const ui32& maxWidth, const ui32& maxHeight);

		/**@brief Hides the cursor based on the given boolean
         * @param[in] hide
         * @returns
         * VOID
         */
		void hideCursor(const bool& hide);
		/**@brief Disables or enables the cursor based on the given boolean
         * @param[in] disable
         * @returns
         * VOID
         */
		void disableCursor(const bool& disable);
		/**@brief Hides the window based on the given boolean
         * @param[in] hideWindow
         * @returns
         * VOID
         */
		void hide(const bool& hideWindow);

		/**@brief Sets the input pointers of the window
         * @returns
         * VOID
         */
		void setInputPointer();

		/**@brief Sets the cursor form for the window
         * @param[in] cursorForm
         * @returns
         * VOID
         */
		void setStandardCursor(const CursorForm& cursorForm = CursorForm::StandardCursor);
		/**@brief Sets the custom cursor format for the window
         * @param[in] pixels
         * @param[in] hotX
         * @param[in] hotY
         * @returns
         * VOID
         */
		void setCursor16(const unsigned char* pixels, const ui8& hotX, const ui8& hotY);
		/**@brief Sets the custom cursor format to 16*16 pixel for the window
         * @param[in] pixels
         * @param[in] hotX
         * @param[in] hotY
         * @returns
         * VOID
         */
		void setCursor32(const unsigned char* pixels, const ui8& hotX, const ui8& hotY);
		/**@brief Sets the custom cursor format to 32*32 pixel for the window
         * @param[in] pixels
         * @param[in] hotX
         * @param[in] hotY
         * @returns
         * VOID
         */
		void setCursor64(const unsigned char* pixels, const ui8& hotX, const ui8& hotY);
		/**@brief Sets the custom cursor format to 64*64 pixel for the window
         * @param[in] pixels
         * @param[in] hotX
         * @param[in] hotY
         * @returns
         * VOID
         */

		//get
		/**@brief Gets all available monitor connected to the pc and stores it in the window
         * @returns
         * VOID
         */
		void getAvailableMonitor();
		/**@brief Checks if the window is still valid
         * @retval TRUE if the window is valid
         * @retval FALSE if the window is not valid or is closed
         */
		bool isWindowValid() const;

		//stuff
		/**@brief Highlights the window
         * @returns
         * VOID
         */
		void attention() const;
		/**@brief Maximized the window
         * @returns
         * VOID
         */
		void maximize() const;
		/**@brief Minimized the window
         * @returns
         * VOID
         */
		void minimize() const;
		/**@brief Restores the window
         * @returns
         * VOID
         */
		void restore() const;
		/**@brief Sets the focus on the window
         * @returns
         * VOID
         */
		void focus() const;
		/**@brief Swaps the buffers of the window
         * @returns
         * VOID
         */
		void swapBuffers() const;
		/**@brief Close the window
         * @returns
         * VOID
         */
		void close() const;
	};

	/**@brief Holds all information about how a window should be created and builds the window*/
	struct WindowBuildObj
	{
	private:
		Settings mSettings = {
			.width			= 1024,
			.height			= 768,
			.fullscreen		= false,
			.monitor		= 0,
			.videoMode		= 0,
			.redBit			= 8,
			.greenBit		= 8,
			.blueBit		= 8,
			.opacity		= 1.0f,
			.refreshRate	= 30,
			.winPosX		= 0,
			.winPosY		= 0,
			.openGLMajor	= 4,
			.openGLMinor	= 6,
			.fileName		= "winSettings.node"
		};

		bool mCenter					= false;
		bool mHide						= false;
		bool mDisable					= false;
		bool mSetCursorPos				= false;
		bool mSetCursorForm				= false;
		bool mHideWindow				= false;
		bool mMakeBorderless			= false;
		CustomCursorForm mCustomForm	= None;
		CursorForm mCursorForm			= StandardCursor;
		ui32 mCursorPosX				= 0;
		ui32 mCursorPosY				= 0;
		const unsigned char* mPixels	= nullptr;
		ui8 mHotX						= 0;
		ui8 mHotY						= 0;
		bool mSetLimits					= false;
		ui32 mLimits[4]					= { 0, 0, 0, 0 };

	public:
	    /**@brief Sets the targeted size to the window build settings
         * @param[in] width
         * @param[in] height
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setSize(const ui32& width, const ui32& height);
		/**@brief Sets the option for fullscreen in the window build settings based on the value
         * @param[in] fullscreen
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setFullscreen(const bool& fullscreen);
		/**@brief Sets the targeted monitor to the window build settings
         * @param[in] monitor
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setMonitor(const ui32& monitor);
		/**@brief Sets the targeted video mode to the window build settings
         * @param[in] vMode
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setVideoMode(const ui32& vMode);
		/**@brief Sets the targeted rgb buffer size to the window build settings
         * @param[in] r
         * @param[in] g
         * @param[in] b
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setRGBBufferSize(const ui32& r, const ui32& g, const ui32& b);
		/**@brief Sets the targeted opacity for the window to the window build settings
         * @param[in] opacity
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setOpacity(const f32& opacity);
		/**@brief Sets the targeted refresh rate for the window to the window build settings
         * @param[in] refreshRate
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setRefreshRate(const ui32& refreshRate);
		/**@brief Sets the targeted position for the window to the window build settings
         * @param[in] x
         * @param[in] y
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setWindowPosition(const ui32& x, const ui32& y);
		/**@brief Sets the targeted cursor position to the window build settings
         * @param[in] x
         * @param[in] y
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setCursorPos(const ui32& x, const ui32& y);
		/**@brief Sets the targeted openGL version for the window to the window build settings
         * @param[in] major
         * @param[in] minor
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setOpenGLVersion(const ui32& major, const ui32& minor);
		/**@brief Sets the targeted custom cursor form for the window to the window build settings
         * @param[in] cursorForm
         * @param[in] pixels
         * @param[in] hotX
         * @param[in] hotY
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setWindowCustomCursor(const CustomCursorForm& cursorForm, const ui8* pixels, const ui8& hotX, const ui8& hotY);
		/**@brief Sets the targeted standard cursor fom for the window to the window build settings
         * @param[in] form
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setStandardCursor(const CursorForm& form);
		/**@brief Sets the window size limits to the window build settings
         * @param[in] minWidth
         * @param[in] minHeight
         * @param[in] maxWidth
         * @param[in] maxHeight
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setWindowSizeLimits(const ui32& minWidth, const ui32& minHeight, const ui32& maxWidth, const ui32& maxHeight);
		/**@brief Sets the save file name for the window save file
         * @param[in] fileName
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& setSettingsFileName(const char* fileName);
		/**@brief Centers the window on the monitor
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& centerWindowOnScreen();
		/**@brief Hides the cursor on the window
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& hideCursor();
		/**@brief Hides the window on monitor
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& hideWindow();
		/**@brief Makes the window borderless
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& makeBorderless();
		/**@brief Disables the cursor on the window
         * @returns
         * Returns a WindowBuildObj& to the actual window builder
         */
		WindowBuildObj& disableCursor();
		/**@brief Builds the Window with the given settings and the given title
         * @param[in] Title
         * @returns
         * Returns a new Window
         */
		Window build(const char* title);
	} static WindowBuilder;
};
#endif // !WINDOW_H