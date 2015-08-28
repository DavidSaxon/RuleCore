#ifndef OMICRON_RENDERING_SHADING_TEXTURE_H_
#   define OMICRON_RENDERING_SHADING_TEXTURE_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "lib/glm/glm.hpp"

namespace omi {

namespace tex {

    // the types of textures
    enum Type {

        TEXTURE,
        ANIMATION
    };
}

/*********************************************\
| A wrapper around an OpenGL texture pointer. |
\*********************************************/
class Texture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a blank texture */
    Texture();

    /** Creates a new texture with the given OpenGL texture pointer
    @param id the pointer to the OpenGL texture*/
    Texture( GLuint id, const glm::vec2& dimensions );

    /** Creates a copy of the given texture
    @param other the other texture from */
    Texture(const Texture& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~Texture();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    const Texture& operator=(const Texture& other);

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Updates the texture */
    virtual void update();

    /** @return the OpenGL pointer to the current texture */
    GLuint getId() const;

    /** @return the type of the texture */
    virtual tex::Type getType() const;

    /** @return the dimensions of the texture */
    const glm::vec2& getDimensions() const;

    /** @return if the texture is visible */
    bool isVisible() const;

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the OpenGL pointer to the texture
    GLuint m_id;
    // the dimensions of the texture
    glm::vec2 m_dimensions;

    // if the texture is visible
    bool m_visible;
};

} // namespace omi

#endif
