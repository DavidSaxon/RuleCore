#include "ProjExplosion.hpp"

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

ProjExplosion::ProjExplosion( const glm::vec3& pos, unsigned type )
    :
    m_pos     ( pos ),
    m_type    ( type ),
    m_progress( 1.0F )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void ProjExplosion::init()
{
    m_transform = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_transform );

    // TODO: add mesh based on type
    // mesh
    if ( m_type == 0 )
    {
        m_mesh = omi::ResourceManager::getMesh(
                "unit_down_explosion",
                "",
                m_transform
        );
        m_colour = glm::vec3( 0.3F, 0.1F, 1.0F );
    }
    else
    {
        m_mesh = omi::ResourceManager::getMesh(
                "unit_up_explosion",
                "",
                m_transform
        );
        m_colour = glm::vec3( 1.0F, 0.1F, 0.1F );
    }

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
            0.03f,
            0.008f
    );
    m_components.add( m_light );

    // play sound
    std::string explSond( "proj_down_1" );
    unsigned r = rand() % 3;
    if ( rand() % 2 == 1 )
    {
        explSond = "proj_down_2";
    }
    if ( m_type == 1 )
    {
        explSond = "proj_up_1";
        if ( rand() % 2 == 1 )
        {
            explSond = "proj_up_2";
        }
    }
    omi::SoundPool::play(
            omi::ResourceManager::getSound( explSond ),
            false,
            0.5F
    );
}

void ProjExplosion::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    // explode mesh
    m_progress -= 0.05F * omi::fpsManager.getTimeScale();

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

        m_transform->scale += 1.4F * omi::fpsManager.getTimeScale();
    }
}
