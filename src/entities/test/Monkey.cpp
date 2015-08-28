#include "Monkey.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Monkey::init()
{
    m_move = 0.0f;
    m_transform = new omi::Transform(
            "",
            glm::vec3( 4.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
        );
    omi::Mesh* mesh =
        omi::ResourceManager::getMesh( "test_monkey", "", m_transform );
    mesh->getMaterial().specular =
        new omi::Specular( 128.0f, glm::vec3( 1.0f, 1.0f, 1.0f ) );
    m_components.add( mesh );
}

void Monkey::update()
{
    m_move += 0.2f * omi::fpsManager.getTimeScale();
    m_transform->translation.z = 11.0f * util::math::sind( m_move );
}

