//
// Created by Kevin-Laptop on 28.07.2022.
//

#include "../../hdr/core.h"
#include "../../hdr/gfx/renderer.h"
#include "../../hdr/gfx/batch.h"
#include "../../hdr/gfx/image.h"

namespace GFX
{
    namespace Renderer
    {
        static glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);

        void DrawTriangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, BatchHandler::defaultImage.mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::defaultImage.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, color, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, color, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, color, glm::vec2{0, 0}, textureIndex}
            };

            BatchHandler::AddToBatch(vertices, 3);
        }

        void DrawTexturedTriangle(const glm::vec2& position, const Image& texture, const float& width, const float& height)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, texture.mId);
                textureIndex =(float)batch->getMapedTextureIndex(texture.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, white, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, glm::vec2{0, 0}, textureIndex}
            };

            BatchHandler::AddToBatch(vertices, 3, texture);
        }

        void DrawTexturedTriangle(const glm::vec2& position, const Sprite& sprite, const float& width, const float& height)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, sprite.mId);
                textureIndex =(float)batch->getMapedTextureIndex(sprite.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, white, sprite.uv0, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, sprite.uv1, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, sprite.uv3, textureIndex}
            };

            BatchHandler::AddToBatch(vertices, 3, sprite.mId);
        }

        void DrawRectangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, BatchHandler::defaultImage.mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::defaultImage.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[6] = {
            	BatchVertex{ glm::vec2{x, y}, color, glm::vec2{0.0f, 1.0f}, textureIndex },
            	BatchVertex{ glm::vec2{x + width, y}, color, glm::vec2{0.0f, 0.0f}, textureIndex },
            	BatchVertex{ glm::vec2{x, y - height}, color, glm::vec2{1.0f, 1.0f}, textureIndex },

                BatchVertex{ glm::vec2{x + width, y}, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                BatchVertex{ glm::vec2{x + width , y - height}, color, glm::vec2{1.0f, 0.0f}, textureIndex },
                BatchVertex{ glm::vec2{x, y - height}, color, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            BatchHandler::AddToBatch(vertices, 6);
        }

        void DrawTexturedRectangle(const glm::vec2& position, const Image& texture, const float& width, const float& height)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, texture.mId);
                textureIndex =(float)batch->getMapedTextureIndex(texture.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[6] = {
                    BatchVertex{glm::vec2{x, y}, glm::vec4{1, 1, 1, 1}, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, glm::vec4{1, 1, 1, 1}, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, glm::vec4{1, 1, 1, 1}, glm::vec2{0, 0}, textureIndex},

                    BatchVertex{ glm::vec2{x + width, y}, glm::vec4{1, 1, 1, 1}, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ glm::vec2{x + width , y - height}, glm::vec4{1, 1, 1, 1}, glm::vec2{1.0f, 0.0f}, textureIndex },
                    BatchVertex{ glm::vec2{x, y - height}, glm::vec4{1, 1, 1, 1}, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            BatchHandler::AddToBatch(vertices, 6);
        }

        void DrawTexturedRectangle(const glm::vec2& position, const Sprite& sprite, const float& width, const float& height)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, sprite.mId);
                textureIndex =(float)batch->getMapedTextureIndex(sprite.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[6] = {
                    BatchVertex{glm::vec2{x, y}, white, sprite.uv0, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, white, sprite.uv1, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, white, sprite.uv3, textureIndex},

                    BatchVertex{ glm::vec2{x + width, y}, white, sprite.uv1, textureIndex },
                    BatchVertex{ glm::vec2{x + width , y - height}, white, sprite.uv2, textureIndex },
                    BatchVertex{ glm::vec2{x, y - height}, white, sprite.uv3, textureIndex }
            };

            BatchHandler::AddToBatch(vertices, 6);
        }

        void DrawLine(const glm::vec2& positionStart,
                      const glm::vec2& positionEnd,
                      const glm::vec4& color,
                      const float& lineWidth)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, BatchHandler::defaultImage.mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::defaultImage.mId);
            }

            glm::vec2 ab = positionEnd - positionStart;

            glm::vec2 ab_perpendicular_1 = { -ab.y, ab.x };
            ab_perpendicular_1 = glm::normalize(ab_perpendicular_1);
            ab_perpendicular_1 *= lineWidth * 0.5f;
            glm::vec2 VERTEX_ONE = positionStart + ab_perpendicular_1;

            glm::vec2 ab_perpendicular_2 = { ab.y, -ab.x };
            ab_perpendicular_2 = glm::normalize(ab_perpendicular_2);
            ab_perpendicular_2 *= lineWidth * 0.5f;
            glm::vec2 VERTEX_TWO = positionStart + ab_perpendicular_2;

            glm::vec2 ba = positionStart - positionEnd;

            glm::vec2 ba_perpendicular_1 = { -ba.y, ba.x };
            ba_perpendicular_1 = glm::normalize(ba_perpendicular_1);
            ba_perpendicular_1 *= lineWidth * 0.5f;
            glm::vec2 VERTEX_THREE = positionEnd + ba_perpendicular_1;

            glm::vec2 ba_perpendicular_2 = { ba.y, -ba.x };
            ba_perpendicular_2 = glm::normalize(ba_perpendicular_2);
            ba_perpendicular_2 *= lineWidth * 0.5f;
            glm::vec2 VERTEX_FOUR = positionEnd + ba_perpendicular_2;

            BatchVertex vertices[6] = {
                    BatchVertex{ VERTEX_ONE, color, glm::vec2{0.0f, 1.0f}, textureIndex },
                    BatchVertex{ VERTEX_TWO, color, glm::vec2{0.0f, 0.0f}, textureIndex },
                    BatchVertex{ VERTEX_FOUR, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ VERTEX_TWO, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ VERTEX_THREE, color, glm::vec2{1.0f, 0.0f}, textureIndex },
                    BatchVertex{ VERTEX_FOUR, color, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            BatchHandler::AddToBatch(vertices, 6);
        }

        void DrawLinedRectangle(const glm::vec2 &position,
                                const glm::vec4 &color,
                                const float &width,
                                const float &height,
                                const float &lineWidth)
        {
            CHECK_INIT_GFX

            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, BatchHandler::defaultImage.mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::defaultImage.mId);
            }

            float w = lineWidth / 2;

            DrawLine({position.x, position.y - w}, {position.x + width, position.y - w}, color, lineWidth);
            DrawLine({position.x, position.y - height + w}, {position.x + width, position.y - height + w}, color, lineWidth);
            DrawLine({position.x + w, position.y}, {position.x + w, position.y - height}, color, lineWidth);
            DrawLine({position.x + width - w, position.y}, {position.x + width - w, position.y - height}, color, lineWidth);
        }

        void render(Shader &shader)
        {
            CHECK_INIT_GFX

            BatchHandler::RenderBatches(shader);
        }

        namespace Gui
        {
        }
    }
}