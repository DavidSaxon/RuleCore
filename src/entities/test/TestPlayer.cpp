#include "TestPlayer.hpp"

namespace {

static const float LOOK_SPEED = 0.15f;
static const float MOVE_SPEED = 0.15f;

} // namespace anonymous

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestPlayer::init()
{
    m_fDown = false;

    // create the camera
    m_camT = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 10.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
        );
    m_components.add( m_camT );
    omi::Camera* camera = new omi::Camera( "", omi::cam::PERSPECTIVE, m_camT );
    camera->setExposure( 1.2f );
    m_components.add( camera );

    // create collision checker
    m_collisionChecker = new omi::CollisionChecker( "" );
    m_collisionChecker->addBounding(
            new omi::BoundingRect( glm::vec2( 0.2f, 0.2f ), m_camT ) );
    m_components.add( m_collisionChecker );

    // create spot light
    // m_components.add( new omi::SpotLight(
    //     "", m_camT, 1.0f, glm::vec3( 1.0f, 1.0f, 1.0f ),
    //     0.0f, 0.4f, 0.025f, 40.0f, 30.0f
    // ) );

    // music
    omi::Music* music = new omi::Music(
            "", "res/sound/music/test/imminent_war.ogg", 1.0f, true
    );
    m_components.add( music );
    music->play();
}

void TestPlayer::update()
{
    // look
    if ( omi::omi_hasFocus )
    {
        m_camT->rotation.x +=
            ( omi::displaySettings.getCentre().y -
                    omi::input::getMousePos().y ) *
            LOOK_SPEED * omi::fpsManager.getTimeScale();
        m_camT->rotation.y +=
            ( omi::displaySettings.getCentre().x -
                    omi::input::getMousePos().x ) *
            LOOK_SPEED * omi::fpsManager.getTimeScale();
    }

    // calculate the amount to move
    glm::vec3 move;
    float moveSpeed = MOVE_SPEED * omi::fpsManager.getTimeScale();
    if ( omi::input::isKeyPressed( omi::input::key::W ) )
    {
        move.z = -util::math::cosd( m_camT->rotation.y ) * moveSpeed;
        move.x = -util::math::sind( m_camT->rotation.y ) * moveSpeed;
    }
    if ( omi::input::isKeyPressed( omi::input::key::S ) )
    {
        move.z = util::math::cosd( m_camT->rotation.y ) * moveSpeed;
        move.x = util::math::sind( m_camT->rotation.y ) * moveSpeed;
    }
    if ( omi::input::isKeyPressed( omi::input::key::A ) )
    {
        move.z =  util::math::sind( m_camT->rotation.y ) * moveSpeed;
        move.x = -util::math::cosd( m_camT->rotation.y ) * moveSpeed;
    }
    if ( omi::input::isKeyPressed( omi::input::key::D ) )
    {
        move.z = -util::math::sind( m_camT->rotation.y ) * moveSpeed;
        move.x =  util::math::cosd( m_camT->rotation.y ) * moveSpeed;
    }

    // play sound
    if ( omi::input::isKeyPressed( omi::input::key::F ) )
    {
        // play sound
        if ( !m_fDown )
        {
            omi::SoundPool::play(
                omi::ResourceManager::getSound( "explosion_1" ), false, 1.0f );
            omi::renderSettings.setShadows( !omi::renderSettings.getShadows() );
            m_fDown = true;
        }
    }
    else
    {
        m_fDown = false;
    }

    // check for collisions
    m_camT->translation +=
            m_collisionChecker->forwardBestCheck( move, "block" );
    // if ( !m_collisionChecker->forwardCheck( move, "block" ) )
    // {
    //     m_camT->translation += move;
    // }
}
