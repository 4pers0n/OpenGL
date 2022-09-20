#pragma once

#include <GLM/glm.hpp>

namespace Maths
{
    /**
     * \brief A class represents a model matrix that manages transformation from
     * local space to world space
     */
    class ModelMatrix
    {
    private:
        glm::mat4 m_Matrix;

    public:
        /**
         * \brief Initialize the model matrix with identity matrix
         */
        ModelMatrix();

        /**
         * \brief Initialize the model matrix with a given matrix 
         * \param initialMatrix The initial matrix to be used
         */
        ModelMatrix(const glm::mat4& initialMatrix);

        /**
         * \brief Set the model matrix
         * \param matrix New model matrix to be used
         */
        inline void SetMatrix(const glm::mat4& matrix) { m_Matrix = matrix; }

        /**
         * \brief Get the latest model matrix
         * \return The model matrix
         */
        inline glm::mat4 GetMatrix() const { return m_Matrix; }

        /**
         * \brief Translate(move) the model in the world space with the given vec3
         * \param trans A vec3 specifies how the model should move
         */
        void Translate(const glm::vec3& trans);

        /**
         * \brief Rotate the model in the world space
         * \param degrees The angle this model should rotate(in 360 unit)
         * \param axis Specifies which is the rotation axis
         */
        void Rotate(float degrees, const glm::vec3& axis);

        /**
         * \brief Scale the model in the world space
         * \param scale Specifies the scalar
         */
        void Scale(const glm::vec3& scale);

    };  // class ModelMatrix
}  // namespace Maths