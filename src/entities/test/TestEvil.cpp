#include "TestEvil.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestEvil::init()
{
    m_transTimer = 0.0f;
    m_trans = false;
    m_walk = false;

    m_transform = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, -10.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_transform );

    m_mesh = omi::ResourceManager::getKeyFrameMesh(
            "test_evil_key", "", m_transform );
    // m_mesh->ignoreLight( "purple_point" );
    m_mesh->setDoVisCheck( false );
    m_components.add( m_mesh );

    m_visMesh =
            omi::ResourceManager::getMesh( "test_evil_vis", "", m_transform );
    m_visMesh->setDoVisCheck( true );
    m_visMesh->setOnlyVisCheck( true );
    m_components.add( m_visMesh );
}

void TestEvil::update()
{
    if ( !m_walk && !m_trans )
    {
        m_transTimer += 0.0025f * omi::fpsManager.getTimeScale();
        if ( m_transTimer > 1.0f )
        {
            m_trans = true;
            m_mesh->transition( "walk", 26 );
        }
    }
    else if ( !m_walk && m_trans && !m_mesh->isTransitioning() )
    {
        m_walk = true;
    }
    else
    {
        // move
        m_transform->translation.z += 0.022f * omi::fpsManager.getTimeScale();
    }

    // check if this is visible
    if ( m_visMesh->getVisCam() )
    {
        // std::cout << "I see dead people" << std::endl;
    }
    else
    {
        // std::cout << "no" << std::endl;
    }

}
