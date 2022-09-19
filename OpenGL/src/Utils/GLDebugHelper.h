#pragma once

#include <iostream>

#include <Gl/glew.h>

namespace Utils
{
    #define ASSERT(x) if(!(x)) __debugbreak()
    #define GLCall(x) Utils::GLClearError();\
    x;\
    ASSERT(Utils::GLLogCall(#x, __FILE__, __LINE__))

    /**
     * \brief Recursively clear all OpenGL errors
     */
    inline void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    /**
     * \brief Recursively print out all the OpenGL errors with the given information
     * \param function Function name c string
     * \param file File name c string
     * \param line Line number
     * \return true If there is no error; false otherwise
     */
    inline bool GLLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << "):" << function <<
                " " << file << ":" << line << std::endl;
            return false;
        }
        return true;
    }
}  //namespace Utils
