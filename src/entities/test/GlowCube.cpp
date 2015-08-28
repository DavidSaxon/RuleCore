#include "GlowCube.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GlowCube::GlowCube() :
    m_colour        ( 1.0f, 0.0f, 0.0f, 1.0f ),
    m_colourChange  ( 0.0f ),
    m_flickerCounter( 0.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GlowCube::init()
{
    // transformation
    m_transform = new omi::Transform(
            "",
            glm::vec3( -6.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
        );
    m_components.add( m_transform );

    // add collision detector
    m_collisionDetect = new omi::CollisionDetector( "", "block", this );
    m_collisionDetect->addBounding(
            new omi::BoundingRect( glm::vec2( 1.0f, 1.0f ), m_transform ) );
    m_components.add( m_collisionDetect );

    // add mesh
    m_mesh =
        omi::ResourceManager::getMesh( "glow_cube", "", m_transform );
    m_mesh->getMaterial().colour = m_colour;
    m_mesh->getMaterial().glow =
        new omi::Glow( glm::vec3( m_colour + 0.75f ), 1.0f,
        omi::ResourceManager::getTexture( "glow_cube" ) );
    m_components.add( m_mesh );

    // add light
    m_light = new omi::PointLight(
        "", m_transform, 1.0f,
        glm::vec3( m_colour ), 0.05f, 0.2f, 0.000001f
    );
    m_components.add( m_light );
}

void GlowCube::update()
{
    // change colour
    m_colourChange += 0.005f * omi::fpsManager.getTimeScale();
    if ( m_colourChange > 3.0f )
    {
        m_colourChange -= 3.0f;
    }

    if ( m_colourChange <= 1.0f )
    {
        m_colour.r = 1.0f - m_colourChange;
        m_colour.g = m_colourChange;
        m_colour.b = 0.0f;
    }
    else if ( m_colourChange > 1.0f && m_colourChange < 2.0f )
    {
        float colourChange = m_colourChange - 1.0f;
        m_colour.r = 0.0f;
        m_colour.g = 1.0f - colourChange;
        m_colour.b = colourChange;
    }
    else
    {
        float colourChange = m_colourChange - 2.0f;
        m_colour.r = colourChange;
        m_colour.g = 0.0f;
        m_colour.b = 1.0f - colourChange;
    }

    // update the cube's colour
    m_mesh->getMaterial().colour = m_colour;
    m_mesh->getMaterial().glow->setColour( glm::vec3( m_colour + 0.75f ) );
    m_light->setColour( glm::vec3( m_colour ) );

    // apply light flicker
    // if ( m_flickerCounter > 1.0f )
    // {
    //     m_flickerCounter -= 1.0f;
    //     float flicker = static_cast<float>( rand() % 1000 ) / 4000.0f;
    //     m_mesh->getMaterial().glow->setBrightness( 0.7f + ( flicker / 3.0f ) );
    //     flicker += 0.75f;
    //     m_light->setPower( flicker );
    // }
    // else
    // {
    //     m_flickerCounter += 0.25f * omi::fpsManager.getTimeScale();
    // }

}

