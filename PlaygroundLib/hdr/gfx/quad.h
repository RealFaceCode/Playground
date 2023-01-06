#ifndef __QUAD_H__
#define __QUAD_H__
#include "../core.h"
#include "../util/buffer/list.h"

struct Quad
{
    float x;
    float y; 
    float width;
    float height;
    float rotation;
};

std::array<glm::vec2, 6> GetRawQuad();
List<glm::vec2> GetQuads(float meshX, float meshY, float meshScacleW, float meshScacleH, float meshRotate, List<Quad>& quads);

#endif // __QUAD_H__