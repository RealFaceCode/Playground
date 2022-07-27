//
// Created by Kevin-Laptop on 27.07.2022.
//

#include "../../hdr/core.h"

#ifndef PLAYGROUND_RENDERER_H
#define PLAYGROUND_RENDERER_H

namespace GFX
{
    struct Image;

    namespace Renderer
    {
        void Init();

        void DrawTriangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedTriangle(const glm::vec2& position, const Image& texture, const float& width, const float& height);
        void DrawRectangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedRectangle(const glm::vec2& position, const Image& texture, const float& width, const float& height);
        void DrawLine(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedLine(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);

        namespace Gui
        {
        }
    }
}
#endif //PLAYGROUND_RENDERER_H
