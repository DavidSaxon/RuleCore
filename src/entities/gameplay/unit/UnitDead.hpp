#ifndef RULECORE_ENTITIES_GAMEPLAY_UNIT_UNITDEAD_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_UNIT_UNITDEAD_HPP_

#include "src/omicron/entity/Entity.hpp"

class UnitDead : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    UnitDead( const glm::vec3& pos );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the position of the projectile
    glm::vec3 m_pos;

    omi::Transform* m_transform;
    omi::Mesh* m_mesh;

    omi::PointLight* m_light;

    glm::vec3 m_colour;

    float m_progress;
};

#endif
