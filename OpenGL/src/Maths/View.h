#pragma once

#include <GLM/glm.hpp>

namespace Maths
{

    /**
     * \brief Defines all the movement supported by this camera system
     */
    enum CameraMovement
    {
        Forward,
        Backward,
        Left,
        Right,
        Up,
        Down
    };

    /**
     * \brief A class represents a view matrix(also known as camera)
     * that manages transformation from world space to view space
     */
    class ViewMatrix
    {
    private:
        // const values for processing input
        const float MovementSpeed = 2.5f;
        const float MouseSensitivity = 0.1f;

        // camera attributes local space
        glm::vec3 m_CameraFront;
        glm::vec3 m_CameraUp;
        glm::vec3 m_CameraRight;

        // camera attributes world space
        glm::vec3 m_CameraPos;
        glm::vec3 m_WorldUp;

        // camera rotation in Euler angles
        float m_Yaw;
        float m_Pitch;

    public:
        /**
         * \brief Initialize the camera with a position at the world origin and facing towards negative z direction
         */
        ViewMatrix();

        /**
         * \brief Initialize with the parameters
         * \param cameraPos The initial camera position
         * \param worldUp The vec3 defines the world's up position
         * \param yaw The initial yaw
         * \param pitch The initial pitch
         */
        ViewMatrix(glm::vec3 cameraPos, glm::vec3 worldUp, float yaw, float pitch);

        /**
         * \brief Move the camera based on direction
         * \param direction A CameraMovement enum that defines how the camera should move
         * \param deltaTime The delta time between frames used to calculate the speed
         */
        void Move(CameraMovement direction, float deltaTime);

        /**
         * \brief Rotate the camera based on the offset for pitch and yaw
         * \param xoffset The yaw offset
         * \param yoffset The pitch offset
         */
        void LookAround(float xoffset, float yoffset);

        /**
         * \brief Get the actual view matrix used in MVP transformation
         * \return The view matrix
         */
        glm::mat4 GetMatrix() const;

    private:
        /**
         * \brief Helper function called whenever there is an update on the camera's rotation.
         * Used to update all internal data
         */
        void UpdateRotation();

    };  // class ViewMatrix
}  // namespace Maths
