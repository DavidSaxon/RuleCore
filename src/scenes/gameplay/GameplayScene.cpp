#include "GameplayScene.hpp"

#include "src/omicron/input/Input.hpp"

#include "src/entities/gameplay/GameplayControl.hpp"
#include "src/entities/gameplay/terrain/Environment.hpp"
#include "src/entities/menu/PauseMenu.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GameplayScene::init()
{
    // effects
    omi::renderSettings.setFilmGrain( 0.05f );

    // add entities
    addEntity( new PauseMenu() );
    addEntity( new GameplayControl() );
    addEntity( new Environment() );
}

bool GameplayScene::update()
{
    // TODO: REMOVE THIS
    if ( omi::input::isKeyPressed( omi::input::key::F7 ) )
    {
        return true;
    }

    return false;
}

omi::Scene* GameplayScene::nextScene()
{
    return NULL;
}
