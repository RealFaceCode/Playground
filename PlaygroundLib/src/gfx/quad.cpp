#include "../../hdr/gfx/quad.h"

namespace GFX
{
    std::array<glm::vec2, 6> GetRawQuad()
    {
        std::array<glm::vec2, 6> quad;
        quad[0] = glm::vec2{0.0f, 0.0f};
        quad[1] = glm::vec2{1.0f, 0.0f};
        quad[2] = glm::vec2{1.0f, 1.0f};
        quad[3] = glm::vec2{1.0f, 1.0f};
        quad[4] = glm::vec2{0.0f, 1.0f};
        quad[5] = glm::vec2{0.0f, 0.0f};

        return quad;
    }

    static void HandleObjects(List<Pair<glm::vec2, glm::vec2>>& quadMesh, List<Quad>& quads, float& sumX, float& sumY)
    {
        glm::vec3 quadCenter{0.5, 0.5, 0};
        for(ui64 i = 0; i < quads.length(); i++)
        {
            Quad q = *quads.at(i);
            auto rawQuad = GetRawQuad();

            float x = q.x;
            float y = q.y;
            float w = q.width;
            float h = q.height; 
            float s0 = q.texCoordS0;
            float s1 = q.texCoordS1;
            float t0 = q.texCoordT0;
            float t1 = q.texCoordT1;
            float r = q.rotation;

            glm::mat4 rotateObj = glm::translate(glm::identity<glm::mat4>(), quadCenter);
            rotateObj = glm::rotate(rotateObj, glm::radians(r), glm::vec3(0, 0, 1));
            rotateObj = glm::translate(rotateObj, -quadCenter);
            glm::mat4 scaleObj = glm::scale(glm::identity<glm::mat4>(), {w, h, 1});
            glm::mat4 translateObj = glm::translate(glm::identity<glm::mat4>(), {x, y, 0});
            glm::mat4 transformObj = translateObj * rotateObj * scaleObj;

            for (auto& vert : rawQuad)
            {
                vert = transformObj * glm::vec4(vert, 0.0f, 1.0f);
                sumX += vert.x;
                sumY += vert.y;
            }

            std::array<Pair<glm::vec2, glm::vec2>, 6> processedQuad;
            processedQuad[0] = Pair<glm::vec2, glm::vec2>{rawQuad[0], {s0, t0}};
            processedQuad[1] = Pair<glm::vec2, glm::vec2>{rawQuad[1], {s1, t0}};
            processedQuad[2] = Pair<glm::vec2, glm::vec2>{rawQuad[2], {s1, t1}};
            processedQuad[3] = Pair<glm::vec2, glm::vec2>{rawQuad[3], {s1, t1}};
            processedQuad[4] = Pair<glm::vec2, glm::vec2>{rawQuad[4], {s0, t1}};
            processedQuad[5] = Pair<glm::vec2, glm::vec2>{rawQuad[5], {s0, t0}};

            quadMesh.add(&processedQuad[0], 6); 
        }
    }

    static void HandleMesh(List<Pair<glm::vec2, glm::vec2>>& quadMesh, const float& meshX, 
                            const float& meshY, const float& meshScaleW, 
                            const float& meshScaleH, const float& meshRotate,
                            const float& sumX, const float& sumY)
    {
        glm::vec3 meshCenter{0, 0, 0};
        meshCenter.x = sumX / (float)quadMesh.length();
        meshCenter.y = sumY / (float)quadMesh.length();

        glm::mat4 rotateMesh = glm::translate(glm::identity<glm::mat4>(), meshCenter);
        rotateMesh = glm::rotate(rotateMesh, glm::radians(meshRotate), glm::vec3(0, 0, 1));
        rotateMesh = glm::translate(rotateMesh, -meshCenter);
        glm::mat4 scaleMesh = glm::scale(glm::identity<glm::mat4>(), {meshScaleW, meshScaleH, 1});
        glm::mat4 translateMesh = glm::translate(glm::identity<glm::mat4>(), {meshX, meshY, 0});
        glm::mat4 transformMesh = translateMesh * rotateMesh * scaleMesh;

        for (auto& vert : quadMesh)
        {
            auto& v = (glm::vec2&)vert.first;
            v = transformMesh * glm::vec4(v, 0.0f, 1.0f);
        }
    }

    List<Pair<glm::vec2, glm::vec2>> GetQuads(const float& meshX, const float& meshY, 
                            const float& meshScaleW, const float& meshScaleH, 
                            const float& meshRotate, List<Quad>& quads)
    {
        List<Pair<glm::vec2, glm::vec2>> quadMesh;
        float sumX = 0;
        float sumY = 0;

        HandleObjects(quadMesh, quads, sumX, sumY);
        HandleMesh(quadMesh, meshX, meshY, meshScaleW, meshScaleH, meshRotate, sumX, sumY);

        return quadMesh;
    }
} // namespace GFX