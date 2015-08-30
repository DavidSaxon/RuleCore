#include "MainMenu.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

MainMenu::~MainMenu()
{
    m_menuMusic->stop();
}

void MainMenu::init()
{
    // add text
    omi::Transform* t1 = new omi::Transform(
            "",
            glm::vec3( 0.0F, 0.7F, 0.0F ),
            glm::vec3(),
            glm::vec3( 1.0F, 1.0F, 1.0F )
    );
    m_components.add( t1 );

    omi::Text* text1 =
            omi::ResourceManager::getText( "MENU_TITLE_TEXT", "", t1 );
    text1->gui = true;
    text1->setString( "RuleCore" );
    text1->setHorCentred( true );
    // text1->getMaterial().colour = glm::vec4( 0.1F, 0.1F, 1.0F, 1.0F );
    m_components.add( text1 );

    // add text
    omi::Transform* t2 = new omi::Transform(
            "",
            glm::vec3( 0.0F, 0.1F, 0.0F ),
            glm::vec3(),
            glm::vec3( 1.0F, 1.0F, 1.0F )
    );
    m_components.add( t2 );

    omi::Text* text2 =
            omi::ResourceManager::getText( "MAIN_MENU_TEXT", "", t2 );
    text2->gui = true;
    text2->setString( "Press 'A' for generated world" );
    text2->setHorCentred( true );
    m_components.add( text2 );

    // add text
    omi::Transform* t3 = new omi::Transform(
            "",
            glm::vec3( 0.0F, -0.2F, 0.0F ),
            glm::vec3(),
            glm::vec3( 1.0F, 1.0F, 1.0F )
    );
    m_components.add( t3 );

    omi::Text* text3 =
            omi::ResourceManager::getText( "MAIN_MENU_TEXT", "", t3 );
    text3->gui = true;
    text3->setString( "Press 'B' for flat world" );
    text3->setHorCentred( true );
    m_components.add( text3 );

    // add text
    omi::Transform* t4 = new omi::Transform(
            "",
            glm::vec3( 0.0F, -0.7F, 0.0F ),
            glm::vec3(),
            glm::vec3( 1.0F, 1.0F, 1.0F )
    );
    m_components.add( t4 );

    omi::Text* text4 =
            omi::ResourceManager::getText( "MAIN_MENU_TEXT", "", t4 );
    text4->gui = true;
    text4->setString( "Press 'Esc' to exit" );
    text4->setHorCentred( true );
    m_components.add( text4 );

    // music
    m_menuMusic = new omi::Music(
            "", "res/sound/music/menu.ogg", 0.6F, true
    );
    m_menuMusic->play();
}

void MainMenu::update()
{
}
