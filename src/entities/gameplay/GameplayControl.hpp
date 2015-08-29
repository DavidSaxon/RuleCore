#ifndef RULECORE_ENTITIES_GAMEPLAY_GAMEPLAYCONTROL_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_GAMEPLAYCONTROL_HPP_

#include "src/omicron/entity/Entity.hpp"

class GameplayControl : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    GameplayControl();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // camera translations
    omi::Transform* m_rotateT;
    omi::Transform* m_transT;

    // the current zoom amount of the camera
    float m_camZoom;
    // the current elevation of the camera
    float m_camElevation;

    // is true if the look control key is down
    float m_lookControlDown;
    // the current position the mouse is locked at
    glm::vec2 m_mouseLockPos;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void lookControl();

    void initComponents();
};

#endif
