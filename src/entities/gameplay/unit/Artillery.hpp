#ifndef RULECORE_ENTITIES_GAMEPLAY_UNIT_ARTILLERY_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_UNIT_ARTILLERY_HPP_

#include "src/omicron/entity/Entity.hpp"

namespace unit
{

enum Team
{
    PLAYER = 0,
    ENEMY
};

enum State
{
    STATE_FALLING = 0,
    STATE_INPLACE,
    STATE_STD
};

enum Rule
{
    RULE_NONE = 0,
    RULE_DOWN,
    RULE_UP,
    RULE_COUNT
};

} // namespace unit

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class Environment;

class Artillery : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    int hp;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Artillery(
            unit::Team team,
            size_t x,
            size_t z,
            Environment* environment );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

    void hardRemove();

    void setRule( unit::Rule rule );

    void setAngle( float angle );

    const glm::vec3& getPos();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    Environment* m_environment;

    // the team of the unit
    unit::Team m_team;
    // the colour being using
    glm::vec3 m_colour;

    // the current state of the unit
    unit::State m_state;

    // the current rule
    unit::Rule m_rule;

    glm::vec3 m_pos;

    // the transform of the unit
    omi::Transform* m_transform;
    // the land hit transform
    omi::Transform* m_landHitT;

    // the landing light
    omi::PointLight* m_landingLight;

    // selection mesh
    omi::Mesh* m_selectionMesh;
    omi::Mesh* m_outlineMesh;

    omi::Transform* m_ruleT;

    // rule meshes
    omi::Mesh* m_noRuleMesh;
    omi::Mesh* m_downRuleMesh;
    omi::Mesh* m_upRuleMesh;

    // the mesh of the trail
    omi::Mesh* m_trail;
    float m_trailFade;
    // the mesh of the landing hit animation
    omi::Mesh* m_landHit;
    float m_landHitGrow;

    bool m_readyToFire;
    float m_reloadTimer;

    bool m_leftDown;

    bool m_dragging;
    // the current position the mouse is locked at
    glm::vec2 m_mouseLockPos;

    bool m_rightDown;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void fireWeapon();
};


#endif
