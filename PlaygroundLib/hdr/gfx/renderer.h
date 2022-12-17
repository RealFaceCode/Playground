#ifndef PLAYGROUND_RENDERER_H
#define PLAYGROUND_RENDERER_H
#include "../core.h"
#include "../window/window.h"
#include "batch.h"
#include "camera.h"
#include "../util/buffer/string.h"

namespace GFX
{
    struct Image;
    struct Sprite;
    struct Shader;
    struct BatchVertex;

    namespace Draw
    {
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

    struct ButtonEvent
    {
    public:
        bool isClickedLeft;
        bool isClickedRight;
        bool wasReleasedLeft;
        bool wasReleasedRight;
        bool isHovered;
    };

    struct Renderer
    {
    private:
        struct OrthoCamArgs
        {
        public:
            f32 mLeft;
            f32 mRight;
            f32 mTop;
            f32 mBottom;
            f32 mZNear;
            f32 mZFar;
        };

        struct GuiSettings
        {
        public:
            float mLineWidth;
            glm::vec4 mWindowColor;
            glm::vec4 mLineColor;
        };

        struct RendererSettings
        {
        public:
            OrthoCamArgs mOrthoCamArgs;
            GuiSettings mGuiSettings;
            glm::vec4 mClearColor;
        };
    public:
        Renderer();
        ~Renderer();

        void setOrtho(const f32& left, const f32& right,
                      const f32& top, const f32& bottom,
                      const f32& zNear, const f32& zFar);
        void setClearColor(const f32& r, const f32& g, const f32& b, const f32& a);

        ButtonEvent drawButton(const glm::vec2& pos, const glm::vec2& size, const String& text);

        void render();
    private:
        RendererSettings mSettings{};
        BatchHandler mBatchHandler;
        Camera* mCamera;
        Shader* mShader;
    };
}
#endif //PLAYGROUND_RENDERER_H
