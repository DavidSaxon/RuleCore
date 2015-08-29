#include "GroundBlock.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GroundBlock::GroundBlock( const glm::vec3& pos )
    :
    m_pos( pos )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GroundBlock::init()
{
    // transform
    omi::Transform* transform = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
        );
    m_components.add( transform );

    // mesh
    omi::Mesh* mesh =
            omi::ResourceManager::getMesh( "std_ground_cube", "", transform );
    m_components.add( mesh );
}

void GroundBlock::update()
{

}
