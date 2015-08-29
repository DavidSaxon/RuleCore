#ifndef RULECORE_ENTITIES_GAMEPLAY_TERRAIN_ENVIRONMENT_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_TERRAIN_ENVIRONMENT_HPP_

#include "src/omicron/entity/Entity.hpp"

#include <vector>

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class BlockRenderer;
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

    // the render optmiser for blocks
    BlockRenderer* m_blockRenderer;

    // the 3 dimensional grid containing the terrain cubes
    std::vector< std::vector< std::vector< GroundBlock* > > > m_terrain;

    // the transform for sunlight
    omi::Transform* m_sunT;
    // the transform for the sun globe
    omi::Transform* m_sunGlobeT;

    // sun rotation
    float m_sunRot;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void initCompoents();

    void generateTerrain();

    void generateMountain( size_t x, size_t z, size_t height );

    bool generateColoumn( size_t x, size_t z, size_t height );

    void generatePit( size_t x, size_t z, size_t height );

    bool removeColumn( size_t x, size_t z, size_t height );
};

#endif
