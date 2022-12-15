#include "../../hdr/window/window.h"
#include "../../hdr/window/input.h"
#include "../../hdr/logger.h"
#include "../../hdr/util/memory.h"
#include <OpenGL.h>

#ifdef _DEBUG
#define CHECK_INIT {if(!INIT){ LOG_ASSERT(false, {}, "Window::Init() was never called!");}};
#else
#define CHECK_INIT
#endif

namespace Window
{
	static const char* dirSavePath = "../assets/settings/";
    static bool INIT = false;

	void SetSavePathDir(const char* dirPath)
	{
		dirSavePath = dirPath;
	}

	void Init() 
	{
		if (!glfwInit())
		{
		    LOG_ASSERT(false, {}, "Failed to init GLFW!");
		}
		glfwSetErrorCallback([](int error, const char* discription) {
		    LOG_ERROR({}, "GLFW error[%i] '%s'", error, discription);
			}
		);
		Input::InitInput();
		INIT = true;
	}

	void Cleanup()
	{
        glfwTerminate();
        Input::CleanInput();
	}

	void pollEvents()
	{
        CHECK_INIT
		glfwPollEvents();
	}



    void Window::init()
	{
        CHECK_INIT
		setInputPointer();
	}

	void Window::clear()
	{
        CHECK_INIT
        saveSettings();

		glfwSetCursor(mHandle, nullptr);
		if (mImageCursor.pixels != nullptr)
		{
			Free(mImageCursor.pixels);
		}
		mImageCursor.pixels = nullptr;

		if (mCursor)
		{
		    glfwDestroyCursor((GLFWcursor*)MemDeReg(mCursor));
		}

		if (mHandle)
		{
			glfwDestroyWindow((GLFWwindow*)MemDeReg(mHandle));
		}

		for (auto monitor : mMonitors)
		{
		    MemDeReg((void*)monitor.vidModes);
			MemDeReg((void*)monitor.monitor);
		}
		mMonitors.clear();
	}

	void Window::saveSettings()
	{
        CHECK_INIT

        std::string path(dirSavePath);
        path.append(mSettings.fileName);

        FHandle::Node node;
        node["Window"]["Settings"]["Size"]              = (i32)mSettings.width;
        node["Window"]["Settings"]["Size"]              = (i32)mSettings.height;
        node["Window"]["Settings"]["OpenGLVersion"]     = (i32)mSettings.openGLMajor;
        node["Window"]["Settings"]["OpenGLVersion"]     = (i32)mSettings.openGLMinor;
        node["Window"]["Settings"]["RefreshRate"]       = (i32)mSettings.refreshRate;
        node["Window"]["Settings"]["Monitor"]           = (i32)mSettings.monitor;
        node["Window"]["Settings"]["VideoMode"]         = (i32)mSettings.videoMode;
        node["Window"]["Settings"]["WinPos"]            = (i32)mSettings.winPosX;
        node["Window"]["Settings"]["WinPos"]            = (i32)mSettings.winPosY;
        node["Window"]["Settings"]["Bits"]              = (i32)mSettings.redBit ;
        node["Window"]["Settings"]["Bits"]              = (i32)mSettings.greenBit;
        node["Window"]["Settings"]["Bits"]              = (i32)mSettings.blueBit;
        node["Window"]["Settings"]["Opacity"]           = mSettings.opacity;
        node.write(path.c_str());

	}

	void Window::loadSettings()
	{
        CHECK_INIT
		std::string path(dirSavePath);
		path.append(mSettings.fileName);
		FHandle::Node node = FHandle::Node::loadNode(path.c_str());
		if (!node.empty())
		{
			mSettings.width         = node["Window"]["Settings"]["Size"].getAsInt(0);
			mSettings.height        = node["Window"]["Settings"]["Size"].getAsInt(1);
			mSettings.openGLMajor   = node["Window"]["Settings"]["OpenGLVersion"].getAsInt(0);
			mSettings.openGLMinor   = node["Window"]["Settings"]["OpenGLVersion"].getAsInt(1);
			mSettings.refreshRate   = node["Window"]["Settings"]["RefreshRate"].getAsInt(0);
			mSettings.monitor       = node["Window"]["Settings"]["Monitor"].getAsInt(0);
			mSettings.videoMode     = node["Window"]["Settings"]["VideoMode"].getAsInt(0);
			mSettings.winPosX       = node["Window"]["Settings"]["WinPos"].getAsInt(0);
			mSettings.winPosY       = node["Window"]["Settings"]["WinPos"].getAsInt(1);
			mSettings.redBit        = node["Window"]["Settings"]["Bits"].getAsInt(0);
			mSettings.greenBit      = node["Window"]["Settings"]["Bits"].getAsInt(1);
			mSettings.blueBit       = node["Window"]["Settings"]["Bits"].getAsInt(2);
			mSettings.opacity       = node["Window"]["Settings"]["Opacity"].getAsInt(0);
		}
	}

	void Window::setTitle(const char* title)
	{
        CHECK_INIT
		glfwSetWindowTitle(mHandle, title);
	}

	void Window::setSize(const ui32& width, const ui32& height)
	{
        CHECK_INIT
		mSettings.width = width;
		mSettings.height = height;
		glfwSetWindowSize(mHandle, (i32)width, (i32)height);
	}

	void Window::setMonitor(const ui32& monitor)
	{
        CHECK_INIT
		if (monitor >= mMonitors.size())
		{
		    LOG_WARNING({}, "Window monitor setting'%i' is greater than the number of monitors'%i'!", monitor, mMonitors.size() -1);
			mSettings.monitor = mMonitors.size() - 1;
		}
		else {
			mSettings.monitor = monitor;
		}

		const GLFWvidmode* vMode = &mMonitors[mSettings.monitor].vidModes[mSettings.videoMode];
		glfwSetWindowMonitor(mHandle, mMonitors[mSettings.monitor].monitor, 0, 0, vMode->width, vMode->height, vMode->refreshRate);
	}

	void Window::setVideoMode(const ui32& videoMode)
	{
        CHECK_INIT
		if (videoMode >= mMonitors[mSettings.monitor].countVidModes)
		{
		    LOG_WARNING({},
                        "Window video mode setting'%i' is greater than the number of video modes'%i'!",
                        videoMode, mMonitors[mSettings.monitor].countVidModes);
			mSettings.videoMode = mMonitors[mSettings.monitor].countVidModes - 1;
		}
		else
		{
			mSettings.videoMode = videoMode;
		}
		
		const GLFWvidmode* vMode = &mMonitors[mSettings.monitor].vidModes[mSettings.videoMode];
		glfwSetWindowMonitor(mHandle, mMonitors[mSettings.monitor].monitor, 0, 0, vMode->width, vMode->height, vMode->refreshRate);
	}

	void Window::setOpacity(const f32& opacity)
	{
        CHECK_INIT
		float opc = opacity;
		if (opc > 1.0f)
		{
		    LOG_WARNING({}, "Window opacity'%f' cannot be greater than 1.0f!", opacity);
			opc = 1.0f;
		}
		else if (opacity < 0.0f)
		{
		    LOG_WARNING({}, "Window opacity'%f' cannot be less than 1.0f!", opacity);
			opc = 0.0f;
		}
		mSettings.opacity = opc;
		glfwSetWindowOpacity(mHandle, mSettings.opacity);
	}

	void Window::setRefreshrate(const ui32& refreshRate)
	{
        CHECK_INIT
		mSettings.refreshRate = refreshRate;
		const GLFWvidmode* vMode = &mMonitors[mSettings.monitor].vidModes[mSettings.videoMode];
		glfwSetWindowMonitor(mHandle, mMonitors[mSettings.monitor].monitor, 0, 0, vMode->width, vMode->height, vMode->refreshRate);
	}

	void Window::setPosition(const ui32& x, const ui32& y)
	{
        CHECK_INIT
		if (x > mMonitors[mSettings.monitor].maxWidth)
		{
		    LOG_WARNING({},
                        "window x position'%i' is larger than the screen resolution in width'%i'!",
                        x, mMonitors[mSettings.monitor].maxWidth);
		}
		if (y > mMonitors[mSettings.monitor].MaxHeight)
		{
		    LOG_WARNING({},
                        "window y position'%i' is larger than the screen resolution in height'%i'!",
                        y, mMonitors[mSettings.monitor].MaxHeight);
		}

		mSettings.winPosX = x;
		mSettings.winPosY = y;
		glfwSetWindowPos(mHandle, (i32)mSettings.winPosX, (i32)mSettings.winPosY);
	}

	void Window::setCursorPosition(const ui32& x, const ui32& y)
	{
        CHECK_INIT
		if (x > mSettings.width)
		{
		    LOG_WARNING({}, "Cursor position x is larger than the window with!");
		}

		if (y > mSettings.height)
		{
		    LOG_WARNING({}, "Cursor position y is larger than the window with!");
		}

		glfwSetCursorPos(mHandle, x, y);
	}

	void Window::setSizeLimits(const ui32& minWidth, const ui32& minHeight, const ui32& maxWidth, const ui32& maxHeight)
	{
        CHECK_INIT
		glfwSetWindowSizeLimits(mHandle, (i32)minWidth, (i32)minHeight, (i32)maxWidth, (i32)maxHeight);
	}

	void Window::hideCursor(const bool& hide)
	{
        CHECK_INIT
		if (hide)
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void Window::disableCursor(const bool& disable)
	{
        CHECK_INIT
		if (disable)
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void Window::hide(const bool& hideWindow)
	{
        CHECK_INIT
		if (hideWindow)
		{
			glfwHideWindow(mHandle);
		}
		else
		{
			glfwShowWindow(mHandle);
		}
	}

	void Window::setInputPointer()
	{
		Input::SetWindowSizePointer(&mSettings.width, &mSettings.height);
		Input::SetWindowPositionPointer(&mSettings.winPosX, &mSettings.winPosY);
	}

	void Window::setStandardCursor(const CursorForm& cursorForm)
	{
        CHECK_INIT
		if(mCursor)
		{
		    glfwDestroyCursor((GLFWcursor*)MemDeReg(mCursor));
			mCursor = nullptr;
		}

		int c = GLFW_ARROW_CURSOR;

		switch (cursorForm)
		{
		case CursorForm::StandardCursor:
			c = GLFW_ARROW_CURSOR;
			break;
		case CursorForm::CrosshairCursor:
			c = GLFW_CROSSHAIR_CURSOR;
			break;
		case CursorForm::HandCursor:
			c = GLFW_HAND_CURSOR;
			break;
		case CursorForm::HResizeCursor:
			c = GLFW_HRESIZE_CURSOR;
			break;
		case CursorForm::VResizeCursor:
			c = GLFW_VRESIZE_CURSOR;
			break;
		case CursorForm::IBeamCursor:
			c = GLFW_IBEAM_CURSOR;
			break;
		}
		
		mCursor = (GLFWcursor*)MemReg(glfwCreateStandardCursor(c));
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::setCursor16(const unsigned char* pixels, const ui8& hotX, const ui8& hotY)
	{
        CHECK_INIT
		if (strlen((const char*)pixels) != 16 * 16 * 4)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! Cursor size is 16 * 16 and 4 * 8 bit for RGBA channels");
			return;
		}

		if (hotX > 15)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! hotX'%i' max is 15", hotX);
			return;
		}

		if (hotY > 15)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! hotY'%i' max is 15", hotY);
			return;
		}

		mImageCursor.width = 16;
		mImageCursor.height = 16;

		if (mImageCursor.pixels != nullptr)
		{
			Free(mImageCursor.pixels);
			mImageCursor.pixels = nullptr;
		}

		mImageCursor.pixels = (unsigned char*)Malloc(16 * 16 * 4 * sizeof(unsigned char));
		memcpy(mImageCursor.pixels, pixels, 16 * 16 * 4);

		if (mCursor)
		{
		    glfwDestroyCursor((GLFWcursor*)MemDeReg(mCursor));
			mCursor = nullptr;
		}

		mCursor = (GLFWcursor*)MemReg(glfwCreateCursor(&mImageCursor, hotX, hotY));
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::setCursor32(const unsigned char* pixels, const ui8& hotX, const ui8& hotY)
	{
        CHECK_INIT
		if (strlen((const char*)pixels) != 32 * 32 * 4)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! Cursor size is 32 * 32 and 4 * 8 bit for RGBA channels");
			return;
		}

		if (hotX > 31)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! hotX'%i' max is 31", hotX);
			return;
		}

		if (hotY > 31)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! hotY'%i' max is 31", hotY);
			return;
		}

		mImageCursor.width = 32;
		mImageCursor.height = 32;

		if (mImageCursor.pixels != nullptr)
		{
			Free(mImageCursor.pixels);
			mImageCursor.pixels = nullptr;
		}

		mImageCursor.pixels = (unsigned char*)Malloc(32 * 32 * 4 * sizeof(unsigned char));
		memcpy(mImageCursor.pixels, pixels, 32 * 32 * 4);

		if (mCursor)
		{
		    glfwDestroyCursor((GLFWcursor*)MemDeReg(mCursor));
			mCursor = nullptr;
		}

		mCursor = (GLFWcursor*)MemReg(glfwCreateCursor(&mImageCursor, hotX, hotY));
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::setCursor64(const unsigned char* pixels, const ui8& hotX, const ui8& hotY)
	{
        CHECK_INIT
		if (strlen((const char*)pixels) != 64 * 64 * 4)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! Cursor size is 64 * 64 and 4 * 8 bit for RGBA channels");
			return;
		}

		if (hotX > 63)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! hotX'%i' max is 63", hotX);
			return;
		}

		if (hotY > 63)
		{
		    LOG_ERROR({}, "Failed to set glfw cursor! hotY'%i' max is 63", hotY);
			return;
		}

		mImageCursor.width = 64;
		mImageCursor.height = 64;

		if (mImageCursor.pixels != nullptr)
		{
			Free(mImageCursor.pixels);
			mImageCursor.pixels = nullptr;
		}

		mImageCursor.pixels = (unsigned char*)Malloc(64 * 64 * 4 * sizeof(unsigned char));
		memcpy(mImageCursor.pixels, pixels, 64 * 64 * 4);

		if (mCursor)
		{
		    glfwDestroyCursor((GLFWcursor*)MemDeReg(mCursor));
			mCursor = nullptr;
		}

		mCursor = (GLFWcursor*)MemReg(glfwCreateCursor(&mImageCursor, hotX, hotY));
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::getAvailableMonitor()
	{
        CHECK_INIT
		i32 countMonitors;
		i32 countVidModes;
		GLFWmonitor** monitors = glfwGetMonitors(&countMonitors);

		for (int i = 0; i < countMonitors; i++)
		{
			Monitor m;
			m.monitor = (GLFWmonitor*)MemReg((void*)monitors[i]);
			m.vidModes = (GLFWvidmode*)MemReg((void*)glfwGetVideoModes(monitors[i], &countVidModes));
			m.countVidModes = countVidModes;
			m.maxWidth = m.vidModes[countVidModes - 1].width;
			m.MaxHeight = m.vidModes[countVidModes - 1].height;
			mMonitors.emplace_back(m);
		}
	}

	bool Window::isWindowValid() const
	{
        CHECK_INIT
		return !glfwWindowShouldClose(mHandle);
	}

	void Window::attention() const
	{
        CHECK_INIT
		glfwRequestWindowAttention(mHandle);
	}

	void Window::maximize() const
	{
        CHECK_INIT
		glfwMaximizeWindow(mHandle);
	}

	void Window::minimize() const
	{
        CHECK_INIT
		glfwIconifyWindow(mHandle);
	}

	void Window::restore() const
	{
        CHECK_INIT
		glfwRestoreWindow(mHandle);
	}

	void Window::focus() const
	{
        CHECK_INIT
		glfwFocusWindow(mHandle);
	}

	void Window::swapBuffers() const
	{
        CHECK_INIT
		glfwSwapBuffers(mHandle);
	}

	void Window::close() const
	{
        CHECK_INIT
		glfwSetWindowShouldClose(mHandle, true);
	}

	WindowBuildObj& WindowBuildObj::setSize(const ui32& width, const ui32& height)
	{
        CHECK_INIT
		mSettings.width = width;
		mSettings.height = height;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setFullscreen(const bool& fullscreen)
	{
        CHECK_INIT
		mSettings.fullscreen = fullscreen;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setMonitor(const ui32& monitor)
	{
        CHECK_INIT
		mSettings.monitor = monitor;
		return *this;
	}
	
	WindowBuildObj& WindowBuildObj::setVideoMode(const ui32& vMode)
	{
        CHECK_INIT
		mSettings.videoMode = vMode;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setRGBBufferSize(const ui32& r, const ui32& g, const ui32& b)
	{
        CHECK_INIT
		mSettings.redBit	= r;
		mSettings.greenBit	= g;
		mSettings.blueBit	= b;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setOpacity(const f32& opacity)
	{
        CHECK_INIT
		mSettings.opacity = opacity;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setRefreshRate(const ui32& refreshRate)
	{
        CHECK_INIT
		mSettings.refreshRate = refreshRate;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setWindowPosition(const ui32& x, const ui32& y)
	{
        CHECK_INIT
		mSettings.winPosX = x;
		mSettings.winPosY = y;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setCursorPos(const ui32& x, const ui32& y)
	{
        CHECK_INIT
		mSetCursorPos = true;
		mCursorPosX = x;
		mCursorPosY = y;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setOpenGLVersion(const ui32& major, const ui32& minor)
	{
        CHECK_INIT
		mSettings.openGLMajor = major;
		mSettings.openGLMinor = minor;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setWindowCustomCursor(const CustomCursorForm& cursorForm, const unsigned char* pixels, const ui8& hotX, const ui8& hotY)
	{
        CHECK_INIT
		if (cursorForm == CustomCursorForm::None)
		{
			mSetCursorForm = false;
		}
		else
		{
			mSetCursorForm = true;
			mCustomForm = cursorForm;
			mPixels = pixels;
			mHotX = hotX;
			mHotY = hotY;
		}
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setStandardCursor(const CursorForm& form)
	{
        CHECK_INIT
		mCursorForm = form;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setWindowSizeLimits(const ui32& minWidth, const ui32& minHeight, const ui32& maxWidth, const ui32& maxHeight)
	{
        CHECK_INIT
		mSetLimits = true;
		mLimits[0] = minWidth;
		mLimits[1] = minHeight;
		mLimits[2] = maxWidth;
		mLimits[3] = maxHeight;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setSettingsFileName(const char* fileName)
	{
        CHECK_INIT
		mSettings.fileName = fileName;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::centerWindowOnScreen()
	{
        CHECK_INIT
		mCenter = true;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::hideCursor()
	{
        CHECK_INIT
		mHide = true;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::hideWindow()
	{
        CHECK_INIT
		mHideWindow = true;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::makeBorderless()
	{
        CHECK_INIT
		mMakeBorderless = true;
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		return *this;
	}

	WindowBuildObj& WindowBuildObj::disableCursor()
	{
        CHECK_INIT
		mDisable = true;
		return *this;
	}

	Window WindowBuildObj::build(const char* title)
	{
        CHECK_INIT
		Window win;
		win.mSettings = mSettings;
		win.getAvailableMonitor();
		win.loadSettings();


		if (win.mSettings.monitor >= win.mMonitors.size())
		{
		    LOG_WARNING({},
                        "Window monitor setting'%i' is greater than the number of monitors'%i'!",
                        win.mSettings.monitor, win.mMonitors.size() - 1);
		    win.mSettings.monitor = win.mMonitors.size() - 1;
		}

		if (win.mSettings.videoMode >= win.mMonitors[win.mSettings.monitor].countVidModes)
		{
		    LOG_WARNING({},
                        "Window video mode setting'%i' is greater than the number of video modes'%i'!",
                        win.mSettings.videoMode, win.mMonitors[win.mSettings.monitor].countVidModes);
		    win.mSettings.videoMode = win.mMonitors[win.mSettings.monitor].countVidModes - 1;
		}

		GLFWmonitor* monitor = nullptr;

		if (mSettings.fullscreen)
		{
			monitor = win.mMonitors[win.mSettings.monitor].monitor;
			const GLFWvidmode* vidMode = &win.mMonitors[win.mSettings.monitor].vidModes[win.mSettings.videoMode];
			win.mSettings.width = vidMode->width;
			win.mSettings.height = vidMode->height;

			glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
		}
		else
		{
			glfwWindowHint(GLFW_RED_BITS, win.mSettings.redBit);
			glfwWindowHint(GLFW_GREEN_BITS, win.mSettings.greenBit);
			glfwWindowHint(GLFW_BLUE_BITS, win.mSettings.blueBit);
			glfwWindowHint(GLFW_REFRESH_RATE, win.mSettings.refreshRate);
		}

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mSettings.openGLMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mSettings.openGLMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (mMakeBorderless)
		{
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		}

		win.mHandle = (GLFWwindow*)MemReg(glfwCreateWindow(win.mSettings.width, win.mSettings.height, title, monitor, nullptr));
		glfwMakeContextCurrent(win.mHandle);

		//calbacks
		{
			glfwSetKeyCallback(win.mHandle, Input::glfwKeyCallback);
			glfwSetCharCallback(win.mHandle, Input::glfwCharacterCallback);
			glfwSetCharModsCallback(win.mHandle, Input::glfwCharModsCallback);
			glfwSetDropCallback(win.mHandle, Input::glfwDropCallback);
			glfwSetCursorEnterCallback(win.mHandle, Input::glfwCursorEnterCallback);
			glfwSetCursorPosCallback(win.mHandle, Input::glfwCursorPositionCallback);
			glfwSetFramebufferSizeCallback(win.mHandle, Input::glfwFramebufferSizeCallback);
			glfwSetJoystickCallback(Input::glfwJoystickCallback);
			glfwSetMonitorCallback(Input::glfwMonitorCallback);
			glfwSetMouseButtonCallback(win.mHandle, Input::glfwMouseButtonCallback);
			glfwSetScrollCallback(win.mHandle, Input::glfwScrollCallback);
			glfwSetWindowContentScaleCallback(win.mHandle, Input::glfwWindowContentScaleCallback);
			glfwSetWindowCloseCallback(win.mHandle, Input::glfwWindowCloseCallback);
			glfwSetWindowFocusCallback(win.mHandle, Input::glfwWindowFocusCallback);
			glfwSetWindowMaximizeCallback(win.mHandle, Input::glfwWindowMaximizeCallback);
			glfwSetWindowPosCallback(win.mHandle, Input::glfwWindowPosCallback);
			glfwSetWindowRefreshCallback(win.mHandle, Input::glfwWindowRefreshCallback);
			glfwSetWindowSizeCallback(win.mHandle, Input::glfwWindowSizeCallback);
			glfwSetWindowIconifyCallback(win.mHandle, Input::glfwIconifyCallback);
		}

		if (mHide)
		{
			glfwSetInputMode(win.mHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		if (mDisable)
		{
			glfwSetInputMode(win.mHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		if (mSetCursorPos)
		{
			win.setCursorPosition(mCursorPosX, mCursorPosY);
		}

		win.setOpacity(win.mSettings.opacity);

		if (mCenter)
		{
			ui32 maxWidth = win.mMonitors[win.mSettings.monitor].maxWidth;
			ui32 maxHeight = win.mMonitors[win.mSettings.monitor].MaxHeight;
			ui32 width = win.mSettings.width;
			ui32 height = win.mSettings.height;
			ui32 x = ((maxWidth / 2) - (width / 2));
			ui32 y = ((maxHeight / 2) - (height / 2));
			win.mSettings.winPosX = x;
			win.mSettings.winPosY = y;
			glfwSetWindowPos(win.mHandle, x, y);
		}
		else
		{
			win.setPosition(win.mSettings.winPosX, win.mSettings.winPosY);
		}

		if (mSetLimits)
		{
			win.setSizeLimits(mLimits[0], mLimits[1], mLimits[2], mLimits[3]);
		}

		if (mSetCursorForm)
		{
			switch (mCustomForm)
			{
			case CustomCursorForm::Cursor16:
				win.setCursor16(mPixels, mHotX, mHotY);
				break;
			case CustomCursorForm::Cursor32:
				win.setCursor32(mPixels, mHotX, mHotY);
				break;
			case CustomCursorForm::Cursor64:
				win.setCursor64(mPixels, mHotX, mHotY);
				break;
			}
		}
		else
		{
			win.setStandardCursor(mCursorForm);
		}

		if (mHideWindow)
		{
			win.hide(true);
		}

		return win;
	}
};