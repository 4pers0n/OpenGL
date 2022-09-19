#pragma once

#include <string>

namespace GLBasics
{
    /**
     * \brief Texture class that handles extracting data from a file and binding it
     */
    class Texture
    {
    private:
        unsigned int m_RendererID;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

    public:
        /**
         * \brief Constructs a texture class with the given file path
         * \param path A string that is the path to a PNG file that will be used as texture
         */
        Texture(const std::string& path);

        /**
         * \brief Calls the underlying OpenGL function to delete the texture
         */
        ~Texture();

        /**
         * \brief Bind this texture
         * \param slot which sampler2D slot to use
         */
        void Bind(unsigned int slot = 0) const;
        
        /**
         * \brief Unbind this texture
         */
        void UnBind() const;

        /**
         * \brief Get the width of the input PNG file
         * \return An integer that is the width
         */
        inline int GetWidth() const { return m_Width; }

        /**
         * \brief Get the height of the input PNG file
         * \return An integer that is the height
         */
        inline int GetHeight() const { return m_Height; }
    };  // class Texture
}  // namespace GLBasics