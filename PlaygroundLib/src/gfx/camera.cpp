#include "../../hdr/gfx/camera.h"
#include "../../hdr/gfx/gfx.h"

namespace GFX
{
    Camera::Camera()
        : mProj(glm::mat4(1.0f)), mView(glm::mat4(1.0f)),
        mWindowWidth((ui32*)GetWindowWidth()), mWindowHeight((ui32*)GetWindowHeight())
    {}

    Camera::~Camera()
    {}

    float Camera::getAspect()
    {
        return (float)*mWindowWidth/(float)*mWindowHeight;
    }

    glm::mat4 &Camera::getProjectionMatrix()
    {
        return mProj;
    }

    glm::mat4 &Camera::getViewMatrix()
    {
        return mView;
    }

    OrthoCamera::OrthoCamera()
        : Camera(), mLeft(0.f), mRight(0.f), mTop(0.f), mBottom(0.f), mZNear(0.f), mZFar(0.f)
    {}

    OrthoCamera::OrthoCamera(const float& left,
                             const float& right,
                             const float& top,
                             const float& bottom,
                             const float& zNear,
                             const float& zFar)
        : Camera(), mLeft(left), mRight(right), mTop(top), mBottom(bottom), mZNear(zNear), mZFar(zFar)
    {}

    OrthoCamera::~OrthoCamera()
    {}

    void OrthoCamera::calculate()
    {
        float aspect = getAspect();
        glm::mat4& proj = getProjectionMatrix();
        proj = glm::ortho(mLeft * aspect, mRight * aspect, mBottom, mTop, mZNear, mZFar);
        glm::mat4& view = getViewMatrix();
        view = glm::lookAt(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
    }
}
