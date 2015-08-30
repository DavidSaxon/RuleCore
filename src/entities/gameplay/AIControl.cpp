#include "AIControl.hpp"

#include "src/entities/gameplay/unit/Artillery.hpp"

#include "src/data/Globals.hpp"

#include <sstream>

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

AIControl::AIControl( Environment* environment )
    :
    m_environment( environment ),
    m_nextUpdateTime( 1.0F ),
    m_updateCounter( 0.0F ),
    m_reinforce    ( 0.0F ),
    m_doneReinforce( false ),
    m_reinTextTime( 0.0F )
{
    // add the units
    for ( size_t i = 0; i < 8; ++i )
    {
        Artillery* a = new Artillery(
                unit::PLAYER,
                rand() % 50,
                ( rand() % 25 ) + 6,
                m_environment
        );
        m_player.push_back( a );
        addEntity( a );
    }

    for ( size_t i = 0; i < 8; ++i )
    {
        Artillery* a = new Artillery(
                unit::ENEMY,
                rand() % 50,
                94 - ( ( rand() % 25 ) + 1 ),
                m_environment
        );
        m_enemy.push_back( a );
        addEntity( a );
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void AIControl::init()
{
    // add text
    omi::Transform* t1 = new omi::Transform(
            "",
            glm::vec3( -1.6F, 0.9F, 0.0F ),
            glm::vec3(),
            glm::vec3( 0.75F, 0.75F, 0.75F )
    );
    m_components.add( t1 );

    m_textP = omi::ResourceManager::getText( "UI_text", "", t1 );
    m_textP->gui = true;
    m_textP->setString( "Player: 8" );
    m_components.add( m_textP );

    // add text
    omi::Transform* t2 = new omi::Transform(
            "",
            glm::vec3( -1.6F, 0.8F, 0.0F ),
            glm::vec3(),
            glm::vec3( 0.75F, 0.75F, 0.75F )
    );
    m_components.add( t2 );

    m_textE = omi::ResourceManager::getText( "UI_text", "", t2 );
    m_textE->gui = true;
    m_textE->setString( "Enemy: 8" );
    m_components.add( m_textE );


    // add text
    omi::Transform* t3 = new omi::Transform(
            "",
            glm::vec3( 0.0F, 0.85F, 0.0F ),
            glm::vec3(),
            glm::vec3( 1.0F, 1.0F, 1.0F )
    );
    m_components.add( t3 );

    m_reinText = omi::ResourceManager::getText( "UI_text", "", t3 );
    m_reinText->gui = true;
    m_reinText->setString( "Reinforcements!" );
    m_reinText->setHorCentred( true );
    m_reinText->visible = false;
    m_components.add( m_reinText );

}

void AIControl::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    m_reinforce += 0.0002F * omi::fpsManager.getTimeScale();
    if ( !m_doneReinforce && m_reinforce >= 1.0F )
    {
        m_doneReinforce = true;
        m_reinText->visible = true;

        for ( size_t i = 0; i < 6; ++i )
        {
            Artillery* a = new Artillery(
                    unit::PLAYER,
                    rand() % 50,
                    ( rand() % 25 ) + 6,
                    m_environment
            );
            m_player.push_back( a );
            addEntity( a );
        }

        for ( size_t i = 0; i < 6; ++i )
        {
            Artillery* a = new Artillery(
                    unit::ENEMY,
                    rand() % 50,
                    94 - ( ( rand() % 25 ) + 1 ),
                    m_environment
            );
            m_enemy.push_back( a );
            addEntity( a );
        }
    }
    else if ( m_doneReinforce )
    {
        m_reinTextTime += 0.002F * omi::fpsManager.getTimeScale();

        if ( m_reinTextTime >= 1.0F )
        {
            m_reinText->visible = false;
            m_doneReinforce = false;
            m_reinforce = 0.0F;
            m_reinTextTime = 0.0F;
        }
    }

    // check over player units
    std::vector< Artillery* >::iterator pit = m_player.begin();
    for( ; pit != m_player.end(); )
    {
        if ( ( *pit )->hp <= 0 )
        {
            ( *pit )->hardRemove();
            pit = m_player.erase( pit );
        }
        else
        {
            ++pit;
        }
    }

    std::vector< Artillery* >::iterator eit = m_enemy.begin();
    for( ; eit != m_enemy.end(); )
    {
        if ( ( *eit )->hp <= 0 )
        {
            ( *eit )->hardRemove();
            eit = m_enemy.erase( eit );
        }
        else
        {
            ++eit;
        }
    }


    // control enemies
    m_updateCounter += 0.005F * omi::fpsManager.getTimeScale();
    if ( m_updateCounter >= m_nextUpdateTime )
    {
        m_updateCounter = 0.0F;
        float r = ( static_cast< float >( rand() % 1000 ) / 1000.0F ) - 0.5F;
        r *= 0.1F;
        m_nextUpdateTime = 1.0F + r;

        // perform AI update
        if ( m_enemy.size() > 0 )
        {
            changeState();
            changeAngle();
        }
    }

    // update the text
    std::stringstream ssP;
    ssP << "Player: " << m_player.size();
    m_textP->setString( ssP.str() );

    std::stringstream ssE;
    ssE << "Enemy: " << m_enemy.size();
    m_textE->setString( ssE.str() );
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void AIControl::changeState()
{
    // choose a random unit
    Artillery* a = m_enemy[ rand() % m_enemy.size() ];

    // chose a random state
    if ( rand() % 2 == 0 )
    {
        a->setRule( unit::RULE_DOWN );
    }
    else
    {
        a->setRule( unit::RULE_UP );
    }
}

void AIControl::changeAngle()
{
    if ( m_player.size() == 0 )
    {
        return;
    }

    // choose a random unit
    Artillery* a = m_enemy[ rand() % m_enemy.size() ];

    // choose random player unit
        // choose a random unit
    Artillery* p = m_player[ rand() % m_enemy.size() ];

    // get the angle between the two
    float angle = omi::vecutil::angleBetween(
            p->getPos().xz(), a->getPos().xz()
    );

    a->setAngle( 90.0F - angle );
}
