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

    static void HandleObjects(List<glm::vec2>& quadMesh, List<Quad>& quads, float& sumX, float& sumY)
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

            quadMesh.add(&rawQuad[0], 6); 
        }
    }

    static void HandleMesh(List<glm::vec2>& quadMesh, const float& meshX, 
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
            glm::vec2& v = (glm::vec2&)vert;
            v = transformMesh * glm::vec4(v, 0.0f, 1.0f);
        }
    }

    List<glm::vec2> GetQuads(const float& meshX, const float& meshY, 
                            const float& meshScaleW, const float& meshScaleH, 
                            const float& meshRotate, List<Quad>& quads)
    {
        List<glm::vec2> quadMesh;
        float sumX = 0;
        float sumY = 0;

        HandleObjects(quadMesh, quads, sumX, sumY);
        HandleMesh(quadMesh, meshX, meshY, meshScaleW, meshScaleH, meshRotate, sumX, sumY);

        return quadMesh;
    }
} // namespace GFX