#ifndef RULECORE_ENTITIES_GAMEPLAY_UNIT_PROJEXPLOSION_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_UNIT_PROJEXPLOSION_HPP_

#include "src/omicron/entity/Entity.hpp"

class ProjExplosion : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    ProjExplosion( const glm::vec3& pos, unsigned type );

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

    // the type
    unsigned m_type;

    omi::Transform* m_transform;
    omi::Mesh* m_mesh;

    omi::PointLight* m_light;

    glm::vec3 m_colour;

    float m_progress;
};

#endif
