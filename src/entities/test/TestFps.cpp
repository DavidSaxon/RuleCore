#include "TestFps.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestFps::init()
{
    m_counter = 1.1f;

    omi::Transform* transform = new omi::Transform(
            "",
            glm::vec3( 1.4f, 0.8f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( transform );

    m_text =
            omi::ResourceManager::getText( "test_text_1", "", transform );
    m_text->gui = true;
    m_text->setString( "0" );
    m_components.add( m_text );
}

void TestFps::update()
{
    if ( m_counter > 1.0f )
    {
        m_counter -= 1.0f;

        std::stringstream ss;
        ss << static_cast<int>( omi::fpsManager.getFPS() );

        if ( omi::fpsManager.getFPS() > 60.0f )
        {
            m_text->getMaterial().colour = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
        }
        else if ( omi::fpsManager.getFPS() > 30.0f )
        {
            m_text->getMaterial().colour = glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f );
        }
        else
        {
            m_text->getMaterial().colour = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
        }

        m_text->setString( ss.str() );
    }
    else
    {
        m_counter += 0.05f * omi::fpsManager.getTimeScale();
    }
}
