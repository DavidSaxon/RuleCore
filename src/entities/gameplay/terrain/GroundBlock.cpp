#include "GroundBlock.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GroundBlock::GroundBlock(
        size_t x,
        size_t y,
        size_t z,
        const glm::vec3& offset,
        std::vector< std::vector< std::vector< GroundBlock* > > >* world,
        size_t worldWidth,
        size_t worldLength,
        size_t worldDepth,
        BlockRenderer* renderer )
    :
    m_x          ( x ),
    m_y          ( y ),
    m_z          ( z ),
    m_offset     ( offset ),
    m_type       ( block::TYPE_GRASS ),
    m_world      ( world ),
    m_worldWidth ( worldWidth ),
    m_worldLength( worldLength ),
    m_worldDepth ( worldDepth ),
    m_renderer   ( renderer )
{
    evalulateType();
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GroundBlock::init()
{
}

void GroundBlock::update()
{
    addFace( block::FACE_UP );
    addFace( block::FACE_DOWN );
    addFace( block::FACE_NORTH );
    addFace( block::FACE_SOUTH );
    addFace( block::FACE_EAST );
    addFace( block::FACE_WEST );

}

void GroundBlock::blockRemove()
{
    remove();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GroundBlock::evalulateType()
{
    m_type = block::TYPE_DIRT;

    size_t half = m_worldDepth / 2;

    size_t grassStart = static_cast< size_t >( half - ( rand() % 3 ) );
    size_t grassEnd = half + 2;

    size_t mountainStart =
            static_cast< size_t >( half + 3 + ( ( rand() % 5 ) - 2 ) );
    size_t mountainEnd =
            static_cast< size_t >( half + 5 + ( ( rand() % 5 ) - 2 ) );

    size_t dirtyStart =
            static_cast< size_t >( half + 6 + ( ( rand() % 5 ) - 2 ) );
    size_t dirtyEnd =
            static_cast< size_t >( half + 9 + ( ( rand() % 5 ) - 2 ) );

    size_t snowStart =
            static_cast< size_t >( half + 10 + ( ( rand() % 5 ) - 2 ) );
    size_t snowEnd =
            static_cast< size_t >( half + 13 + ( ( rand() % 5 ) - 2 ) );

    size_t gravelStart =
            static_cast< size_t >( half - 14 + ( ( rand() % 5 ) - 2 ) );
    size_t gravelEnd =
            static_cast< size_t >( half - 8 + ( ( rand() % 5 ) - 2 ) );

    size_t stoneStart =
            static_cast< size_t >( half - 11 + ( ( rand() % 5 ) - 2 ) );

    if (  m_y >= grassStart && m_y <= grassEnd )
    {
        // check if there is a block above
        if ( m_y == m_worldDepth - 1 ||
             ( *m_world )[ m_x ][ m_z ][ m_y + 1 ] == NULL )
        {
            m_type = block::TYPE_GRASS;
            return;
        }
    }

    if ( m_y >= mountainStart && m_y <= mountainEnd )
    {
        // check if there is a block above
        if ( m_y == m_worldDepth - 1 ||
             ( *m_world )[ m_x ][ m_z ][ m_y + 1 ] == NULL )
        {
            m_type = block::TYPE_MOUNTAIN_GRASS;
            return;
        }
    }

    if ( m_y >= dirtyStart && m_y <= dirtyEnd )
    {
        // check if there is a block above
        m_type = block::TYPE_DIRTY_SNOW;
        return;
    }

    if ( m_y >= snowStart )
    {
        // check if there is a block above
        m_type = block::TYPE_SNOW;
        return;
    }

    if ( m_y >= gravelStart && m_y <= gravelEnd )
    {
        // check if there is a block above
        m_type = block::TYPE_GRAVEL;
        return;
    }
    else if ( m_y < gravelStart )
    {
        // check if there is a block above
        m_type = block::TYPE_STONE;
        return;
    }
}

void GroundBlock::addFace( block::FaceDirection face )
{
    // check if the face should be shown
    bool shouldAdd = false;
    switch( face )
    {
        case block::FACE_UP:
        {
            // is this an edge?
            if ( m_y == m_worldDepth - 1 )
            {
                shouldAdd = true;
                break;
            }

            // check block above?
            if ( ( *m_world )[ m_x ][ m_z ][ m_y + 1 ] == NULL )
            {
                shouldAdd = true;
            }
            break;
        }
        case block::FACE_DOWN:
        {
            // is this an edge?
            if ( m_y == 0 )
            {
                shouldAdd = true;
                break;
            }

            // check block above?
            if ( ( *m_world )[ m_x ][ m_z ][ m_y - 1 ] == NULL )
            {
                shouldAdd = true;
            }
            break;
        }
        case block::FACE_NORTH:
        {
            // is this an edge?
            if ( m_z == 0 )
            {
                shouldAdd = true;
                break;
            }

            // check block above?
            if ( ( *m_world )[ m_x ][ m_z - 1 ][ m_y  ] == NULL )
            {
                shouldAdd = true;
            }
            break;
        }
        case block::FACE_SOUTH:
        {
            // is this an edge?
            if ( m_z == m_worldLength - 1 )
            {
                shouldAdd = true;
                break;
            }

            // check block above?
            if ( ( *m_world )[ m_x ][ m_z + 1 ][ m_y  ] == NULL )
            {
                shouldAdd = true;
            }
            break;
        }
        case block::FACE_EAST:
        {
            // is this an edge?
            if ( m_x == m_worldWidth - 1 )
            {
                shouldAdd = true;
                break;
            }

            // check block above?
            if ( ( *m_world )[ m_x + 1 ][ m_z ][ m_y  ] == NULL )
            {
                shouldAdd = true;
            }
            break;
        }
        case block::FACE_WEST:
        {
            // is this an edge?
            if ( m_x == 0 )
            {
                shouldAdd = true;
                break;
            }

            // check block above?
            if ( ( *m_world )[ m_x - 1 ][ m_z ][ m_y  ] == NULL )
            {
                shouldAdd = true;
            }
            break;
        }
    }

    // add the face?
    if ( shouldAdd )
    {
        glm::vec3 pos( m_x, m_y, m_z );
        m_renderer->addFace( pos - m_offset, face, m_type );
    }
}
