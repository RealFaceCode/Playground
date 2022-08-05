//
// Created by Kevin-Laptop on 27.07.2022.
//

#include "../../hdr/core.h"

#ifndef PLAYGROUND_RENDERER_H
#define PLAYGROUND_RENDERER_H

namespace GFX
{
    struct Image;
    struct Sprite;
    struct Shader;

    namespace Renderer
    {
        void Init();

        void DrawTriangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedTriangle(const glm::vec2& position, const Image* texture, const float& width, const float& height);
        void DrawTexturedTriangle(const glm::vec2& position, const Sprite* sprite, const float& width, const float& height);
        void DrawRectangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedRectangle(const glm::vec2& position, const Image* texture, const float& width, const float& height);
        void DrawTexturedRectangle(const glm::vec2& position, const Sprite* sprite, const float& width, const float& height);
        void DrawLine(const glm::vec2& positionStart,
                      const glm::vec2& positionEnd,
                      const glm::vec4& color,
                      const float& lineWidth);
        void DrawLinedRectangle(const glm::vec2& position,
                                const glm::vec4& color,
                                const float& width,
                                const float& height,
                                const float& lineWidth);

        void render(Shader& shader);

        namespace Gui
        {
            struct GuiSettings
            {
            public:
                float lineWidth = 0.01;
                glm::vec4 windowColor = { 36.0f, 44.0f, 56.0f, 255.0f};
                glm::vec4 lineColor = {22.0f, 2.0f, 94.0f, 255.0f};
            };

            struct GuiObject
            {
            public:
                GuiSettings mGuiSettings;

            public:
                bool DrawButton(const ui32& x, const ui32& y,
                                const ui32& width, const ui32& height,
                                const char* text);
                bool DrawButton(const ui32& x, const ui32& y,
                                const ui32& width, const ui32& height,
                                const Image& image, const char* text);
            };

            GuiObject* CreateGuiObject();
        }
    }
}
#endif //PLAYGROUND_RENDERER_H
