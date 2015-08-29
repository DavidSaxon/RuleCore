#ifndef RULECORE_ENTITIES_GAMEPLAY_TERRAIN_GROUNDBLOCK_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_TERRAIN_GROUNDBLOCK_HPP_

#include "src/omicron/entity/Entity.hpp"

class GroundBlock : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    GroundBlock( const glm::vec3& pos );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the position of the block
    glm::vec3 m_pos;
};

#endif
