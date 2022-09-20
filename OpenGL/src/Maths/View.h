#pragma once

#include <GLM/glm.hpp>

namespace Maths
{
    /**
     * \brief A class represents a view matrix(also known as camera)
     * that manages transformation from world space to view space
     */
    class ViewMatrix
    {
    private:
        glm::mat4 m_Matrix;

    public:
        /**
         * \brief Initialize the view matrix with identity matrix
         */
        ViewMatrix();

        /**
         * \brief Initialize the view matrix with a given matrix
         * \param initialMatrix The initial matrix to be used
         */
        ViewMatrix(const glm::mat4& initialMatrix);

        /**
         * \brief Set the view matrix
         * \param matrix New view matrix to be used
         */
        inline void SetMatrix(const glm::mat4& matrix) { m_Matrix = matrix; }

        /**
         * \brief Get the latest view matrix
         * \return The view matrix
         */
        inline glm::mat4 GetMatrix() const { return m_Matrix; }

        /**
         * \brief Translate(move) the camera in the world space with the given vec3
         * \param trans A vec3 specifies how the camera should move
         */
        void Translate(const glm::vec3& trans);

        /**
         * \brief Rotate the camera in the world space
         * \param degrees The angle this camera should rotate(in 360 unit)
         * \param axis Specifies which is the rotation axis
         */
        void Rotate(float degrees, const glm::vec3& axis);

    };  // class ViewMatrix
}  // namespace Maths
