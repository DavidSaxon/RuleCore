#include "GameplayControl.hpp"

#include "src/data/Globals.hpp"
#include "src/omicron/input/Input.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const float LOOK_SPEED = 0.1F;
static const float ZOOM_SPEED = 1.5F;
static const float MOVE_SPEED = 0.015F;
static const float ELVA_SPEED = 1.0F;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GameplayControl::GameplayControl()
    :
    m_camZoom        ( 75.0F ),
    m_camElevation   ( 25.0F ),
    m_lookControlDown( false )
{
}

GameplayControl::~GameplayControl()
{
    m_mainMusic->stop();
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GameplayControl::init()
{
    // initialise the components
    initComponents();
}

void GameplayControl::update()
{
    // TODO: COULD DO PAUSE MUSIC HERE? CHECK REVIERIE PLAYER
    if ( global::pause )
    {
        return;
    }

    if ( omi::input::isKeyPressed( omi::input::key::LEFT_SHIFT ) )
    {
        moveControl();
    }
    else
    {
        lookControl();
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GameplayControl::moveControl()
{
    // is middle mouse down down?
    if ( omi::input::mousePressed( omi::input::mouse_button::MIDDLE ) )
    {
        if ( !m_lookControlDown )
        {
            // look the cursor
            omi::systemSettings.setCursorLocked( true );
            m_mouseLockPos = omi::input::getMousePos();
            omi::systemSettings.setCursorLockPosition( m_mouseLockPos );
        }
        m_lookControlDown = true;

        // move the camera based on the mouse movement
        float x_diff =
                ( m_mouseLockPos.x - omi::input::getMousePos().x ) * MOVE_SPEED;
        float y_diff =
                ( m_mouseLockPos.y - omi::input::getMousePos().y ) * MOVE_SPEED;
        m_preT->translation.x +=
                ( util::math::sind( m_rotateT->rotation.y ) * y_diff ) +
                ( util::math::cosd( m_rotateT->rotation.y ) * x_diff );
        m_preT->translation.z -=
                ( util::math::sind( m_rotateT->rotation.y ) * x_diff ) +
                ( util::math::cosd( m_rotateT->rotation.y ) * y_diff );

        if ( m_preT->translation.x < 0.0F )
        {
            m_preT->translation.x = 0.0F;
        }
        if ( m_preT->translation.x > 50.0F )
        {
            m_preT->translation.x = 50.0F;
        }

        if ( m_preT->translation.z < 0.0F )
        {
            m_preT->translation.z = 0.0F;
        }
        if ( m_preT->translation.z > 100.0F )
        {
            m_preT->translation.z = 100.0F;
        }

        // don't process any further
        return;
    }

    // unlock the mouse
    if ( m_lookControlDown )
    {
        omi::systemSettings.setCursorLocked( false );
        m_lookControlDown = false;
    }

    // change elevation
    m_camElevation += ELVA_SPEED * omi::input::getMouseScroll();
    if ( m_camElevation < 0.0F )
    {
        m_camElevation = 0.0F;
    }
    if ( m_camElevation >= 50.0F )
    {
        m_camElevation = 50.0F;
    }
    m_preT->translation.y = m_camElevation;
}

void GameplayControl::lookControl()
{
    // is middle mouse down down?
    if ( omi::input::mousePressed( omi::input::mouse_button::MIDDLE ) )
    {
        if ( !m_lookControlDown )
        {
            // look the cursor
            omi::systemSettings.setCursorLocked( true );
            m_mouseLockPos = omi::input::getMousePos();
            omi::systemSettings.setCursorLockPosition( m_mouseLockPos );
        }
        m_lookControlDown = true;

        // rotate the camera based on how far the mouse has moved from the lock
        // position
        m_rotateT->rotation.x +=
            ( m_mouseLockPos.y - omi::input::getMousePos().y ) * LOOK_SPEED;
        m_rotateT->rotation.y +=
            ( m_mouseLockPos.x - omi::input::getMousePos().x ) * LOOK_SPEED;

        if ( m_rotateT->rotation.x < -90.0F )
        {
            m_rotateT->rotation.x = -90.0F;
        }
        if ( m_rotateT->rotation.x >= 45.0F )
        {
            m_rotateT->rotation.x = 45.0F;
        }

        // don't process any further
        return;
    }

    // unlock the mouse
    if ( m_lookControlDown )
    {
        omi::systemSettings.setCursorLocked( false );
        m_lookControlDown = false;
    }

    //  zoom
    m_camZoom -= ZOOM_SPEED * omi::input::getMouseScroll();
    // apply to camera
    m_transT->translation.z = m_camZoom;
}

void GameplayControl::initComponents()
{
    // camera transforms
    m_preT = new omi::Transform(
            "",
            glm::vec3( 25.0f, m_camElevation, 50.0F ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_preT );
    m_rotateT = new omi::Transform(
            "",
            m_preT,
            glm::vec3( 0.0f, 0.0F, 0.0F ),
            glm::vec3( -35.0F, 135.0F, 0.0F ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_rotateT );
    m_transT = new omi::Transform(
            "",
            m_rotateT,
            glm::vec3( 0.0f, 0.0F, m_camZoom ),
            glm::vec3( 0.0F, 0.0F, 0.0F ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_transT );

    // the camera
    omi::Camera* camera = new omi::Camera(
        "",
        omi::cam::PERSPECTIVE,
        m_transT,
        0.2F,
        370.0F
    );
    camera->setExposure( 2.2f );
    m_components.add( camera );

    // music
    m_mainMusic = new omi::Music(
            "", "res/sound/music/reign_of_terror.ogg", 0.6F, true
    );
    m_mainMusic->play();
}
