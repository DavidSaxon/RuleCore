#include "Texture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Texture::Texture() :
    m_id     (0),
    m_visible(true) {
}

Texture::Texture( GLuint id, const glm::vec2& dimensions ) :
    m_id        (id),
    m_dimensions( dimensions ),
    m_visible   (true) {
}

Texture::Texture(const Texture& other) :
    m_id        ( other.m_id ),
    m_dimensions( other.m_dimensions ),
    m_visible   ( true ) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Texture::~Texture() {
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const Texture& Texture::operator=(const Texture& other) {

    m_id         = other.m_id;
    m_dimensions = other.m_dimensions;
    m_visible    = other.m_visible;

    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Texture::update() {

    // do nothing
}

GLuint Texture::getId() const {

    return m_id;
}

tex::Type Texture::getType() const {

    return tex::TEXTURE;
}

const glm::vec2& Texture::getDimensions() const
{
    return m_dimensions;
}

bool Texture::isVisible() const {

    return m_visible;
}

} // namespace omi
