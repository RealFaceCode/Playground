#include <OpenGL.h>
#include "../../hdr/core.h"
#include "../../hdr/gfx/renderer.h"
#include "../../hdr/gfx/batch.h"
#include "../../hdr/gfx/image.h"
#include "../../hdr/util/memory.h"
#include "../../hdr/gfx/shader.h"
#include "../../hdr/window/input.h"

namespace GFX
{
    namespace DRAW_2D
    {
        void DrawRectangle(BatchHandler<BatchVertex2D>& bHandler,const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
            const float& x = position.x;
            const float& y = position.y;

            BatchVertex2D v[6] = 
            {
                BatchVertex2D{ glm::vec2{x, y}, color, {}, 0},
                BatchVertex2D{ glm::vec2{x + width, y}, color, {}, 0},
                BatchVertex2D{ glm::vec2{x, y - height}, color, {}, 0},
                BatchVertex2D{ glm::vec2{x + width, y}, color, {}, 0},
                BatchVertex2D{ glm::vec2{x + width , y - height}, color, {}, 0},
                BatchVertex2D{ glm::vec2{x, y - height}, color, {}, 0}
            };

            bHandler.addToBatch(v, 6);
        }

        void DrawTexturedRectangle(BatchHandler<BatchVertex2D>& bHandler, const glm::vec2& position, const Image* texture, const float& width, const float& height)
        {
            if(texture == nullptr)
            {
                return;
            }

            f32 textureIndex = 0;
            {
                Batch<BatchVertex2D>* batch = bHandler.getBatchHasSpaceMatchTexture(3, texture->mId);
                textureIndex = (f32)batch->getMapedTextureIndex(texture->mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex2D v[6] = {
                    BatchVertex2D{glm::vec2{x, y}, {1.0f, 1.0f, 1.0f, 1.0f}, glm::vec2{0, 1}, textureIndex},
                    BatchVertex2D{glm::vec2{x + width, y}, {1.0f, 1.0f, 1.0f, 1.0f}, glm::vec2{1, 1}, textureIndex},
                    BatchVertex2D{glm::vec2{x, y - height}, {1.0f, 1.0f, 1.0f, 1.0f}, glm::vec2{0, 0}, textureIndex},
                    BatchVertex2D{glm::vec2{x + width, y}, {1.0f, 1.0f, 1.0f, 1.0f}, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex2D{glm::vec2{x + width , y - height}, {1.0f, 1.0f, 1.0f, 1.0f}, glm::vec2{1.0f, 0.0f}, textureIndex },
                    BatchVertex2D{glm::vec2{x, y - height}, {1.0f, 1.0f, 1.0f, 1.0f}, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            bHandler.addToBatch(v, 6, texture->mId);
        }

        void DrawTexturedRectangle(BatchHandler<BatchVertex2D>& bHandler, const glm::vec2& position, const Sprite* sprite, const float& width, const float& height)
        {
            if(sprite == nullptr)
            {
                return;
            }

            f32 textureIndex = 0;
            {
                Batch<BatchVertex2D>* batch = bHandler.getBatchHasSpaceMatchTexture(3, sprite->mId);
                textureIndex = (f32)batch->getMapedTextureIndex(sprite->mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex2D vertices[6] = {
                    BatchVertex2D{glm::vec2{x, y}, {1.0f, 1.0f, 1.0f, 1.0f}, sprite->uv0, textureIndex},
                    BatchVertex2D{glm::vec2{x + width, y}, {1.0f, 1.0f, 1.0f, 1.0f}, sprite->uv1, textureIndex},
                    BatchVertex2D{glm::vec2{x, y - height}, {1.0f, 1.0f, 1.0f, 1.0f}, sprite->uv3, textureIndex},
                    BatchVertex2D{ glm::vec2{x + width, y}, {1.0f, 1.0f, 1.0f, 1.0f}, sprite->uv1, textureIndex },
                    BatchVertex2D{ glm::vec2{x + width , y - height}, {1.0f, 1.0f, 1.0f, 1.0f}, sprite->uv2, textureIndex },
                    BatchVertex2D{ glm::vec2{x, y - height}, {1.0f, 1.0f, 1.0f, 1.0f}, sprite->uv3, textureIndex }
            };

            bHandler.addToBatch(vertices, 6, sprite->mId);
        }

        void DrawLine(BatchHandler<BatchVertex2D>& bHandler, const glm::vec2& positionStart,
                      const glm::vec2& positionEnd, const glm::vec4& color, const f32& lineWidth)
        {
            i32 wW = (ui32&)*GFX::GetWindowWidth();
            i32 wH = (ui32&)*GFX::GetWindowHeight();

            glm::vec2 ab = positionEnd - positionStart;
            glm::vec2 ab_perpendicular = { -ab.y, ab.x };
            ab_perpendicular = glm::normalize(ab_perpendicular);

            ab_perpendicular.x *= (lineWidth /(float)wW) * 0.5f;
            ab_perpendicular.y *= (lineWidth / (float)wH) * 0.5f;

            glm::vec2 VERTEX_ONE = positionStart + ab_perpendicular;
            glm::vec2 VERTEX_TWO = positionStart - ab_perpendicular;
            glm::vec2 VERTEX_THREE = positionEnd - ab_perpendicular;
            glm::vec2 VERTEX_FOUR = positionEnd + ab_perpendicular;

            GFX::BatchVertex2D v[6] = {
                GFX::BatchVertex2D{VERTEX_ONE, color, {0, 1}, 0},
                GFX::BatchVertex2D{VERTEX_TWO, color, {0, 0}, 0},
                GFX::BatchVertex2D{VERTEX_THREE, color, {1, 0}, 0},
                GFX::BatchVertex2D{VERTEX_THREE, color, {1, 0}, 0},
                GFX::BatchVertex2D{VERTEX_FOUR, color, {1, 1}, 0},
                GFX::BatchVertex2D{VERTEX_ONE, color, {0, 1}, 0},
            };

            bHandler.addToBatch(v, 6);
        }
    
        void DrawLinedRectangle(BatchHandler<BatchVertex2D>& batchHandler, const glm::vec2 &position,
                                const glm::vec4 &color, const f32 &width,
                                const f32 &height,  f32 &lineWidth)
        {
            f32 wv = (lineWidth / (f32)*GetWindowWidth()) * 0.5f;
            f32 wh = (lineWidth / (f32)*GetWindowHeight()) * 0.5f;
           
            DrawLine(batchHandler, {position.x, position.y - wh}, {position.x + width, position.y - wh}, color, lineWidth);
            DrawLine(batchHandler, {position.x, position.y - height + wh}, {position.x + width, position.y - height + wh}, color, lineWidth);
            DrawLine(batchHandler, {position.x + wv, position.y}, {position.x + wv, position.y - height}, color, lineWidth);
            DrawLine(batchHandler, {position.x + width - wv, position.y}, {position.x + width - wv, position.y - height}, color, lineWidth);
        }
    }

    namespace DRAW_3D
    {

    }

    Renderer::Renderer()
    {
        setDefaultSettings();
        createShader();
    }
    
    void Renderer::setBatch2DSettings(const ui32 mMaxVertices, const ui32& mDrawMode)
    {
        mSettingsBatch2D.mMaxVertices = mMaxVertices;
        mSettingsBatch2D.mDrawMode = mDrawMode;
    }
    void Renderer::setBatch3DSettings(const ui32 mMaxVertices, const ui32& mDrawMode)
    {
        mSettingsBatch3D.mMaxVertices = mMaxVertices;
        mSettingsBatch3D.mDrawMode = mDrawMode;
    }
    
    void Renderer::setBatchGui2DSettings(const ui32 mMaxVertices, const ui32& mDrawMode)
    {
        mSettingsBatchGui2D.mMaxVertices = mMaxVertices;
        mSettingsBatchGui2D.mDrawMode = mDrawMode;
    }
    void Renderer::setGuisettings(const f32& lineWidth, const glm::vec4& windowColor, const glm::vec4& lineColor)
    {
        mGuiSettings = {
            .mLineWidth = lineWidth,
            .mWindowColor = windowColor,
            .mLineColor = lineColor
        };
    }
    ButtonEvent Renderer::drawButton(const glm::vec2 &pos, const glm::vec2 &size, const String &text)
    {
        ButtonEvent bEvent{
            .isClickedLeft = false,
            .isClickedRight = false,
            .wasReleasedLeft = false,
            .wasReleasedRight = false,
            .isHovered = false,
        };
        auto p = pos;
        auto s = size;
        ui32& wWidth = (ui32&)*GetWindowWidth();
        ui32& wHeight = (ui32&)*GetWindowHeight();
        ui32 mx = Input::GetMouseX();
        ui32 my = Input::GetMouseY();
        p.y += s.y;
        p.x /= (float)wWidth;
        p.y /= (float)wHeight;
        s.x /= (float)wWidth;
        s.y /= (float)wHeight;
        if(mx >= (ui32)pos.x && mx <= (ui32)pos.x + (ui32)size.x
        && my >= (ui32)pos.y && my <= (ui32)pos.y + (ui32)size.y)
        {
            bEvent.isHovered = true;
            if(Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
            {
                bEvent.isClickedLeft = true;
            }
            if(Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
            {
                bEvent.isClickedRight = true;
            }
            if(Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
            {
                bEvent.wasReleasedLeft = true;
            }
            if(Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_2))
            {
                bEvent.wasReleasedRight = true;
            }
        }
        DRAW_2D::DrawRectangle(mBatchGui2D, p, mGuiSettings.mWindowColor, s.x, s.y);
        DRAW_2D::DrawLinedRectangle(mBatchGui2D, p, mGuiSettings.mLineColor, s.x, s.y, mGuiSettings.mLineWidth);
        return bEvent;
    }

    void Renderer::render()
    {
        mShader = ShaderHandler::GetShader("Gui");
        mShader->bind();
        glm::mat4 proj = glm::ortho(0, 1, 1, 0, 0, 100);
        mShader->setUniformMat4("uProj", proj);
        mShader->setUniformMat4("uView", glm::mat4(1.0f));
        mBatchGui2D.renderBatches(*mShader);
    }

    void Renderer::setDefaultSettings()
    {
        setBatch2DSettings(1024, GL_DYNAMIC_DRAW);
        setBatch3DSettings(1024, GL_DYNAMIC_DRAW);
        setBatchGui2DSettings(1024, GL_DYNAMIC_DRAW);
        mBatch2D.set(mSettingsBatch2D.mMaxVertices, mSettingsBatch2D.mDrawMode);
        mBatch3D.set(mSettingsBatch3D.mMaxVertices, mSettingsBatch3D.mDrawMode);
        mBatchGui2D.set(mSettingsBatchGui2D.mMaxVertices, mSettingsBatchGui2D.mDrawMode);
        setGuisettings( 1.0f, 
                        {36.0f / 255.0f, 44.0f / 255.0f, 56.0f / 255.0f, 255.0f / 255.0f},
                        {22.0f / 255.0f, 2.0f / 255.0f, 94.0f / 255.0f, 255.0f / 255.0f});
    }

    void Renderer::createShader()
    {
        ShaderHandler::AddShader("Gui");
        ShaderHandler::AddCompileSource("Gui", "../assets/shader/shader.vert", GL_VERTEX_SHADER);
        ShaderHandler::AddCompileSource("Gui", "../assets/shader/shader.frag", GL_FRAGMENT_SHADER);
        ShaderHandler::BuildShader("Gui");
    }
}

/*
namespace GFX
{
    namespace Draw
    {
        static glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);

        void DrawTriangle(BatchHandler& batchHandler, const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
            float textureIndex = 0;
            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, BatchHandler::GetDefaultImage().mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::GetDefaultImage().mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, color, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, color, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, color, glm::vec2{0, 0}, textureIndex}
            };

            batchHandler.addToBatch(vertices, 3);
        }

        void DrawTexturedTriangle(BatchHandler& batchHandler, const glm::vec2& position, const Image* texture, const float& width, const float& height)
        {
            if(texture == nullptr)
            {
                return;
            }

            float textureIndex = 0;
            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, texture->mId);
                textureIndex =(float)batch->getMapedTextureIndex(texture->mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, white, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, glm::vec2{0, 0}, textureIndex}
            };

            batchHandler.addToBatch(vertices, 3, *texture);
        }

        void DrawTexturedTriangle(BatchHandler& batchHandler, const glm::vec2& position, const Sprite* sprite, const float& width, const float& height)
        {
            if(sprite == nullptr)
            {
                return;
            }

            float textureIndex = 0;
            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, sprite->mId);
                textureIndex =(float)batch->getMapedTextureIndex(sprite->mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, white, sprite->uv0, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, sprite->uv1, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, sprite->uv3, textureIndex}
            };

            batchHandler.addToBatch(vertices, 3, sprite->mId);
        }

        void DrawRectangle(BatchHandler& batchHandler, const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
            float textureIndex = 0;
            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, BatchHandler::GetDefaultImage().mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::GetDefaultImage().mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex vertices[6] = {
            	BatchVertex{ glm::vec2{x, y}, color, glm::vec2{0.0f, 1.0f}, textureIndex },
            	BatchVertex{ glm::vec2{x + width, y}, color, glm::vec2{0.0f, 0.0f}, textureIndex },
            	BatchVertex{ glm::vec2{x, y - height}, color, glm::vec2{1.0f, 1.0f}, textureIndex },

                BatchVertex{ glm::vec2{x + width, y}, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                BatchVertex{ glm::vec2{x + width , y - height}, color, glm::vec2{1.0f, 0.0f}, textureIndex },
                BatchVertex{ glm::vec2{x, y - height}, color, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            batchHandler.addToBatch(vertices, 6);
        }

        void DrawTexturedRectangle(BatchHandler& batchHandler, const glm::vec2& position, const Image* texture, const float& width, const float& height)
        {
            if(texture == nullptr)
            {
                return;
            }

            float textureIndex = 0;
            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, texture->mId);
                textureIndex =(float)batch->getMapedTextureIndex(texture->mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex vertices[6] = {
                    BatchVertex{glm::vec2{x, y}, white, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, glm::vec2{0, 0}, textureIndex},

                    BatchVertex{ glm::vec2{x + width, y}, white, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ glm::vec2{x + width , y - height}, white, glm::vec2{1.0f, 0.0f}, textureIndex },
                    BatchVertex{ glm::vec2{x, y - height}, white, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            batchHandler.addToBatch(vertices, 6, texture->mId);
        }

        void DrawTexturedRectangle(BatchHandler& batchHandler, const glm::vec2& position, const Sprite* sprite, const float& width, const float& height)
        {
            if(sprite == nullptr)
            {
                return;
            }

            f32 textureIndex = 0;
            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, sprite->mId);
                textureIndex = (f32)batch->getMapedTextureIndex(sprite->mId);
            }

            f32 x = position.x;
            f32 y = position.y;

            BatchVertex vertices[6] = {
                    BatchVertex{glm::vec2{x, y}, white, sprite->uv0, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, sprite->uv1, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, sprite->uv3, textureIndex},

                    BatchVertex{ glm::vec2{x + width, y}, white, sprite->uv1, textureIndex },
                    BatchVertex{ glm::vec2{x + width , y - height}, white, sprite->uv2, textureIndex },
                    BatchVertex{ glm::vec2{x, y - height}, white, sprite->uv3, textureIndex }
            };

            batchHandler.addToBatch(vertices, 6, sprite->mId);
        }

        void DrawLine(BatchHandler& batchHandler,
                      const glm::vec2& positionStart,
                      const glm::vec2& positionEnd,
                      const glm::vec4& color,
                      const f32& lineWidth)
        {
            float textureIndex = 0;

            {
                Batch* batch = batchHandler.getBatchHasSpaceMatchTexture(3, BatchHandler::GetDefaultImage().mId);
                textureIndex = (f32)batch->getMapedTextureIndex(BatchHandler::GetDefaultImage().mId);
            }

            f32 lw = lineWidth * 0.5f;
            
            f32 wWidth = *GetWindowWidth();
            f32 wHeight = *GetWindowWidth();


            glm::vec2 ab = positionEnd - positionStart;
            glm::vec2 ab_perpendicular = { -ab.y, ab.x };

            ab_perpendicular = glm::normalize(ab_perpendicular);
            ab_perpendicular.x *= lw / wWidth;
            ab_perpendicular.y *= lw / wHeight;

            glm::vec2 VERTEX_ONE = positionStart + ab_perpendicular;
            glm::vec2 VERTEX_TWO = positionStart - ab_perpendicular;
            glm::vec2 VERTEX_THREE = positionEnd - ab_perpendicular;
            glm::vec2 VERTEX_FOUR = positionEnd + ab_perpendicular;

            BatchVertex vertices[6] = {
                    BatchVertex{ VERTEX_ONE, color, glm::vec2{0.0f, 1.0f}, textureIndex },
                    BatchVertex{ VERTEX_TWO, color, glm::vec2{0.0f, 0.0f}, textureIndex },
                    BatchVertex{ VERTEX_FOUR, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ VERTEX_TWO, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ VERTEX_THREE, color, glm::vec2{1.0f, 0.0f}, textureIndex },
                    BatchVertex{ VERTEX_FOUR, color, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            batchHandler.addToBatch(vertices, 6);
        }

        void DrawLinedRectangle(BatchHandler& batchHandler,
                                const glm::vec2 &position,
                                const glm::vec4 &color,
                                const f32 &width,
                                const f32 &height,
                                const f32 &lineWidth)
        {
            f32 w = lineWidth * 0.5f;

            DrawLine(batchHandler, {position.x, position.y - w}, {position.x + width, position.y - w}, color, lineWidth);
            //DrawLine(batchHandler, {position.x, position.y - height + w}, {position.x + width, position.y - height + w}, color, lineWidth);
            //DrawLine(batchHandler, {position.x + w, position.y}, {position.x + w, position.y - height}, color, lineWidth);
            //DrawLine(batchHandler, {position.x + width - w, position.y}, {position.x + width - w, position.y - height}, color, lineWidth);
        }

        void render(BatchHandler& batchHandler, Shader &shader)
        {
            batchHandler.renderBatches(shader);
        }
    }

    Renderer::Renderer()
        : mCamera(nullptr), mShader(nullptr), mBatchHandler()
    {
        mSettings = {
            .mOrthoCamArgs{
                .mLeft      = 0.0f,
                .mRight     = 10.0f,
                .mTop       = 0.0f,
                .mBottom    = -10.0f,
                .mZNear     = 0.0f,
                .mZFar      = 100.0f,
            },
            .mGuiSettings{
                .mLineWidth = 10.f,
                .mWindowColor = {36.0f / 255.0f, 44.0f / 255.0f, 56.0f / 255.0f, 255.0f / 255.0f},
                .mLineColor = {22.0f / 255.0f, 2.0f / 255.0f, 94.0f / 255.0f, 255.0f / 255.0f},
            },
            .mClearColor = {0.2f, 0.2f, 0.2f, 1.0f},
        };

        mCamera = (Camera*)MemReg(new OrthoCamera(mSettings.mOrthoCamArgs.mLeft,
                                                  mSettings.mOrthoCamArgs.mRight,
                                                  mSettings.mOrthoCamArgs.mTop,
                                                  mSettings.mOrthoCamArgs.mBottom,
                                                  mSettings.mOrthoCamArgs.mZNear,
                                                  mSettings.mOrthoCamArgs.mZFar));
        GFX::ShaderHandler::AddShader("batchShader");
        GFX::ShaderHandler::AddCompileSource("batchShader", "../assets/shader/shader.vert", GL_VERTEX_SHADER);
        GFX::ShaderHandler::AddCompileSource("batchShader", "../assets/shader/shader.frag", GL_FRAGMENT_SHADER);
        GFX::ShaderHandler::BuildShader("batchShader");
        GFX::ShaderHandler::BindShader("batchShader");
        mShader = GFX::ShaderHandler::GetShader("batchShader");
    }

    Renderer::~Renderer()
    {
        Free(mCamera);
        mBatchHandler.clear();
    }

    void Renderer::setOrtho(const f32 &left, const f32 &right,
                            const f32 &top, const f32 &bottom,
                            const f32 &zNear,const f32 &zFar)
    {
        mSettings.mOrthoCamArgs =
        {
            .mLeft      = left,
            .mRight     = right,
            .mTop       = top,
            .mBottom    = bottom,
            .mZNear     = zNear,
            .mZFar      = zFar,
        };
        if(mCamera->getMode() == Ortho)
        {
            auto* cam = (OrthoCamera*)mCamera;
            cam->setOrtho(left, right, top, bottom, zNear, zFar);
        }
    }

    void Renderer::setClearColor(const f32 &r, const f32 &g, const f32 &b, const f32 &a)
    {
        mSettings.mClearColor = {r, g, b, a};
    }

    ButtonEvent Renderer::drawButton(const glm::vec2 &pos, const glm::vec2 &size, const String &text)
    {
        ButtonEvent bEvent{
            .isClickedLeft = false,
            .isClickedRight = false,
            .wasReleasedLeft = false,
            .wasReleasedRight = false,
            .isHovered = false,
        };

        auto p = pos;
        auto s = size;
        ui32& wWidth = (ui32&)*GetWindowWidth();
        ui32& wHeight = (ui32&)*GetWindowHeight();
        ui32 mx = Input::GetMouseX();
        ui32 my = Input::GetMouseY();

        p.y *= -1;
        p.x /= (float)wWidth;
        p.y /= (float)wHeight;
        s.x /= (float)wWidth;
        s.y /= (float)wHeight;

        if(mx >= (ui32)pos.x && mx <= (ui32)pos.x + (ui32)size.x
        && my >= (ui32)pos.y && my <= (ui32)pos.y + (ui32)size.y)
        {
            bEvent.isHovered = true;
            if(Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
            {
                bEvent.isClickedLeft = true;
            }
            if(Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
            {
                bEvent.isClickedRight = true;
            }
            if(Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
            {
                bEvent.wasReleasedLeft = true;
            }
            if(Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_2))
            {
                bEvent.wasReleasedRight = true;
            }
        }

        Draw::DrawRectangle(mBatchHandler, p, mSettings.mGuiSettings.mWindowColor, s.x, s.y);
        Draw::DrawLinedRectangle(mBatchHandler, p, mSettings.mGuiSettings.mLineColor, s.x, s.y, mSettings.mGuiSettings.mLineWidth);
        return bEvent;
    }

    void Renderer::render()
    {
        glClearColor(mSettings.mClearColor.r, mSettings.mClearColor.g,
                     mSettings.mClearColor.b, mSettings.mClearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
        mCamera->calculate();
        mShader->bind();
        mShader->setUniformMat4("uProj", mCamera->getProjectionMatrix());
        mShader->setUniformMat4("uView", mCamera->getViewMatrix());
        mBatchHandler.renderBatches(*mShader);
    }
}*/