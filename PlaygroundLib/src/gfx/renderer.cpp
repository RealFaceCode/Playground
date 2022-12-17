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
            //lm::vec2 ab = positionEnd - positionStart;

            //lm::vec2 ab_perpendicular_1 = { -ab.y, ab.x };
            //b_perpendicular_1 = glm::normalize(ab_perpendicular_1);
            //b_perpendicular_1 *= lw;
            //lm::vec2 VERTEX_ONE = positionStart + ab_perpendicular_1;

            //lm::vec2 ab_perpendicular_2 = { ab.y, -ab.x };
            //b_perpendicular_2 = glm::normalize(ab_perpendicular_2);
            //b_perpendicular_2 *= lw;
            //lm::vec2 VERTEX_TWO = positionStart + ab_perpendicular_2;

            //lm::vec2 ba = positionStart - positionEnd;

            //lm::vec2 ba_perpendicular_1 = { -ba.y, ba.x };
            //a_perpendicular_1 = glm::normalize(ba_perpendicular_1);
            //a_perpendicular_1 *= lw;
            //lm::vec2 VERTEX_THREE = positionEnd + ba_perpendicular_1;

            //lm::vec2 ba_perpendicular_2 = { ba.y, -ba.x };
            //a_perpendicular_2 = glm::normalize(ba_perpendicular_2);
            //a_perpendicular_2 *= lw;
            //lm::vec2 VERTEX_FOUR = positionEnd + ba_perpendicular_2;

            f32 wWidth = *GetWindowWidth();
            f32 wHeight = *GetWindowWidth();


            glm::vec2 ab = positionEnd - positionStart;
            glm::vec2 ab_perpendicular = { -ab.y, ab.x };

            ab_perpendicular = glm::normalize(ab_perpendicular);
            ab_perpendicular *= lw;

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
            DrawLine(batchHandler, {position.x, position.y - height + w}, {position.x + width, position.y - height + w}, color, lineWidth);
            DrawLine(batchHandler, {position.x + w, position.y}, {position.x + w, position.y - height}, color, lineWidth);
            DrawLine(batchHandler, {position.x + width - w, position.y}, {position.x + width - w, position.y - height}, color, lineWidth);
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
                .mLineWidth = 0.01,
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
}