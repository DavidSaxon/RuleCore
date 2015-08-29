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

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GameplayControl::GameplayControl()
    :
    m_camZoom        ( 50.0F ),
    m_camElevation   ( 0.0F ),
    m_lookControlDown( false )
{
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

    lookControl();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

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
    m_rotateT = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0F, 0.0F ),
            glm::vec3( -25.0F, 90.0F, 0.0F ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_rotateT );
    m_transT = new omi::Transform(
            "",
            m_rotateT,
            glm::vec3( 0.0f, m_camElevation, m_camZoom ),
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
    camera->setExposure( 2.0f );
    m_components.add( camera );
}
