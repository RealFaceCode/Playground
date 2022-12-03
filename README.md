#Playground

###Linking and building with Cmake

Example for a project

```Cmake
cmake_minimum_required(VERSION 3.19)
project(Game)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "hdr/*.hpp" "src/*.c" "hdr/*.h")

include_directories("vendor/Playground/PlaygroundLib/hdr")
include_directories("vendor/Playground/PlaygroundLib/vendor/glfw/include")
include_directories("vendor/Playground/PlaygroundLib/vendor/glad")
include_directories("vendor/Playground/PlaygroundLib/vendor/glm/glm")
include_directories("vendor/Playground/PlaygroundLib/vendor/fhandle")
include_directories("vendor/Playground/PlaygroundLib/vendor/stb")

add_executable(Game ${SOURCE_FILES} ${GLAD_FILES} ${FHANDLE_FILES} src/main.cpp)

add_subdirectory(vendor/Playground/PlaygroundLib)
target_link_libraries(Game PlaygroundLib)
```

###Example code

Initialize core functions

```cpp
int main()
{
CoreInit();
MemoryEnableTracking(true);     //optional
```

Building a window with settings

```cpp
    Window::Init();

    Window::Window win = Window::WindowBuilder
            .setSize(900, 600)
            .setRGBBufferSize(8, 8, 8)
            .setOpacity(1.0f)
            .setRefreshRate(60)
            .centerWindowOnScreen()
            .setStandartCursor(Window::CrosshairCursor)
            .setSettingsFileName("window.node")
            .build("playground");

    win.init();
```

Declare witch inputs are gathered and with file ending are allowed to load with a file drop.

```cpp
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
```

initialize the rendering.

```cpp
    GFX::Init();
    GFX::Renderer::Init(&win);
```

Adding files to the sprite sheet builder and creating a sprite sheet.

```cpp
    {
        GFX::SpriteSheetBuilder::AddFile("../assets/images/images.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/bricks.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/dirt.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/chiseled_stone_bricks.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/chiseled_quartz_block.png");
    }
    auto sheet = GFX::SpriteSheetBuilder::CreateSpriteSheet("../assets/spritesheets/sheet.png", true);
```

Creating, building and binding a shader, also get the pointer for the shader.


```cpp
    {
        GFX::ShaderHandler::AddShader("batchShader");
        GFX::ShaderHandler::AddCompileSource("batchShader", "../assets/shader/shader.vert", GL_VERTEX_SHADER);
        GFX::ShaderHandler::AddCompileSource("batchShader", "../assets/shader/shader.frag", GL_FRAGMENT_SHADER);
        GFX::ShaderHandler::BuildShader("batchShader");
        GFX::ShaderHandler::BindShader("batchShader");
    }
    auto* shader = GFX::ShaderHandler::GetShader("batchShader");
```

Add a texture to the image handler.

```cpp
    {
        GFX::ImageHandler::AddImage("../assets/images/bricks.png");
    }
```

 Calculating some stuff for the projection matrix.

```cpp
    float aspect = (float)win.mSettings.width / (float)win.mSettings.height;

    float scale = 0.0075;
    float left = (float)win.mSettings.width / -2.0f * scale;
    float right = (float)win.mSettings.width / 2.0f * scale;
    float bottom = (float)win.mSettings.height / -2.0f * scale;
    float top = (float)win.mSettings.height / 2.0f * scale;
```

Calculating the projection and the view matrix and pushing this to the shader.

```cpp
    glm::mat4 proj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
    shader->setUniformMat4("uProj", proj);
    shader->setUniformMat4("uView", view);
```

Setting glViewport and glClearColor.

```cpp
    glViewport(0, 0, 900, 600);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
```

Starting the mainloop a set exit by pressing the "ESCAPE" key.

```cpp
    while (win.isWindowValid())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            win.close();
        }
```

Binding the shader and calculating the projection matrix and pushing it to the shader.

```cpp
        shader->bind();

        left = (float)win.mSettings.width / -2.0f * scale;
        right = (float)win.mSettings.width / 2.0f * scale;
        bottom = (float)win.mSettings.height / -2.0f * scale;
        top = (float)win.mSettings.height / 2.0f * scale;

        proj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        shader->setUniformMat4("uProj", proj);
```

Drawing a textured rectangle to the window.

```cpp
        GFX::Renderer::DrawTexturedRectangle({win.mSettings.width / -2.0f * scale, win.mSettings.height / 2.0f * scale}, &sheet.mSprites["bricks"], 1, 1);
        GFX::Renderer::render(*shader);
```

Updating the input buffers, window buffers and polling events.

```cpp
        Input::Update();
        win.swapBuffers();
        Window::pollEvents();
```

Project cleanup and checking for memory leaks.

```cpp
    }

    win.clear();
    if(MemoryPrintStack())
    {
        system("pause");
    }
    return 0;
}
```

##Documentation
###Window / WindowBuildObj
Namespace Window
####_Structs_
######Settings
Stores all window related settings.

```cpp
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
```
######Monitor
Stores all infos from a monitor connected to the pc.

```cpp
struct Monitor
{
	ui32 maxWidth;
	ui32 MaxHeight;
	GLFWmonitor* monitor;
	ui8 countVidModes;
	const GLFWvidmode* vidModes;
};
```

####_Enums_
######CursorForm
Defines with standard curse should be used. Default is StandardCursor.

```cpp
enum CursorForm
{
	StandardCursor,
	CrosshairCursor,
	HandCursor,
	HResizeCursor,
	VResizeCursor,
	IBeamCursor,
};
```
######CustomCursorForm
Defines resolution for a custom cursor format.

```cpp
enum CustomCursorForm
{
	None,
	Cursor16,
	Cursor32,
	Cursor64
};
```

####_Functions_
####WindowBuilderObj
######WindowBuildObj& setSize(const ui32, const ui32)
Sets the window dimensions. If the width / height higher as the monitor width / height the targeted width / height is set to max monitor width / height.

```cpp
WindowBuildObj& setSize(const ui32 width, const ui32 height);
```
######WindowBuildObj& setFullscreen(const bool)
Sets the Window to borderless fullscreen. If now monitor or video mode declared, both will be 0. This means first monitor with min resolution.

```cpp
WindowBuildObj& setFullscreen(const bool fullscreen);
```
######WindowBuildObj& setMonitor(const ui32)#
Sets the targeted monitor for fullscreen. If the number below 0 or higher than the amount of monitors connected to the pc it is set to the minimal or maximal number.

```cpp
WindowBuildObj& setMonitor(const ui32 monitor);
```
######WindowBuildObj& setVideoMode(ui32);
Sets the Video mode for the declared monitor. If the targeted video mode higher than the supported video mode the highest video mode will be set.

```cpp
WindowBuildObj& setVideoMode(ui32 vMode);
```
######WindowBuildObj& setRGBBufferSize(const ui32, const ui32, const ui32);
Sets the RGB buffer for the window in bytes .

```cpp
WindowBuildObj& setRGBBufferSize(const ui32 r, const ui32 g, const ui32 b);
```
######WindowBuildObj& setOpacity(const f32);
Sets the opacity from the window. 0.f means invisible amd 1.f means visible.
```cpp
WindowBuildObj& setOpacity(const f32 opacity);
```
######WindowBuildObj& setRefreshRate(const ui32);
Sets the target frames per seconds.

```cpp
WindowBuildObj& setRefreshRate(const ui32 refreshRate);
```
######WindowBuildObj& setWindowPosition(const ui32, const ui32);
Sets the window position on screen.

```cpp
WindowBuildObj& setWindowPosition(const ui32 x, const ui32 y);
```
######WindowBuildObj& setCurserPos(const ui32, const ui32)
Sets the position of the cursor in the window.

```cpp
WindowBuildObj& setCurserPos(const ui32 x, const ui32 y);
```
######WindowBuildObj& setOpenGLVersion(const ui32, ui32)
sets the major and minor version for OpenGL(should be 4.6).

```cpp
WindowBuildObj& setOpenGLVersion(const ui32 major, ui32 minor);
```
######WindowBuildObj& setWindowCustomCursor(CustomCursorForm, const unsigned char*,  ui8, ui8)
Creates a custom cursor.
```
INPUT
    CustomCursorForm cursorForm         defines with resolution the cursor has.
    const unsigned char* pixels         pointer to the pixel data.
    ui8 hotX, ui8 hotY                  defines witch pixel is hot
```

```cpp
WindowBuildObj& setWindowCustomCursor(CustomCursorForm cursorForm, const unsigned char* pixels, ui8 hotX, ui8 hotY);
```
######WindowBuildObj& setStandartCursor(CursorForm)
Sets witch standard cursor is used.

```cpp
WindowBuildObj& setStandartCursor(CursorForm form);
```
######WindowBuildObj& setWindowSizeLimits(ui32, ui32, ui32, ui32)
Sets the window size limitations.

```cpp
WindowBuildObj& setWindowSizeLimits(ui32 minWidth, ui32 minHeight, ui32 maxWidth, ui32 maxHeight);
```
######WindowBuildObj& setSettingsFileName(const char*)
Sets the file name for the window settings. File ending should be .node.

```cpp
WindowBuildObj& setSettingsFileName(const char* fileName);
```
######WindowBuildObj& centerWindowOnScreen()
Center the window on the monitor.

```cpp
WindowBuildObj& centerWindowOnScreen();
```
######WindowBuildObj& hideCursor()
Hides the cursor in the window.

```cpp
WindowBuildObj& hideCursor();
```
######WindowBuildObj& hideWindow()
Hides the window on the monitor.

```cpp
WindowBuildObj& hideWindow();
```
######WindowBuildObj& makeBorderless()
Makes the window borderless.

```cpp
WindowBuildObj& makeBorderless();
```
######WindowBuildObj& disableCoursor()
Disables the cursor

```cpp
WindowBuildObj& disableCursor();
```
######Window build(const char*)
Builds the window with a given title.

```cpp
Window build(const char* title);
```

####Window
######void init()
Initialized general window functions.

```cpp
void init();
```
```cpp
void clear();
```
```cpp
void saveSettings();
```
```cpp
void loadSettings();
```
```cpp
void setTitle(const char* title);
```
```cpp
void setSize(const ui32 width, const ui32 height);
```
```cpp
void setMonitor(const ui32 monitor);
```
```cpp
void setVideoMode(const ui32 videoMode);
```
```cpp
void setOpacity(const f32 opacity);
```
```cpp
void setRefreshrate(const ui32 refreshRate);
```
```cpp
void setPosition(const ui32 x, const ui32 y);
```
```cpp
void setCursorPosition(const ui32 x, const ui32 y);
```
```cpp
void setSizeLimits(ui32 minWidth, ui32 minHeight, ui32 maxWidth, ui32 maxHeight);
```
```cpp
void hideCursor(const bool hide);
```
```cpp
void disableCurser(const bool disable);
```
```cpp
void hide(bool hideWindow);
```
```cpp
void setInputPointer();
```
```cpp
void setStandardCursor(CursorForm cursorForm = CursorForm::StandardCursor);
```
```cpp
void setCursor16(const unsigned char* pixels, ui8 hotX, ui8 hotY);
```
```cpp
void setCursor32(const unsigned char* pixels, ui8 hotX, ui8 hotY);
```
```cpp
void setCursor64(const unsigned char* pixels, ui8 hotX, ui8 hotY);
```
```cpp
void getAvailableMonitor();
```
```cpp
bool isWindowValid();
```
```cpp
void attention();
```
```cpp
void maximize();
```
```cpp
void minimize();
```
```cpp
void restore();
```
```cpp
void focus();
```
```cpp
void swapBuffers();
```
```cpp
void close();
```