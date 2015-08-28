#include "TestSun.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestSun::TestSun() :
    Entity(),
    m_move( 1.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestSun::init()
{
    // transform
    m_transform = new omi::Transform(
            "",
            glm::vec3( 1.0f, 0.5f, 0.0f ),
            glm::vec3(),
            glm::vec3( 4.0f, 4.0f, 4.0f )
    );
    m_components.add( m_transform );
    m_lightT = new omi::Transform(
            "",
            glm::vec3( 1.0f, 0.5f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_lightT );

    // add light
    omi::DirectionalLight* light =
    light =  new omi::DirectionalLight(
        "", m_lightT, 0.8f, glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    light->setCastShadow( true );
    m_components.add( light );

    // add the geo
    omi::Mesh* mesh =
            omi::ResourceManager::getMesh( "test_sun_geo", "", m_transform );
    mesh->castShadow = false;
    mesh->getMaterial().glow =
        new omi::Glow( glm::vec3( 1.0f, 1.0f, 1.0f ), 1.0f );
    m_components.add( mesh );
}

void TestSun::update()
{
    // move the light
    // m_move -= 0.005f * omi::fpsManager.getTimeScale();

    m_move = -0.25f;

    m_transform->translation.x = sin( m_move ) * 60.0f;
    m_transform->translation.y = cos( m_move * 0.4f ) * 40.0f;
    m_transform->translation.z = cos( m_move ) * 60.0f;

    m_lightT->translation.x = m_transform->translation.x;
    m_lightT->translation.y = m_transform->translation.y + 13.0f;
    m_lightT->translation.z = m_transform->translation.z;
}
