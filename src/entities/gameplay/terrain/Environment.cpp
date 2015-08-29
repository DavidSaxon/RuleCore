#include "Environment.hpp"

#include "src/entities/gameplay/terrain/GroundBlock.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const size_t TERRAIN_WIDTH  = 4;
static const size_t TERRAIN_LENGTH = 4;
static const size_t TERRAIN_DEPTH  = 4;

static const size_t TERRAIN_X_OFFSET = TERRAIN_WIDTH / 2;
static const size_t TERRAIN_Z_OFFSET = TERRAIN_LENGTH / 2;
static const size_t TERRAIN_Y_OFFSET = TERRAIN_DEPTH / 2;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Environment::Environment()
{
    // set up the initial size of the terrain vector
    size_t terrainSize = TERRAIN_WIDTH * TERRAIN_LENGTH * TERRAIN_DEPTH;
    m_terrain.resize( terrainSize, NULL );

    // ambient light levels
    omi::renderSettings.setAmbientStrength( 0.5F );
    omi::renderSettings.setAmbientColour( glm::vec3( 1.0F, 1.0F, 1.0F ) );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Environment::init()
{
    initCompoents();

    // TODO: generate level

    // TODO: TESTING: REMOVE ME
    // add some terrain
    for ( size_t w = 0; w < TERRAIN_WIDTH; ++w )
    {
        for ( size_t l = 0; l < TERRAIN_LENGTH; ++l )
        {
            for ( size_t d = 0; d < TERRAIN_DEPTH; ++d )
            {
                glm::vec3 blockPos( w, d, l );
                blockPos.x -= TERRAIN_X_OFFSET;
                blockPos.z -= TERRAIN_Z_OFFSET;
                blockPos.y -= TERRAIN_Y_OFFSET;

                GroundBlock* block = new GroundBlock( blockPos );
                m_terrain[ w * l * d ] = block;
                addEntity( block );
            }
        }
    }
}

void Environment::update()
{
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Environment::initCompoents()
{
    // the sun light
    m_sunT = new omi::Transform(
            "",
            glm::vec3( 1.0f, 0.5f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_sunT );
    omi::DirectionalLight* sunLight = new omi::DirectionalLight(
            "",
            m_sunT,
            0.8f,
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    sunLight->setCastShadow( true );
    m_components.add( sunLight );
}
