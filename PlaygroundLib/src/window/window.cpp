#include "../../hdr/window/window.h"
#include "../../hdr/window/input.h"

namespace Window
{
	static const char* dirSavePath = "data/settings/";

	void SetSavePathDir(const char* dirPath)
	{
		dirSavePath = dirPath;
	}

	void Init() 
	{
		if (!glfwInit())
		{
			log_assert(false, "Failed to init GLFW!");
		}
		glfwSetErrorCallback([](int error, const char* discription) {
			log_fmt_error("GLFW error[%i] '%s'", error, discription);
			}
		);
	}

	void pollEvents()
	{
		glfwPollEvents();
	}

	void Window::init()
	{
		setInputPointer();
	}

	void Window::clear()
	{
		glfwSetCursor(mHandle, nullptr);
		if (mImageCursor.pixels != nullptr)
		{
			delete mImageCursor.pixels;
		}

		mImageCursor.pixels = nullptr;

		if (mCursor)
		{
			glfwDestroyCursor(mCursor);
		}

		if (mHandle)
		{
			glfwDestroyWindow(mHandle);
		}

		for (auto monitor : mMonitors)
		{
			delete monitor.vidModes;
		}
		mMonitors.clear();
	}

	void Window::saveSettings()
	{

	}

	void Window::loadSettings()
	{
		std::string path(dirSavePath);
		path.assign(mSettings.fileName);
		FHandle::Node node = FHandle::Node::loadNode(path.c_str());
		if (!node.empty())
		{
			mSettings.width = node["Window"]["Settings"]["Width"].getAsInt(0);
			mSettings.height = node["Window"]["Settings"]["Height"].getAsInt(0);
		}
	}

	void Window::setTitle(const char* title)
	{
		glfwSetWindowTitle(mHandle, title);
	}

	void Window::setSize(const ui32 width, const ui32 height)
	{
		mSettings.width = width;
		mSettings.height = height;
		glfwSetWindowSize(mHandle, width, height);
	}

	void Window::setMonitor(const ui32 monitor)
	{
		if (monitor >= mMonitors.size())
		{
			log_fmt_warning("Window monitor setting'%i' is greater than the number of monitors'%i'!", monitor, mMonitors.size() -1);
			mSettings.monitor = mMonitors.size() - 1;
		}
		else {
			mSettings.monitor = monitor;
		}

		const GLFWvidmode* vMode = &mMonitors[mSettings.monitor].vidModes[mSettings.videoMode];
		glfwSetWindowMonitor(mHandle, mMonitors[mSettings.monitor].monitor, 0, 0, vMode->width, vMode->height, vMode->refreshRate);
	}

	void Window::setVideoMode(const ui32 videoMode)
	{
		if (videoMode >= mMonitors[mSettings.monitor].countVidModes)
		{
			log_fmt_warning("Window video mode setting'%i' is greater than the number of video modes'%i'!", videoMode, mMonitors[mSettings.monitor].countVidModes);
			mSettings.videoMode = mMonitors[mSettings.monitor].countVidModes - 1;
		}
		else
		{
			mSettings.videoMode = videoMode;
		}
		
		const GLFWvidmode* vMode = &mMonitors[mSettings.monitor].vidModes[mSettings.videoMode];
		glfwSetWindowMonitor(mHandle, mMonitors[mSettings.monitor].monitor, 0, 0, vMode->width, vMode->height, vMode->refreshRate);
	}

	void Window::setOpacity(const f32 opacity)
	{
		float opc = opacity;
		if (opc > 1.0f)
		{
			log_fmt_warning("Window opacity'%f' cannot be greater than 1.0f!", opacity);
			opc = 1.0f;
		}
		else if (opacity < 0.0f)
		{
			log_fmt_warning("Window opacity'%i' cannot be less than 0.0f!", opacity);
			opc = 0.0f;
		}
		mSettings.opacity = opc;
		glfwSetWindowOpacity(mHandle, mSettings.opacity);
	}

	void Window::setRefreshrate(const ui32 refreshRate)
	{
		mSettings.refreshRate = refreshRate;
		const GLFWvidmode* vMode = &mMonitors[mSettings.monitor].vidModes[mSettings.videoMode];
		glfwSetWindowMonitor(mHandle, mMonitors[mSettings.monitor].monitor, 0, 0, vMode->width, vMode->height, vMode->refreshRate);
	}

	void Window::setPosition(const ui32 x, const ui32 y)
	{
		if (x > mMonitors[mSettings.monitor].maxWidth)
		{
			log_fmt_warning("window x position'%i' is larger than the screen resolution in width'%i'!", x, mMonitors[mSettings.monitor].maxWidth);
		}
		if (y > mMonitors[mSettings.monitor].MaxHeight)
		{
			log_fmt_warning("window y position'%i' is larger than the screen resolution in height'%i'!", y, mMonitors[mSettings.monitor].MaxHeight);
		}

		mSettings.winPosX = x;
		mSettings.winPosY = y;
		glfwSetWindowPos(mHandle, mSettings.winPosX, mSettings.winPosY);
	}

	void Window::setCursorPosition(const ui32 x, const ui32 y)
	{
		if (x > mSettings.width)
		{
			log_fmt_warning("Cursor position x is larger than the window with!")
		}

		if (y > mSettings.height)
		{
			log_fmt_warning("Cursor position y is larger than the window with!")
		}

		glfwSetCursorPos(mHandle, x, y);
	}

	void Window::setSizeLimits(ui32 minWidth, ui32 minHeight, ui32 maxWidth, ui32 maxHeight)
	{
		glfwSetWindowSizeLimits(mHandle, minWidth, minHeight, maxWidth, maxHeight);
	}

	void Window::hideCoursor(const bool hide)
	{
		if (hide)
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void Window::disableCourser(const bool disable)
	{
		if (disable)
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(mHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void Window::hide(bool hideWindow)
	{
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

	void Window::setStandartCursor(CursorForm cursorForm)
	{
		if(mCursor)
		{
			glfwDestroyCursor(mCursor);
			mCursor = nullptr;
		}

		int c = GLFW_ARROW_CURSOR;

		switch (cursorForm)
		{
		case CursorForm::StandarCursor:
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
		
		mCursor = glfwCreateStandardCursor(c);
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::setCursor16(const unsigned char* pixels, ui8 hotX, ui8 hotY)
	{
		if (strlen((const char*)pixels) != 16 * 16 * 4)
		{
			log_error("Failed to set glfw cursor! Cursor size is 16 * 16 and 4 * 8 bit for RGBA channels");
			return;
		}

		if (hotX > 15)
		{
			log_fmt_error("Failed to set glfw cursor! hotX'%i' max is 15", hotX);
			return;
		}

		if (hotY > 15)
		{
			log_fmt_error("Failed to set glfw cursor! hotY'%i' max is 15", hotY);
			return;
		}

		mImageCursor.width = 16;
		mImageCursor.height = 16;

		if (mImageCursor.pixels != nullptr)
		{
			delete mImageCursor.pixels;
			mImageCursor.pixels = nullptr;
		}

		mImageCursor.pixels = new unsigned char[16 * 16 * 4];
		memcpy(mImageCursor.pixels, pixels, 16 * 16 * 4);

		if (mCursor)
		{
			glfwDestroyCursor(mCursor);
			mCursor = nullptr;
		}

		mCursor = glfwCreateCursor(&mImageCursor, hotX, hotY);
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::setCursor32(const unsigned char* pixels, ui8 hotX, ui8 hotY)
	{
		if (strlen((const char*)pixels) != 32 * 32 * 4)
		{
			log_error("Failed to set glfw cursor! Cursor size is 32 * 32 and 4 * 8 bit for RGBA channels");
			return;
		}

		if (hotX > 31)
		{
			log_fmt_error("Failed to set glfw cursor! hotX'%i' max is 31", hotX);
			return;
		}

		if (hotY > 31)
		{
			log_fmt_error("Failed to set glfw cursor! hotY'%i' max is 31", hotY);
			return;
		}

		mImageCursor.width = 32;
		mImageCursor.height = 32;

		if (mImageCursor.pixels != nullptr)
		{
			delete mImageCursor.pixels;
			mImageCursor.pixels = nullptr;
		}

		mImageCursor.pixels = new unsigned char[32 * 32 * 4];
		memcpy(mImageCursor.pixels, pixels, 32 * 32 * 4);

		if (mCursor)
		{
			glfwDestroyCursor(mCursor);
			mCursor = nullptr;
		}

		mCursor = glfwCreateCursor(&mImageCursor, hotX, hotY);
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::setCursor64(const unsigned char* pixels, ui8 hotX, ui8 hotY)
	{
		if (strlen((const char*)pixels) != 64 * 64 * 4)
		{
			log_error("Failed to set glfw cursor! Cursor size is 64 * 64 and 4 * 8 bit for RGBA channels");
			return;
		}

		if (hotX > 63)
		{
			log_fmt_error("Failed to set glfw cursor! hotX'%i' max is 63", hotX);
			return;
		}

		if (hotY > 63)
		{
			log_fmt_error("Failed to set glfw cursor! hotY'%i' max is 63", hotY);
			return;
		}

		mImageCursor.width = 64;
		mImageCursor.height = 64;

		if (mImageCursor.pixels != nullptr)
		{
			delete mImageCursor.pixels;
			mImageCursor.pixels = nullptr;
		}

		mImageCursor.pixels = new unsigned char[64 * 64 * 4];
		memcpy(mImageCursor.pixels, pixels, 64 * 64 * 4);

		if (mCursor)
		{
			glfwDestroyCursor(mCursor);
			mCursor = nullptr;
		}

		mCursor = glfwCreateCursor(&mImageCursor, hotX, hotY);
		glfwSetCursor(mHandle, mCursor);
	}

	void Window::getAvailableMonitor()
	{
		i32 countMonitors;
		i32 countVidModes;
		GLFWmonitor** monitors = glfwGetMonitors(&countMonitors);

		for (int i = 0; i < countMonitors; i++)
		{
			Monitor m;
			m.monitor = monitors[i];
			m.vidModes = glfwGetVideoModes(monitors[i], &countVidModes);
			m.countVidModes = countVidModes;
			m.maxWidth = m.vidModes[countVidModes - 1].width;
			m.MaxHeight = m.vidModes[countVidModes - 1].height;
			mMonitors.emplace_back(m);
		}
	}

	bool Window::isWindowValid()
	{
		return !glfwWindowShouldClose(mHandle);
	}

	void Window::attantion()
	{
		glfwRequestWindowAttention(mHandle);
	}

	void Window::maximize()
	{
		glfwMaximizeWindow(mHandle);
	}

	void Window::minimize()
	{
		glfwIconifyWindow(mHandle);
	}

	void Window::restore()
	{
		
		glfwRestoreWindow(mHandle);
	}

	void Window::focus()
	{
		glfwFocusWindow(mHandle);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(mHandle);
		//Todo: fix me i should be somewhere else
		glViewport(0, 0, mSettings.width, mSettings.height);
	}

	void Window::close()
	{
		glfwSetWindowShouldClose(mHandle, true);
	}

	WindowBuildObj& WindowBuildObj::setSize(const ui32 width, const ui32 height)
	{
		mSettings.width = width;
		mSettings.height = height;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setFullscreen(const bool fullscreen)
	{
		mSettings.fullscreen = fullscreen;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setMonitor(const ui32 monitor)
	{
		mSettings.monitor = monitor;
		return *this;
	}
	
	WindowBuildObj& WindowBuildObj::setVideoMode(const ui32 vMode)
	{
		mSettings.videoMode = vMode;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setRGBBufferSize(const ui32 r, const ui32 g, const ui32 b)
	{
		mSettings.redBit	= r;
		mSettings.greenBit	= g;
		mSettings.blueBit	= b;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setOpacity(const f32 opacity)
	{
		mSettings.opacity = opacity;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setRefreshRate(const ui32 refreshRate)
	{
		mSettings.refreshRate = refreshRate;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setWindowPosition(const ui32 x, const ui32 y)
	{
		mSettings.winPosX = x;
		mSettings.winPosY = y;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setCurserPos(const ui32 x, const ui32 y)
	{
		mSetCoursorPos = true;
		mCoursorPosX = x;
		mCoursorPosY = y;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setOpenGLVersion(const ui32 major, ui32 minor)
	{
		mSettings.openGLMajor = major;
		mSettings.openGLMinor = minor;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setWindowCustomCursor(CustomCursorForm cursorForm, const unsigned char* pixels, ui8 hotX, ui8 hotY)
	{
		if (cursorForm == CustomCursorForm::None)
		{
			mSetCursorForm = false;
		}
		else
		{
			mSetCursorForm = true;
			mCustomForm = cursorForm;
			pixels = pixels;
			hotX = hotX;
			hotY = hotY;
		}
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setStandartCursor(CursorForm form)
	{
		mCursorForm = form;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setWindowSizeLimits(ui32 minWidth, ui32 minHeight, ui32 maxWidth, ui32 maxHeight)
	{
		mSetLimits = true;
		mLimits[0] = minWidth;
		mLimits[1] = minHeight;
		mLimits[2] = maxWidth;
		mLimits[3] = maxHeight;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::setSettingsFileName(const char* fileName)
	{
		mSettings.fileName = fileName;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::centerWindowOnScreen()
	{
		mCenter = true;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::hideCoursor()
	{
		mHide = true;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::hideWindow()
	{
		mHideWindow = true;
		return *this;
	}

	WindowBuildObj& WindowBuildObj::makeBorderless()
	{
		mMakeBorderless = true;
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		return *this;
	}

	WindowBuildObj& WindowBuildObj::disableCoursor()
	{
		mDisable = true;
		return *this;
	}

	Window WindowBuildObj::build(const char* title)
	{
		Window win;
		win.mSettings = mSettings;
		win.getAvailableMonitor();
		win.loadSettings();


		if (win.mSettings.monitor >= win.mMonitors.size())
		{
			log_fmt_warning("Window monitor setting'%i' is greater than the number of monitors'%i'!", win.mSettings.monitor, win.mMonitors.size() - 1);
			win.mSettings.monitor = win.mMonitors.size() - 1;
			
		}

		if (win.mSettings.videoMode >= win.mMonitors[win.mSettings.monitor].countVidModes)
		{
			log_fmt_warning("Window video mode setting'%i' is greater than the number of video modes'%i'!", win.mSettings.videoMode, win.mMonitors[win.mSettings.monitor].countVidModes);
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

		if (mMakeBorderless)
		{
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		}

		win.mHandle = glfwCreateWindow(win.mSettings.width, win.mSettings.height, title, monitor, nullptr);
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

		if (mSetCoursorPos)
		{
			win.setCursorPosition(mCoursorPosX, mCoursorPosY);
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
			win.setStandartCursor(mCursorForm);
		}

		if (mHideWindow)
		{
			win.hide(true);
		}

		return win;
	}
};