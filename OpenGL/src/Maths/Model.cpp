#include "Model.h"

#include <GLM/gtc/matrix_transform.hpp>

namespace Maths
{
    ModelMatrix::ModelMatrix()
        : m_Matrix(glm::mat4(1.0f))
    {
    }

    ModelMatrix::ModelMatrix(const glm::mat4& initialMatrix)
        : m_Matrix(initialMatrix)
    {
    }

    void ModelMatrix::Translate(const glm::vec3& trans)
    {
        m_Matrix = glm::translate(m_Matrix, trans);
    }

    void ModelMatrix::Rotate(float degrees, const glm::vec3& axis)
    {
        m_Matrix = glm::rotate(m_Matrix, glm::radians(degrees), axis);
    }

    void ModelMatrix::Scale(const glm::vec3& scale)
    {
        m_Matrix = glm::scale(m_Matrix, scale);
    }
}  // namespace Maths