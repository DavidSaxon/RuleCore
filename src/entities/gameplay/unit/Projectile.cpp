#include "Projectile.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/terrain/Environment.hpp"
#include "src/entities/gameplay/terrain/GroundBlock.hpp"
#include "src/entities/gameplay/unit/ProjExplosion.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const float TURN_SPEED = 0.65F;
static const float MOVE_SPEED = 0.35F;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Projectile::Projectile(
        const glm::vec3& pos,
        float angle,
        bool invert,
        unsigned type,
        Environment* environment )
    :
    m_environment( environment ),
    m_pos        ( pos ),
    m_angle      ( angle ),
    m_tilt       ( 80.0F ),
    m_invert     ( invert ),
    m_type       ( type ),
    m_firstCheck ( true )
{
    // randomise tilt and turn speed
    m_tilt += ( rand() % 20 ) - 10;
    float r = ( static_cast< float >( rand() % 1000 ) / 5000.0F ) - 0.1F;
    m_turnSpeed = TURN_SPEED + r;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Projectile::init()
{
    // transform
    m_transform = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_transform );

    // TODO: assign
    m_colour = glm::vec3( 0.3F, 0.1F, 1.0F );
    if ( m_type == 1 )
    {
        m_colour = glm::vec3( 1.0F, 0.1F, 0.1F );
    }

    // light
    omi::PointLight* light = new omi::PointLight(
            "",
            m_transform,
            1.0F,
            m_colour,
            0.0f,
            0.03f,
            0.008f
    );
    m_components.add( light );

    // mesh
    omi::Mesh* mesh =
            omi::ResourceManager::getMesh( "unit_projectile", "", m_transform );
    mesh->castShadow = false;
    mesh->getMaterial().glow =
                new omi::Glow( m_colour, 1.0F );
    m_components.add( mesh );
}

void Projectile::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    if ( m_firstCheck )
    {
        m_firstCheck = false;
        return;
    }

    // check the projectile is colliding
    float x = m_transform->translation.x;
    float y = m_transform->translation.y;
    float z = m_transform->translation.z;

    bool strong = false;
    if ( rand() % 2 == 1 )
    {
        strong = true;
    }

    GroundBlock* collideBlock = NULL;

    if ( m_type == 0 )
    {
        collideBlock = m_environment->removeBlock( x, y, z, strong );
    }
    else if ( m_type == 1 )
    {
        collideBlock = m_environment->addBlock( x, y, z, strong );
    }

    if ( collideBlock != NULL || y < -30.0F )
    {
        // add explosion
        addEntity( new ProjExplosion( m_transform->translation, m_type ) );

        // delete me!
        remove();
        return;
    }

    // shift the tilt
    m_tilt -= m_turnSpeed * omi::fpsManager.getTimeScale();
    if ( m_tilt < -90.0F )
    {
        m_tilt = -90.0F;
    }

    // move the projectile along the angle
    float moveSpeed =
            MOVE_SPEED *
            omi::fpsManager.getTimeScale();

    m_transform->translation.y +=
            ( util::math::sind( m_tilt ) * moveSpeed );

    moveSpeed *= util::math::cosd( m_tilt );

    if ( m_invert )
    {
        m_transform->translation.z +=
                util::math::cosd( m_angle ) * moveSpeed;
    }
    else
    {
        m_transform->translation.z +=
                util::math::cosd( m_angle ) * moveSpeed;
    }

    m_transform->translation.x +=
            util::math::sind( m_angle ) * moveSpeed;
}
