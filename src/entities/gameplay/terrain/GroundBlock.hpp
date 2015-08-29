#ifndef RULECORE_ENTITIES_GAMEPLAY_TERRAIN_GROUNDBLOCK_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_TERRAIN_GROUNDBLOCK_HPP_

#include "src/omicron/entity/Entity.hpp"

#include <map>

#include "src/entities/gameplay/terrain/BlockRenderer.hpp"

/*************************\
| A standard ground block |
\*************************/
class GroundBlock : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    GroundBlock(
            size_t x,
            size_t y,
            size_t z,
            const glm::vec3& offset,
            std::vector< std::vector< std::vector< GroundBlock* > > >* world,
            size_t worldWidth,
            size_t worldLength,
            size_t worldDepth,
            BlockRenderer* renderer );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

    void blockRemove();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the position of the block
    size_t m_x;
    size_t m_y;
    size_t m_z;
    // the offset
    glm::vec3 m_offset;

    // the type of the block
    block::Type m_type;

    // the grid containing the world
    std::vector< std::vector< std::vector< GroundBlock* > > >* m_world;
    // the dimensions of the world
    size_t m_worldWidth;
    size_t m_worldLength;
    size_t m_worldDepth;

    // the renderer to pass geo data to
    BlockRenderer* m_renderer;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void evalulateType();

    // check face for world data
    void addFace( block::FaceDirection face );
};

#endif
