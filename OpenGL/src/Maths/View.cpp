#include "View.h"

#include <GLM/gtc/matrix_transform.hpp>

namespace Maths
{
    ViewMatrix::ViewMatrix()
        : m_CameraFront(0.0f, 0.0f, -1.0f), m_CameraUp(0.0f, 1.0f, 0.0f),
          m_CameraRight(1.0f, 0.0f, 0.0f), m_CameraPos(0.0f, 0.0f, 0.0f), m_WorldUp(0.0f, 1.0f, 0.0f), m_Yaw(0.0f),
          m_Pitch(0.0f)
    {
        UpdateRotation();
    }

    ViewMatrix::ViewMatrix(glm::vec3 cameraPos, glm::vec3 worldUp, float yaw, float pitch)
        : m_CameraFront(0.0f, 0.0f, -1.0f), m_CameraUp(0.0f, 1.0f, 0.0f),
          m_CameraRight(1.0f, 0.0f, 0.0f), m_CameraPos(cameraPos), m_WorldUp(worldUp), m_Yaw(yaw),
          m_Pitch(pitch)
    {
        UpdateRotation();
    }

    void ViewMatrix::Move(CameraMovement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == Forward)
        {
            m_CameraPos += m_CameraFront * velocity;
        }
        if (direction == Backward)
        {
            m_CameraPos -= m_CameraFront * velocity;
        }
        if (direction == Right)
        {
            m_CameraPos += m_CameraRight * velocity;
        }
        if (direction == Left)
        {
            m_CameraPos -= m_CameraRight * velocity;
        }
        if (direction == Up)
        {
            m_CameraPos += m_CameraUp * velocity;
        }
        if (direction == Down)
        {
            m_CameraPos -= m_CameraUp * velocity;
        }
    }

    void ViewMatrix::LookAround(float xoffset, float yoffset)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (m_Pitch > 89.0f)
        {
            m_Pitch = 89.0f;
        }
        if (m_Pitch < -89.0f)
        {
            m_Pitch = -89.0f;
        }

        UpdateRotation();
    }

    glm::mat4 ViewMatrix::GetMatrix() const
    {
        return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
    }

    void ViewMatrix::UpdateRotation()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
        front.y = sin(glm::radians(m_Pitch));
        front.z = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));

        m_CameraFront = glm::normalize(front);
        m_CameraRight = glm::cross(m_CameraFront, m_WorldUp);
        m_CameraUp = glm::cross(m_CameraRight, m_CameraFront);
    }
}  // namespace Maths
