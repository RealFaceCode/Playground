//
// Created by Kevin-Laptop on 28.07.2022.
//

#include "../../hdr/core.h"
#include "../../hdr/gfx/renderer.h"
#include "../../hdr/gfx/batch.h"

namespace GFX
{
    namespace Renderer
    {

        void DrawTriangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
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
            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, texture.mId);
                textureIndex =(float)batch->getMapedTextureIndex(texture.mId);
            }

            float x = position.x;
            float y = position.y;

            BatchVertex vertices[3] = {
                    BatchVertex{glm::vec2{x, y}, glm::vec4{1, 1, 1, 1}, glm::vec2{0, 1}, textureIndex},
                    BatchVertex{glm::vec2{x + width, y}, glm::vec4{1, 1, 1, 1}, glm::vec2{1, 1}, textureIndex},
                    BatchVertex{glm::vec2{x, y - height}, glm::vec4{1, 1, 1, 1}, glm::vec2{0, 0}, textureIndex}
            };

            BatchHandler::AddToBatch(vertices, 3, texture);
        }

        void DrawRectangle(const glm::vec2& position, const glm::vec4& color, const float& width, const float& height)
        {
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

        void DrawLine(const glm::vec2& positionStart,
                      const glm::vec2& positionEnd,
                      const glm::vec4& color,
                      const float& lineWidth,
                      const bool& edge90)
        {
            float textureIndex = 0;

            {
                Batch* batch = BatchHandler::GetBatchHasSpaceMatchTexture(3, BatchHandler::defaultImage.mId);
                textureIndex =(float)batch->getMapedTextureIndex(BatchHandler::defaultImage.mId);
            }

            float x1 = positionStart.x;
            float y1 = positionStart.y;
            float x2 = positionEnd.x;
            float y2 = positionEnd.y;
            float w = lineWidth;
            float move1 = 0;
            float move2 = 0;
            if(edge90)
            {
                float dif = y2 - y1;
                move1 = (dif * lineWidth);
            }
            if(x1 == x2)
            {
                move2 = move1;
            }

            BatchVertex vertices[6] = {
                    BatchVertex{ glm::vec2{x1, y1 - move2}, color, glm::vec2{0.0f, 1.0f}, textureIndex },
                    BatchVertex{ glm::vec2{x2, y2}, color, glm::vec2{0.0f, 0.0f}, textureIndex },
                    BatchVertex{ glm::vec2{ move1 + x1, y1 - w}, color, glm::vec2{1.0f, 1.0f}, textureIndex },

                    BatchVertex{ glm::vec2{x2, y2}, color, glm::vec2{1.0f, 1.0f}, textureIndex },
                    BatchVertex{ glm::vec2{move1 + x2, y2 - w + move2}, color, glm::vec2{1.0f, 0.0f}, textureIndex },
                    BatchVertex{ glm::vec2{move1 + x1, y1 - w}, color, glm::vec2{0.0f, 0.0f}, textureIndex }
            };

            BatchHandler::AddToBatch(vertices, 6);
        }

        void render(Shader &shader)
        {
            BatchHandler::RenderBatches(shader);
        }

        namespace Gui
        {
        }
    }
}