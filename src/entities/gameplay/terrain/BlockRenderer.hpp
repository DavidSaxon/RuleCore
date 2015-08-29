#ifndef RULECORE_ENTITIES_GAMEPLAY_TERRAIN_BLOCKRENDERER_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_TERRAIN_BLOCKRENDERER_HPP_

#include "src/omicron/entity/Entity.hpp"

#include <map>

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

namespace block
{

// the directions of block faces
enum FaceDirection
{
    FACE_UP = 0,
    FACE_DOWN,
    FACE_NORTH,
    FACE_EAST,
    FACE_SOUTH,
    FACE_WEST
};

// the block types
enum Type
{
    TYPE_GRASS = 0,
    TYPE_DIRT,
    TYPE_MOUNTAIN_GRASS,
    TYPE_DIRTY_SNOW,
    TYPE_SNOW,
    TYPE_GRAVEL,
    TYPE_STONE
};


} // namespace block

/*******************************************************************\
| For optimised block rendering (basically batch rendering blocks). |
\*******************************************************************/
class BlockRenderer : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    BlockRenderer();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

    /** Adds a block face to be rendered for the given type */
    void addFace(
            const glm::vec3& pos,
            block::FaceDirection faceDirection,
            block::Type blockType );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // a mapping from blocks types to their respective geometry
    std::map< block::Type, omi::Geometry* > m_typeToGeo;

    // whether the geometry has been cleared this frame or not
    bool m_clearedThisFrame;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void clearGeo();
};

#endif
