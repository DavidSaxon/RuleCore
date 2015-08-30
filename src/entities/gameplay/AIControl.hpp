#ifndef RULECORE_ENTITIES_GAMEPLAY_AICONTROL_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_AICONTROL_HPP_

#include "src/omicron/entity/Entity.hpp"

#include <vector>

class Artillery;
class Environment;

class AIControl : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    AIControl( Environment* environment );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    Environment* m_environment;

    // units
    std::vector< Artillery* > m_player;
    std::vector< Artillery* > m_enemy;

    omi::Text* m_textP;
    omi::Text* m_textE;

    float m_nextUpdateTime;
    float m_updateCounter;

    float m_reinforce;
    bool m_doneReinforce;
    float m_reinTextTime;

    omi::Text* m_reinText;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void changeState();

    void changeAngle();
};

#endif
