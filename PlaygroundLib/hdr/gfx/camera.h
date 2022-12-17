#ifndef PLAYGROUNDLIB_CAMERA_H
#define PLAYGROUNDLIB_CAMERA_H
#include "../../hdr/core.h"

namespace GFX
{

    enum CameraMode
    {
        None,
        Ortho,
    };

    struct Camera
    {
    public:
        Camera();
        ~Camera();

        virtual void calculate() = 0;

        float getAspect();
        glm::mat4& getProjectionMatrix();
        glm::mat4& getViewMatrix();
        CameraMode& getMode();
    private:
        CameraMode mMode;
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

        void setOrtho(const f32& left, const f32& right,
                      const f32& top, const f32& bottom,
                      const f32& zNear, const f32& zFar);

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
