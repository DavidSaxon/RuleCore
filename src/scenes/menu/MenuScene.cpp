#include "MenuScene.hpp"

#include "src/scenes/gameplay/GameplayScene.hpp"

#include "src/omicron/input/Input.hpp"

#include "src/entities/start_up/MainMenu.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void MenuScene::init()
{
    m_exit = false;
    m_flat = false;

    // apply settings
    omi::renderSettings.setDepthTest( false );

    addEntity( new MainMenu() );
}

bool MenuScene::update()
{
    // check for key pressed
    if ( omi::input::isKeyPressed( omi::input::key::ESCAPE ) )
    {
        m_exit = true;
        return true;
    }
    if ( omi::input::isKeyPressed( omi::input::key::A ) )
    {
        m_flat = false;
        return true;
    }
    if ( omi::input::isKeyPressed( omi::input::key::B ) )
    {
        m_flat = true;
        return true;
    }

    return false;
}

omi::Scene* MenuScene::nextScene()
{
    // revert settings
    omi::renderSettings.setDepthTest( true );

    if ( m_exit )
    {
        return NULL;
    }

    return new GameplayScene( m_flat );
}
