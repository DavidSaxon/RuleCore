#include "StartUpScene.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void StartUpScene::init()
{
    // apply settings
    omi::renderSettings.setDepthTest( false );

    // load the needed resources
    omi::ResourceManager::load( resource_group::ALL );
    omi::ResourceManager::load( resource_group::DEBUG );
    omi::ResourceManager::load( resource_group::START_UP );

    // add entities
    m_omicronLogo = new OmicronLogo();
    addEntity( m_omicronLogo );
}

bool StartUpScene::update()
{
    if ( m_omicronLogo->done() )
    {
        // load the next resources we'll need
        omi::ResourceManager::load(resource_group::TEST);
        omi::ResourceManager::load( resource_group::MENU );

        // start up finished
        return true;
    }

    return false;
}

omi::Scene* StartUpScene::nextScene()
{
    // release resources
    omi::ResourceManager::release( resource_group::START_UP );

    // revert settings
    omi::renderSettings.setDepthTest( true );

    return new TestScene();
}
