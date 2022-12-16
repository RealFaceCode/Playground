#include "../../hdr/core.h"
#include "../../hdr/window/window.h"

#ifndef PLAYGROUND_RENDERER_H
#define PLAYGROUND_RENDERER_H

namespace GFX
{
    struct Image;
    struct Sprite;
    struct Shader;
    struct BatchVertex;
    struct BatchHandler;

    namespace Draw
    {
        void Init(Window::Window* win);

        void DrawTriangle(BatchHandler& batchHandler, const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedTriangle(BatchHandler& batchHandler, const glm::vec2& position, const Image* texture, const float& width, const float& height);
        void DrawTexturedTriangle(BatchHandler& batchHandler, const glm::vec2& position, const Sprite* sprite, const float& width, const float& height);
        void DrawRectangle(BatchHandler& batchHandler, const glm::vec2& position, const glm::vec4& color, const float& width, const float& height);
        void DrawTexturedRectangle(BatchHandler& batchHandler, const glm::vec2& position, const Image* texture, const float& width, const float& height);
        void DrawTexturedRectangle(BatchHandler& batchHandler, const glm::vec2& position, const Sprite* sprite, const float& width, const float& height);
        void DrawLine(BatchHandler& batchHandler,
                      const glm::vec2& positionStart,
                      const glm::vec2& positionEnd,
                      const glm::vec4& color,
                      const float& lineWidth);
        void DrawLinedRectangle(BatchHandler& batchHandler,
                                const glm::vec2& position,
                                const glm::vec4& color,
                                const float& width,
                                const float& height,
                                const float& lineWidth);

        void render(BatchHandler& batchHandler, Shader& shader);
    }

    struct GuiSettings
    {
    public:
        float lineWidth = 0.01;
        glm::vec4 windowColor = { 36.0f / 255.0f, 44.0f / 255.0f, 56.0f / 255.0f, 255.0f / 255.0f};
        glm::vec4 lineColor = {22.0f / 255.0f, 2.0f / 255.0f, 94.0f / 255.0f, 255.0f / 255.0f};
    };

    struct Renderer
    {
    public:
        Renderer();
        ~Renderer();
    private:

    };
}
#endif //PLAYGROUND_RENDERER_H
