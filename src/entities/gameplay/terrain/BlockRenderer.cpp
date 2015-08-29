#include "BlockRenderer.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const float BLOCK_SIZE = 1.0F;
static const float BLOCK_HALF = BLOCK_SIZE / 2.0F;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

BlockRenderer::BlockRenderer()
    :
    m_clearedThisFrame( false )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void BlockRenderer::init()
{
    // create the placeholder meshes for the different types

    // grass
    omi::Geometry* grassGeo = new omi::Geometry();
    omi::Mesh* grassMesh = new omi::Mesh(
            "", 0, NULL,
            grassGeo,
            omi::ResourceManager::getMaterial( "block_grass_1" )
    );
    m_components.add( grassMesh );
    m_typeToGeo[ block::TYPE_GRASS ] = grassGeo;

    // dirt
    omi::Geometry* dirtGeo = new omi::Geometry();
    omi::Mesh* dirtMesh = new omi::Mesh(
            "", 0, NULL,
            dirtGeo,
            omi::ResourceManager::getMaterial( "block_dirt_1" )
    );
    m_components.add( dirtMesh );
    m_typeToGeo[ block::TYPE_DIRT ] = dirtGeo;

    // mountain grass
    omi::Geometry* mountainGrassGeo = new omi::Geometry();
    omi::Mesh* mountainGrassMesh = new omi::Mesh(
            "", 0, NULL,
            mountainGrassGeo,
            omi::ResourceManager::getMaterial( "block_mountain_grass_1" )
    );
    m_components.add( mountainGrassMesh );
    m_typeToGeo[ block::TYPE_MOUNTAIN_GRASS ] = mountainGrassGeo;

    // dirty snow
    omi::Geometry* dirtySnowGeo = new omi::Geometry();
    omi::Mesh* dirtySnowMesh = new omi::Mesh(
            "", 0, NULL,
            dirtySnowGeo,
            omi::ResourceManager::getMaterial( "block_dirty_snow_1" )
    );
    m_components.add( dirtySnowMesh );
    m_typeToGeo[ block::TYPE_DIRTY_SNOW ] = dirtySnowGeo;

    // snow
    omi::Geometry* snowGeo = new omi::Geometry();
    omi::Mesh* snowMesh = new omi::Mesh(
            "", 0, NULL,
            snowGeo,
            omi::ResourceManager::getMaterial( "block_snow_1" )
    );
    m_components.add( snowMesh );
    m_typeToGeo[ block::TYPE_SNOW ] = snowGeo;

    // gravel
    omi::Geometry* gravelGeo = new omi::Geometry();
    omi::Mesh* gravelMesh = new omi::Mesh(
            "", 0, NULL,
            gravelGeo,
            omi::ResourceManager::getMaterial( "block_gravel_1" )
    );
    m_components.add( gravelMesh );
    m_typeToGeo[ block::TYPE_GRAVEL ] = gravelGeo;

    // stone
    omi::Geometry* stoneGeo = new omi::Geometry();
    omi::Mesh* stoneMesh = new omi::Mesh(
            "", 0, NULL,
            stoneGeo,
            omi::ResourceManager::getMaterial( "block_stone_1" )
    );
    m_components.add( stoneMesh );
    m_typeToGeo[ block::TYPE_STONE ] = stoneGeo;
}

void BlockRenderer::update()
{
    // prepare to clear again
    m_clearedThisFrame = false;
}

void BlockRenderer::addFace(
        const glm::vec3& pos,
        block::FaceDirection faceDirection,
        block::Type blockType )
{
    // do we need to clear the blocks?
    if ( !m_clearedThisFrame )
    {
        clearGeo();
        m_clearedThisFrame = true;
    }

    // shorthand
    float x = pos.x;
    float y = pos.y;
    float z = pos.z;

    // add some vertices and normals
    switch( faceDirection )
    {
        case block::FACE_UP:
        {
            // vertices
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );

            // normals
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 1.0F, 0.0F ) );

            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 1.0F, 0.0F ) );
            break;
        }
        case block::FACE_DOWN:
        {
            // vertices
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );

            // normals
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, -1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, -1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, -1.0F, 0.0F ) );

            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, -1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, -1.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, -1.0F, 0.0F ) );
            break;
        }
        case block::FACE_NORTH:
        {
            // vertices
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );

            // normals
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, -1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, -1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, -1.0F ) );

            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, -1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, -1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, -1.0F ) );
            break;
        }
        case block::FACE_EAST:
        {
            // vertices
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );

            // normals
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 1.0F, 0.0F, 0.0F ) );

            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 1.0F, 0.0F, 0.0F ) );
            break;
        }
        case block::FACE_SOUTH:
        {
            // vertices
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x + BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );

            // normals
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, 1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, 1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, 1.0F ) );

            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, 1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, 1.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( 0.0F, 0.0F, 1.0F ) );
            break;
        }
        case block::FACE_WEST:
        {
            // vertices
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z - BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y - BLOCK_HALF,
                    z + BLOCK_HALF
            ) );
            m_typeToGeo[ blockType ]->vertices.push_back( glm::vec3(
                    x - BLOCK_HALF,
                    y + BLOCK_HALF,
                    z + BLOCK_HALF
            ) );

            // normals
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( -1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( -1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( -1.0F, 0.0F, 0.0F ) );

            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( -1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( -1.0F, 0.0F, 0.0F ) );
            m_typeToGeo[ blockType ]->normals.push_back(
                    glm::vec3( -1.0F, 0.0F, 0.0F ) );
            break;
        }
        default:
        {
            // do nothing
            break;
        }
    }

    // add uvs
    m_typeToGeo[ blockType ]->uv.push_back( glm::vec2( 0.0F, 1.0F ) );
    m_typeToGeo[ blockType ]->uv.push_back( glm::vec2( 0.0F, 0.0F ) );
    m_typeToGeo[ blockType ]->uv.push_back( glm::vec2( 1.0F, 0.0F ) );
    m_typeToGeo[ blockType ]->uv.push_back( glm::vec2( 1.0F, 0.0F ) );
    m_typeToGeo[ blockType ]->uv.push_back( glm::vec2( 1.0F, 1.0F ) );
    m_typeToGeo[ blockType ]->uv.push_back( glm::vec2( 0.0F, 1.0F ) );

    // add normals
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void BlockRenderer::clearGeo()
{
    std::map< block::Type, omi::Geometry* >::iterator it = m_typeToGeo.begin();
    for( ; it != m_typeToGeo.end(); ++it )
    {
        // clear the geo
        it->second->vertices.clear();
        it->second->uv.clear();
        it->second->normals.clear();
    }
}
