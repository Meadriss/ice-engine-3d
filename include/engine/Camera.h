#pragma once

#include "utils/constants.h"
#include "WindowGLFW.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/log.h"


namespace ice {


/**
 * Camera component.
 *
 * \date    May 2018
 * \author  Constantin Masson
 */
class Camera {
    /*
     * TODO: DEV NOTE
     * Camera data are kind of hardcoded, these should be placed in gameplay
     * space (Maybe camera gameplay that extends this).
     */

    private:
        float _fov              = 40.0f; // Default value

        glm::vec3 _camPos       = glm::vec3(10.0f, 18.0f, 5.0f);
        glm::vec3 _camTarget    = glm::vec3(10.0f, 0.0f, 5.0f);
        glm::vec3 _worldUp      = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 _camDir;
        glm::vec3 _camRight;
        glm::vec3 _camUp;


    public:

        /**
         * To call once a frame.
         * Update all camera internal data.
         */
        void updateViewData() {
            _camDir     = glm::normalize(_camTarget - _camPos);
            _camRight   = glm::normalize(glm::cross(_camDir, _worldUp));
            // TODO: HARD CODED
            // I have some issue, the camera is 45 degree rotated..
            // So far, I didn't figured out a solution so I hard coded _camRight
            // because, for this very game, it's ok, but it is, in a perfect
            // world, not ok! :p
            _camRight   = glm::vec3(1.0f, 0.0f, 0.0f);
            _camUp      = glm::normalize(glm::cross(_camRight, _camDir));
        }

        glm::mat4 getViewMatrix() const {
            return glm::lookAt(_camPos, _camTarget, _camUp);
        }

        glm::mat4 getPerspectiveMatrix() const {
            int width, height;
            glfwGetWindowSize(WindowGLFW::getInstance()._window, &width, &height);
            float ratio = (float)width / (float)height;

            return glm::perspective(glm::radians(_fov), ratio, 0.1f, 100.0f);
        }

    public:
        glm::vec3 getPosition() const {
            return _camPos;
        }
};


} // End namespace


