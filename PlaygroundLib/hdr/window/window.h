#ifndef WINDOW_H
#define WINDOW_H
#include "../core.h"

namespace Window
{

	void SetSavePathDir(const char* dirPath);
	void Init();
	void pollEvents();

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

	struct Monitor
	{
		ui32 maxWidth;
		ui32 MaxHeight;
		GLFWmonitor* monitor;
		ui8 countVidModes;
		const GLFWvidmode* vidModes;
	};

	enum CursorForm
	{
		StandardCursor,
		CrosshairCursor,
		HandCursor,
		HResizeCursor,
		VResizeCursor,
		IBeamCursor,
	};

	enum CustomCursorForm
	{
		None,
		Cursor16,
		Cursor32,
		Cursor64
	};

	struct Window
	{
	public:
		GLFWwindow* mHandle = nullptr;
		Settings mSettings	= {};
		std::vector<Monitor> mMonitors;
		GLFWimage mImageCursor{ .width = 0, .height = 0, .pixels = nullptr };
		GLFWcursor* mCursor = nullptr;
	public:
		void init();
		void clear();

		//save & load
		void saveSettings();
		void loadSettings();

		//set
		void setTitle(const char* title);
		void setSize(const ui32 width, const ui32 height);
		void setMonitor(const ui32 monitor);
		void setVideoMode(const ui32 videoMode);
		void setOpacity(const f32 opacity);
		void setRefreshrate(const ui32 refreshRate);
		void setPosition(const ui32 x, const ui32 y);
		void setCursorPosition(const ui32 x, const ui32 y);
		void setSizeLimits(ui32 minWidth, ui32 minHeight, ui32 maxWidth, ui32 maxHeight);

		void hideCursor(const bool hide);
		void disableCursor(const bool disable);
		void hide(bool hideWindow);

		void setInputPointer();

		void setStandardCursor(CursorForm cursorForm = CursorForm::StandardCursor);
		void setCursor16(const unsigned char* pixels, ui8 hotX, ui8 hotY);
		void setCursor32(const unsigned char* pixels, ui8 hotX, ui8 hotY);
		void setCursor64(const unsigned char* pixels, ui8 hotX, ui8 hotY);

		//get
		void getAvailableMonitor();
		bool isWindowValid();

		//stuff
		void attention();
		void maximize();
		void minimize();
		void restore();
		void focus();
		void swapBuffers();
		void close();
	};

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
		bool mSetCoursorPos				= false;
		bool mSetCursorForm				= false;
		bool mHideWindow				= false;
		bool mMakeBorderless			= false;
		CustomCursorForm mCustomForm	= None;
		CursorForm mCursorForm			= StandardCursor;
		ui32 mCoursorPosX				= 0;
		ui32 mCoursorPosY				= 0;
		const unsigned char* mPixels	= nullptr;
		ui8 mHotX						= 0;
		ui8 mHotY						= 0;
		bool mSetLimits					= false;
		ui32 mLimits[4]					= { 0, 0, 0, 0 };

	public:
		WindowBuildObj& setSize(const ui32 width, const ui32 height);
		WindowBuildObj& setFullscreen(const bool fullscreen);
		WindowBuildObj& setMonitor(const ui32 monitor);
		WindowBuildObj& setVideoMode(ui32 vMode);
		WindowBuildObj& setRGBBufferSize(const ui32 r, const ui32 g, const ui32 b);
		WindowBuildObj& setOpacity(const f32 opacity);
		WindowBuildObj& setRefreshRate(const ui32 refreshRate);
		WindowBuildObj& setWindowPosition(const ui32 x, const ui32 y);
		WindowBuildObj& setCurserPos(const ui32 x, const ui32 y);
		WindowBuildObj& setOpenGLVersion(const ui32 major, ui32 minor);
		WindowBuildObj& setWindowCustomCursor(CustomCursorForm cursorForm, const unsigned char* pixels,  ui8 hotX, ui8 hotY);
		WindowBuildObj& setStandartCursor(CursorForm form);
		WindowBuildObj& setWindowSizeLimits(ui32 minWidth, ui32 minHeight, ui32 maxWidth, ui32 maxHeight);
		WindowBuildObj& setSettingsFileName(const char* fileName);
		WindowBuildObj& centerWindowOnScreen();
		WindowBuildObj& hideCursor();
		WindowBuildObj& hideWindow();
		WindowBuildObj& makeBorderless();
		WindowBuildObj& disableCursor();
		Window build(const char* title);
	} static WindowBuilder;
};

#endif // !WINDOW_H