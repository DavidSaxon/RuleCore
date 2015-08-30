#ifndef RULECORE_ENTITIES_GAMEPLAY_UNIT_PROJECTILE_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_UNIT_PROJECTILE_HPP_

#include "src/omicron/entity/Entity.hpp"

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class Environment;

class Projectile : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Projectile(
            const glm::vec3& pos,
            float angle,
            bool invert,
            unsigned type,
            Environment* environment );

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

    // the position of the projectile
    glm::vec3 m_pos;
    float m_angle;
    // the current title angle the projectile is heading in
    float m_tilt;

    float m_turnSpeed;

    // should movement be inverted?
    bool m_invert;

    unsigned m_type;

    // the transform of the projectile
    omi::Transform* m_transform;

    glm::vec3 m_colour;

    bool m_firstCheck;
};

#endif
