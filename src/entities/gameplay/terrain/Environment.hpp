#ifndef RULECORE_ENTITIES_GAMEPLAY_TERRAIN_ENVIRONMENT_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_TERRAIN_ENVIRONMENT_HPP_

#include "src/omicron/entity/Entity.hpp"

#include <vector>

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class GroundBlock;

/**************************************\
| Manages the environment of the game. |
\**************************************/
class Environment : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Environment();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the 3 dimensional grid containing the terrain cubes
    std::vector< GroundBlock* > m_terrain;

    // the transform for sunlight
    omi::Transform* m_sunT;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void initCompoents();
};

#endif
