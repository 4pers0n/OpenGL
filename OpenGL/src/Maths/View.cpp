#include "View.h"

#include <GLM/gtc/matrix_transform.hpp>

namespace Maths
{
    ViewMatrix::ViewMatrix()
        : m_Matrix(glm::mat4(1.0f))
    {
    }

    ViewMatrix::ViewMatrix(const glm::mat4& initialMatrix)
        : m_Matrix(initialMatrix)
    {
    }

    void ViewMatrix::Translate(const glm::vec3& trans)
    {
        // scene will move in the reversed direction relative to camera
        m_Matrix = glm::translate(m_Matrix, -trans);
    }

    void ViewMatrix::Rotate(float degrees, const glm::vec3& axis)
    {
        m_Matrix = glm::rotate(m_Matrix, glm::radians(degrees), axis);
    }
}  // namespace Maths
