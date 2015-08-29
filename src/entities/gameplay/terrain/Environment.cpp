#include "Environment.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/terrain/BlockRenderer.hpp"
#include "src/entities/gameplay/terrain/GroundBlock.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const size_t TERRAIN_WIDTH  = 50;
static const size_t TERRAIN_LENGTH = 100;
static const size_t TERRAIN_DEPTH  = 50;

static const float TERRAIN_X_OFFSET = TERRAIN_WIDTH / 2.0;
static const float TERRAIN_Z_OFFSET = TERRAIN_LENGTH / 2.0;
static const float TERRAIN_Y_OFFSET = TERRAIN_DEPTH / 2.0;
static const glm::vec3 TERRAIN_OFFSET(
        0.0F, 0.0F, 0.0F );

static const float SUN_DISTANCE = 130.0F;
static const float SUN_SPEED = 0.1F;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Environment::Environment()
    :
    m_sunRot( 0.0F )
{
    // set up the initial size of the terrain vector
    for ( size_t w = 0; w < TERRAIN_WIDTH; ++w )
    {
        m_terrain.push_back( std::vector< std::vector< GroundBlock* > >() );
        for ( size_t l = 0; l < TERRAIN_LENGTH; ++l )
        {
            m_terrain[ w ].push_back( std::vector< GroundBlock* >() );
            for ( size_t d = 0; d < TERRAIN_DEPTH; ++d )
            {
                m_terrain[ w ][ l ].push_back( NULL );
            }
        }
    }

    // ambient light levels
    omi::renderSettings.setAmbientStrength( 0.6F );
    omi::renderSettings.setAmbientColour( glm::vec3( 1.0F, 1.0F, 1.0F ) );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Environment::init()
{
    // TODO: pass offsets to the renderer
    // create the block render
    m_blockRenderer = new BlockRenderer();
    addEntity( m_blockRenderer );

    initCompoents();

    generateTerrain();
}

void Environment::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    // rotate the sun
    m_sunRot += SUN_SPEED * omi::fpsManager.getTimeScale();
    if ( m_sunRot >= 360.0F )
    {
        m_sunRot -= 360.0F;
    }

    // position the sun
    m_sunT->translation.z = util::math::sind( m_sunRot );
    m_sunT->translation.y = util::math::cosd( m_sunRot );
    m_sunGlobeT->translation.z = m_sunT->translation.z * SUN_DISTANCE;
    m_sunGlobeT->translation.y = m_sunT->translation.y * SUN_DISTANCE;
}

GroundBlock* Environment::getBlock( float x, float y, float z )
{
    // truncate
    size_t t_x = static_cast< size_t >( x );
    size_t t_y = static_cast< size_t >( y );
    size_t t_z = static_cast< size_t >( z );

    // check bounds
    if ( t_x >= TERRAIN_WIDTH )
    {
        return NULL;
    }
    if ( t_z >= TERRAIN_LENGTH )
    {
        return NULL;
    }
    if ( t_y >= TERRAIN_DEPTH )
    {
        return NULL;
    }

    // get the cube
    return m_terrain[ t_x ][ t_z ][ t_y ];
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Environment::initCompoents()
{
    // the sun globe
    m_sunGlobeT = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, -130.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_sunGlobeT );
    omi::Mesh* sunMesh =
            omi::ResourceManager::getMesh( "sun", "", m_sunGlobeT );
    sunMesh->castShadow = false;
    sunMesh->getMaterial().glow =
                new omi::Glow( glm::vec3( 1.0F, 1.0F, 1.0F ), 1.0F );
    m_components.add( sunMesh );

    // the sun light
    m_sunT = new omi::Transform(
            "",
            glm::vec3( 0.3f, 0.5f, 1.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_sunT );
    omi::DirectionalLight* sunLight = new omi::DirectionalLight(
            "",
            m_sunT,
            1.4f,
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    sunLight->setCastShadow( true );
    m_components.add( sunLight );
}

void Environment::generateTerrain()
{
    // fill half the terrain
    for ( size_t w = 0; w < TERRAIN_WIDTH; ++w )
    {
        for ( size_t l = 0; l < TERRAIN_LENGTH; ++l )
        {
            for ( size_t d = 0; d < TERRAIN_DEPTH; ++d )
            {
                if ( d > TERRAIN_DEPTH / 2 )
                {
                    continue;
                }

                GroundBlock* block = new GroundBlock(
                        w,
                        d,
                        l,
                        TERRAIN_OFFSET,
                        &m_terrain,
                        TERRAIN_WIDTH,
                        TERRAIN_LENGTH,
                        TERRAIN_DEPTH,
                        m_blockRenderer
                );
                m_terrain[ w ][ l ][ d ] = block;
                addEntity( block );
            }
        }
    }

    // generate some mountains
    unsigned mountainCount = ( rand() % 30 ) + 25;
    for ( size_t m = 0; m < mountainCount; ++m )
    {
        generateMountain(
                rand() %  TERRAIN_WIDTH,
                rand() %  TERRAIN_LENGTH,
                ( rand() % static_cast< size_t >( TERRAIN_DEPTH / 2.2F ) ) +
                        ( TERRAIN_DEPTH / 2 )
        );
    }

    // generate some pits
    unsigned pitCount = ( rand() % 7 ) + 5;
    for ( size_t m = 0; m < pitCount; ++m )
    {
        generatePit(
                rand() %  TERRAIN_WIDTH,
                rand() %  TERRAIN_LENGTH,
                ( TERRAIN_DEPTH / 2 ) -
                ( rand() % static_cast< size_t >( TERRAIN_DEPTH / 2.2F ) )

        );
    }
}

void Environment::generateMountain( size_t x, size_t z, size_t height )
{
    if ( !generateColoumn( x, z, height ) )
    {
        return;
    }

    if ( x != 0 )
    {
        generateMountain( x - 1, z, height - ( ( rand() % 2 ) + 1 )  );
    }
    if ( x != TERRAIN_WIDTH - 1 )
    {
        generateMountain( x + 1, z, height - ( ( rand() % 2 ) + 1 )  );
    }
    if ( z != 0 )
    {
        generateMountain( x, z - 1, height - ( ( rand() % 2 ) + 1 )  );
    }
    if ( z != TERRAIN_LENGTH - 1 )
    {
        generateMountain( x, z + 1, height - ( ( rand() % 2 ) + 1 )  );
    }
}

bool Environment::generateColoumn( size_t x, size_t z, size_t height )
{
    // generate blocks until we reach the bottom
    bool gen = false;
    for ( int y = height; y >= 0; --y )
    {
        // bail out if we find a block
        if ( m_terrain[ x ][ z ][ y ] != NULL )
        {
            break;
        }
        gen = true;

        GroundBlock* block = new GroundBlock(
                x,
                static_cast< size_t >( y ),
                z,
                TERRAIN_OFFSET,
                &m_terrain,
                TERRAIN_WIDTH,
                TERRAIN_LENGTH,
                TERRAIN_DEPTH,
                m_blockRenderer
        );
        m_terrain[ x ][ z ][ y ] =  block;
        addEntity( block );
    }

    return gen;
}

void Environment::generatePit( size_t x, size_t z, size_t height )
{
    if ( !removeColumn( x, z, height ) )
    {
        return;
    }

    if ( x != 0 )
    {
        generatePit( x - 1, z, height + ( ( rand() % 2 ) + 1 )  );
    }
    if ( x != TERRAIN_WIDTH - 1 )
    {
        generatePit( x + 1, z, height + ( ( rand() % 2 ) + 1 )  );
    }
    if ( z != 0 )
    {
        generatePit( x, z - 1, height + ( ( rand() % 2 ) + 1 )  );
    }
    if ( z != TERRAIN_LENGTH - 1 )
    {
        generatePit( x, z + 1, height + ( ( rand() % 2 ) + 1 )  );
    }

}

bool Environment::removeColumn( size_t x, size_t z, size_t height )
{
    // remove blocks until we reach the bottom
    bool removed = false;
    for ( int y = height; y < TERRAIN_DEPTH; ++y )
    {
        // bail out if we find a null
        if ( m_terrain[ x ][ z ][ y ] == NULL )
        {
            break;
        }
        removed = true;

        // remove the block
        m_terrain[ x ][ z ][ y ]->blockRemove();
        m_terrain[ x ][ z ][ y ] = NULL;
    }

    return removed;
}
