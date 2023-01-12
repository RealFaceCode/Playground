#ifndef __QUAD_H__
#define __QUAD_H__
#include "../core.h"
#include "../util/buffer/list.h"
#include "../util/buffer/pair.h"
#include "batchrenderer/batchvertex.h"

namespace GFX
{
    struct Quad
    {
        float x;
        float y; 
        float width;
        float height;
        float rotation;
        float texCoordS0;
        float texCoordS1;
        float texCoordT0;
        float texCoordT1;
        float r;
        float g;
        float b;
        float a;
        float textureIndex;
    };

    std::array<glm::vec2, 6> GetRawQuad();
    List<Pair<glm::vec2, glm::vec2>> GetQuads(const float& meshX, const float& meshY, 
                            const float& meshScaleW, const float& meshScaleH, 
                            const float& meshRotate, List<Quad>& quads);

    List<BatchVertex2D> GetQuads_BV2D(const float& meshX, const float& meshY, 
                            const float& meshScaleW, const float& meshScaleH, 
                            const float& meshRotate, List<Quad>& quads);
}

#endif // __QUAD_H__