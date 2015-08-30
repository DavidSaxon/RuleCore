#include "UnitDead.hpp"

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

UnitDead::UnitDead( const glm::vec3& pos )
    :
    m_pos     ( pos ),
    m_progress( 1.0F )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void UnitDead::init()
{
    m_transform = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_transform );

    m_mesh = omi::ResourceManager::getMesh(
            "unit_dead",
            "",
            m_transform
    );
    m_colour = glm::vec3( 1.0F, 0.5F, 0.1F );
    m_mesh->getMaterial().glow = new omi::Glow( m_colour, 1.0F );
    m_mesh->castShadow = false;
    m_components.add( m_mesh );

    // light
    m_light = new omi::PointLight(
            "",
            m_transform,
            1.0F,
            m_colour,
            0.0f,
            0.01f,
            0.001f
    );
    m_components.add( m_light );
}

void UnitDead::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    // explode mesh
    m_progress -= 0.02F * omi::fpsManager.getTimeScale();

    if ( m_progress <= 0.0F )
    {
        remove();
    }
    else
    {
        delete m_mesh->getMaterial().glow;
        m_mesh->getMaterial().glow = new omi::Glow(
                m_colour,
                m_progress
        );
        m_mesh->getMaterial().colour.a = m_progress;
        m_light->setPower( m_progress );

        m_transform->scale += 2.5F * omi::fpsManager.getTimeScale();
    }
}
