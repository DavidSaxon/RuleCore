#include "GameplayScene.hpp"

#include "src/data/Globals.hpp"

#include "src/omicron/input/Input.hpp"

#include "src/entities/gameplay/AIControl.hpp"
#include "src/entities/gameplay/GameplayControl.hpp"
#include "src/entities/gameplay/terrain/Environment.hpp"
#include "src/entities/menu/PauseMenu.hpp"

#include "src/scenes/menu/MenuScene.hpp"

// TODO: REMOVE ME
#include "src/entities/debug/FPSCounter.hpp"

GameplayScene::GameplayScene( bool flat )
    :
    m_flat( flat )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GameplayScene::init()
{
    // effects
    omi::renderSettings.setFilmGrain( 0.005f );

    // TODO: REMOVE ME
    // addEntity( new FPSCounter() );

    // add entities
    addEntity( new PauseMenu() );
    addEntity( new GameplayControl() );
    Environment* env = new Environment( m_flat );
    addEntity( env );

    addEntity( new AIControl( env ) );
}

bool GameplayScene::update()
{
    // TODO: REMOVE THIS
    if ( omi::input::isKeyPressed( omi::input::key::F7 ) )
    {
        return true;
    }


    if ( global::fuck )
    {
        global::fuck = false;
        return true;
    }

    return false;
}

omi::Scene* GameplayScene::nextScene()
{
    return new MenuScene();
}
