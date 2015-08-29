#include "Artillery.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/terrain/Environment.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const float FALL_SPEED = 0.06F;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Artillery::Artillery( Environment* environment )
    :
    m_environment( environment ),
    m_state      ( unit::STATE_FALLING )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Artillery::init()
{
    // the transform
    m_transform = new omi::Transform(
            "",
            glm::vec3( 25.0F, 60.0F, 50.0F ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_transform );

    // body mesh
    omi::Mesh* bodyMesh =
            omi::ResourceManager::getMesh( "artillery_body", "", m_transform );
    bodyMesh->getMaterial().specular = new omi::Specular(
            256.0F,
            glm::vec3( 1.0F, 1.0F, 1.0F )
    );
    m_components.add( bodyMesh );

    // trail mesh
    m_trail = omi::ResourceManager::getMesh( "entry_trail", "", m_transform );
    m_trail->castShadow = false;
    m_trail->getMaterial().glow =
                new omi::Glow( glm::vec3( 0.2F, 0.2F, 1.0F ), 1.0F );
    m_components.add( m_trail );
}

void Artillery::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    // update based on state
    switch( m_state )
    {
        case unit::STATE_FALLING:
        {
            float x = m_transform->translation.x;
            float y = m_transform->translation.y;
            float z = m_transform->translation.z;

            // check whether this is colliding with a block
            if ( m_environment->getBlock( x, y, z ) != NULL )
            {
                m_state = unit::STATE_INPLACE;
                m_trail->visible = false;
            }

            // move down
            m_transform->translation.y -=
                    FALL_SPEED * omi::fpsManager.getTimeScale();
            break;
        }
        case unit::STATE_INPLACE:
        {
            break;
        }
    };
}
