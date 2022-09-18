#pragma once

#include "Gl/glew.h"

#include <iostream>

namespace Utils
{
    #define ASSERT(x) if(!(x)) __debugbreak()
    #define GLCall(x) Utils::GLClearError();\
    x;\
    ASSERT(Utils::GLLogCall(#x, __FILE__, __LINE__))

    inline void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    inline bool GLLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << "):" << function <<
                " " << file << ":" << line << std::endl;
            return false;
        }
        return true;
    }
}
