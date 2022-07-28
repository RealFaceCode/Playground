//
// Created by Kevin-Laptop on 27.07.2022.
//

#include "../../hdr/core.h"

#ifndef PLAYGROUND_RENDERER_H
#define PLAYGROUND_RENDERER_H

namespace GFX
{
    struct Image;
    struct Shader;

    namespace Renderer
    {

        //struct
        //{
        //};

        void Init();

        void DrawTriangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedTriangle(const glm::vec2& position, const Image& texture, const float& width, const float& height);
        void DrawRectangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedRectangle(const glm::vec2& position, const Image& texture, const float& width, const float& height);
        void DrawLine(const glm::vec2& positionStart,
                      const glm::vec2& positionEnd,
                      const glm::vec4& color,
                      const float& lineWidth,
                      const bool& edge90 = true);

        void render(Shader& shader);

        namespace Gui
        {
        }
    }
}
#endif //PLAYGROUND_RENDERER_H
