#ifndef PLAYGROUNDLIB_CAMERA_H
#define PLAYGROUNDLIB_CAMERA_H
#include "../../hdr/core.h"

namespace GFX
{
    struct Camera
    {
    public:
        Camera();
        ~Camera();

        virtual void calculate() = 0;

        float getAspect();
        glm::mat4& getProjectionMatrix();
        glm::mat4& getViewMatrix();
    private:
        glm::mat4 mProj;
        glm::mat4 mView;
        ui32* mWindowWidth;
        ui32* mWindowHeight;
    };

    struct OrthoCamera : Camera
    {
    public:
        OrthoCamera();
        OrthoCamera(const float& left,
                    const float& right,
                    const float& top,
                    const float& bottom,
                    const float& zNear,
                    const float& zFar);
        ~OrthoCamera();

        void calculate() override;
    private:
        float mLeft;
        float mRight;
        float mTop;
        float mBottom;
        float mZNear;
        float mZFar;
    };
}
#endif //PLAYGROUNDLIB_CAMERA_H
