#ifndef PLAYGROUNDLIB_CAMERA_H
#define PLAYGROUNDLIB_CAMERA_H
#include <glm.hpp>

struct Camera
        {
        public:
            Camera();
            ~Camera();
        private:
            glm::mat4 mProj;
            glm::mat4 mView;
        };

#endif //PLAYGROUNDLIB_CAMERA_H
