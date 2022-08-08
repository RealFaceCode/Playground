#include <gfx/image.h>
#include "core.h"
#include "window/window.h"
#include "window/input.h"
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/renderer.h"
#include "util/hotloader.h"

// ---------- TODO SECTION ----------
//TODO: implement setting save and load for window
//TODO: implement load function for sprite sheet loading
//TODO: implement text rendering
//TODO: implement gui system
//TODO: implement camera
//TODO: change shader to pipeline instead of program
//TODO: implement hot reloading shader
//TODO: |-> buttons
//TODO: |-> sliders
//TODO: |-> loading/progress bar
//TODO: |-> text fields
//TODO: |-> text input fields
//TODO: |-> checkbox
//TODO: scripting support?
//TODO: |-> lua?
//TODO: check UV´s sprite sheet creator
// ---------- TODO SECTION ----------

int main()
{
    Window::Init();

    Window::Window win = Window::WindowBuilder
            .setSize(900, 600)
            .setRGBBufferSize(8, 8, 8)
            .setOpacity(0.9f)
            .setRefreshRate(60)
            .centerWindowOnScreen()
            .setStandartCursor(Window::CrosshairCursor)
            .build("playground");

    win.init();

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

    {
        GFX::SpriteSheetBuilder::AddFile("../assets/images/red_peper.jpg");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/images.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/bricks.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/dirt.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/chiseled_stone_bricks.png");
        GFX::SpriteSheetBuilder::AddFile("../assets/images/chiseled_quartz_block.png");
    }
    auto sheet = GFX::SpriteSheetBuilder::CreateSpriteSheet("../assets/spritesheets/sheet.png", true);

    GFX::ShaderHandler::AddShader("batchShader");
    GFX::ShaderHandler::AddCompileSource("batchShader", "../assets/shader/shader.vert", GL_VERTEX_SHADER);
    GFX::ShaderHandler::AddCompileSource("batchShader", "../assets/shader/shader.frag", GL_FRAGMENT_SHADER);
    GFX::ShaderHandler::BuildShader("batchShader");
    GFX::ShaderHandler::BindShader("batchShader");
    auto* shader = GFX::ShaderHandler::GetShader("batchShader");

    GFX::ImageHandler::AddImage("../assets/images/bricks.png");
    GFX::ImageHandler::AddImage("../assets/images/chiseled_stone_bricks.png");

    float scale = 1.5f;
    float aspect = (float)win.mSettings.width / (float)win.mSettings.height;

    glm::mat4 proj = glm::ortho(-aspect * scale, aspect * scale, -1.0f * scale, 1.0f * scale, -1.0f, 1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
    shader->setUniformMat4("uProj", proj);
    shader->setUniformMat4("uView", view);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    HotLoader::AddFileToWatch("../assets/shader/shader.frag");

    while (win.isWindowValid())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            win.close();
        }

        if(HotLoader::IsModified("../assets/shader/shader.frag"))
        {
            auto* f = HotLoader::GetFile("../assets/shader/shader.frag");
            log_info("");
        }

        shader->bind();
        aspect = (float)win.mSettings.width / (float)win.mSettings.height;
        proj = glm::ortho(-aspect * scale, aspect * scale, -1.0f * scale, 1.0f * scale, -1.0f, 1.0f);
        shader->setUniformMat4("uProj", proj);

        GFX::Renderer::DrawTexturedRectangle({0, 0}, &sheet.mSprites["bricks"], 1, 1);
        GFX::Renderer::DrawTexturedRectangle({0, 1}, &sheet.mSprites["chiseled_stone_bricks"], 1, 1);
        GFX::Renderer::DrawTexturedRectangle({-1.25, 0}, GFX::ImageHandler::GetImage("bricks"), 1, 1);
        GFX::Renderer::DrawTexturedRectangle({-1.25, 1}, GFX::ImageHandler::GetImage("chiseled_stone_bricks"), 1, 1);
        GFX::Renderer::render(*shader);

        Input::Update();
        win.swapBuffers();
        Window::pollEvents();
        HotLoader::CheckFiles();
    }

    win.clear();

    return 0;
}