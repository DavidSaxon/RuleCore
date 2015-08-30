#include "Artillery.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/terrain/Environment.hpp"
#include "src/entities/gameplay/terrain/GroundBlock.hpp"
#include "src/entities/gameplay/unit/Projectile.hpp"
#include "src/entities/gameplay/unit/UnitDead.hpp"
#include "src/omicron/input/Input.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const glm::vec3 PLAYER_COLOUR( 0.2F, 0.2F, 1.0F );
static const glm::vec3 ENEMY_COLOUR( 1.0F, 0.0F, 0.0F );

static const float FALL_SPEED = 0.4F;
static const float TRAIL_FADE_SPEED = 0.01F;
static const float LANDHIT_SPEED = 0.25F;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Artillery::Artillery(
        unit::Team team,
        size_t x,
        size_t z,
        Environment* environment )
    :
    hp           ( 55 ),
    m_environment( environment ),
    m_team       ( team ),
    m_state      ( unit::STATE_FALLING ),
    m_rule       ( unit::RULE_NONE ),
    m_trailFade  ( 1.0F ),
    m_landHitGrow( 0.0F ),
    m_readyToFire( true ),
    m_reloadTimer( 1.0F ),
    m_leftDown   ( false ),
    m_dragging   ( false ),
    m_rightDown  ( false )
{
    switch( m_team )
    {
        case unit::PLAYER:
        {
            m_colour = PLAYER_COLOUR;
            break;
        }
        case unit::ENEMY:
        {
            m_colour = ENEMY_COLOUR;
            break;
        }
    }

    m_pos = glm::vec3( x, 100.0F + ( rand() % 40 ), z );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Artillery::init()
{
    // the transform
    m_transform = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    if ( m_team == unit::ENEMY )
    {
        m_transform->rotation.y = 180.0F;
    }
    m_components.add( m_transform );

    // selection mesh
    m_selectionMesh = omi::ResourceManager::getMesh(
            "unit_selection_box",
            "",
            m_transform
    );
    m_selectionMesh->selectable = true;
    m_selectionMesh->visible = false;
    m_selectionMesh->castShadow = false;
    m_components.add( m_selectionMesh );

    // outline mesh
    m_outlineMesh =
            omi::ResourceManager::getMesh( "unit_outline", "", m_transform );
    m_outlineMesh->getMaterial().glow =
                new omi::Glow( m_colour, 1.0F );
    m_outlineMesh->visible = false;
    m_outlineMesh->castShadow = false;
    m_components.add( m_outlineMesh );

    // rule transform
    m_ruleT = new omi::Transform(
            "",
            m_transform,
            glm::vec3( 0.0F, 0.0F, 0.0F ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );

    // no rule mesh
    m_noRuleMesh =
            omi::ResourceManager::getMesh( "unit_no_rule", "", m_ruleT );
    m_noRuleMesh->getMaterial().glow =
                new omi::Glow( glm::vec3( 1.0F, 1.0F, 1.0F ), 0.5F );
    m_noRuleMesh->visible = false;
    m_noRuleMesh->castShadow = false;
    m_components.add( m_noRuleMesh );

    // down rule mesh
    m_downRuleMesh =
            omi::ResourceManager::getMesh( "unit_down_rule", "", m_ruleT );
    m_downRuleMesh->getMaterial().glow =
                new omi::Glow( glm::vec3( 0.3F, 0.1F, 1.0F ), 0.5F );
    m_downRuleMesh->visible = true;
    m_downRuleMesh->castShadow = false;
    m_components.add( m_downRuleMesh );

    // up rule mesh
    m_upRuleMesh =
            omi::ResourceManager::getMesh( "unit_up_rule", "", m_ruleT );
    m_upRuleMesh->getMaterial().glow =
                new omi::Glow( glm::vec3( 1.0F, 0.1F, 0.1F ), 0.5F );
    m_upRuleMesh->visible = false;
    m_upRuleMesh->castShadow = false;
    m_components.add( m_upRuleMesh );

    // body mesh
    omi::Mesh* bodyMesh =
            omi::ResourceManager::getMesh( "artillery_body", "", m_transform );
    m_components.add( bodyMesh );

    // support mesh
    omi::Mesh* supportMesh = omi::ResourceManager::getMesh(
            "artillery_support", "", m_transform );
    m_components.add( supportMesh );

    // mount mesh
    omi::Mesh* mountMesh = omi::ResourceManager::getMesh(
            "artillery_mount", "", m_transform );
    mountMesh->getMaterial().colour = glm::vec4( m_colour, 1.0F );
    m_components.add( mountMesh );

    // barrel mesh
    omi::Mesh* barrelMesh = omi::ResourceManager::getMesh(
            "artillery_barrel", "", m_transform );
    m_components.add( barrelMesh );

    // landing light
    m_landingLight = new omi::PointLight(
            "landing_light",
            m_transform,
            1.0F,
            m_colour,
            0.0f,
            0.03f,
            0.003f
    );
    m_components.add( m_landingLight );

    // trail mesh
    m_trail = omi::ResourceManager::getMesh( "entry_trail", "", m_transform );
    m_trail->castShadow = false;
    m_trail->getMaterial().glow =
                new omi::Glow( m_colour, 1.0F );
    m_components.add( m_trail );

    // land hit
    m_landHitT = new omi::Transform(
            "",
            m_transform,
            glm::vec3(),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_landHitT );

    m_landHit = omi::ResourceManager::getMesh(
            "unit_land_hit",
            "",
            m_landHitT
    );
    m_landHit->castShadow = false;
    m_landHit->getMaterial().glow =
                new omi::Glow( m_colour, 1.0F );
    m_landHit->visible = false;
    m_components.add( m_landHit );

    // play entry sound
    omi::SoundPool::play(
            omi::ResourceManager::getSound( "unit_entry" ),
            false,
            0.7F
    );
}

void Artillery::update()
{
    // don't do anything if we're paused
    if ( global::pause )
    {
        return;
    }

    // left down
    if ( omi::input::mousePressed( omi::input::mouse_button::LEFT ) &&
         !m_leftDown )
    {
        m_leftDown = true;

        // selecting this
        if ( m_selectionMesh->selected && m_team == unit::PLAYER )
        {
            if ( !m_dragging )
            {
                m_dragging = true;
                // lock the cursor
                omi::systemSettings.setCursorLocked( true );
                m_mouseLockPos = omi::input::getMousePos();
                omi::systemSettings.setCursorLockPosition( m_mouseLockPos );
            }
        }
    }
    // left up
    if ( !omi::input::mousePressed( omi::input::mouse_button::LEFT ) &&
         m_leftDown )
    {
        m_leftDown = false;
        m_dragging = false;
        omi::systemSettings.setCursorLocked( false );
    }

    // rotate based on mouse lock
    if ( m_dragging )
    {
        m_transform->rotation.y +=
            ( m_mouseLockPos.x - omi::input::getMousePos().x ) * 0.035F;

        if ( m_transform->rotation.y < -45.0F )
        {
            m_transform->rotation.y = -45.0F;
        }
        if ( m_transform->rotation.y > 45.0F )
        {
            m_transform->rotation.y = 45.0F;
        }
    }

    // right down
    if ( omi::input::mousePressed( omi::input::mouse_button::RIGHT ) &&
         !m_rightDown )
    {
        m_rightDown = true;
        if ( m_selectionMesh->selected && m_team == unit::PLAYER )
        {
            m_rule = static_cast< unit::Rule >(
                    ( m_rule + 1 ) % unit::RULE_COUNT
            );
        }
    }
    if ( !omi::input::mousePressed( omi::input::mouse_button::RIGHT ) )
    {
        m_rightDown = false;
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
            GroundBlock* collideBlock = m_environment->getBlock( x, y, z );
            if ( collideBlock != NULL )
            {
                m_state = unit::STATE_INPLACE;
                // land hit start
                m_landHit->visible = true;
                // move to truncated position
                m_transform->translation = glm::vec3(
                        collideBlock->getX(),
                        collideBlock->getY() + 1.0F,
                        collideBlock->getZ()
                );

                // m_outlineMesh->visible = true;

                // play sounds
                std::string hitSound( "land_hit_1" );
                if ( rand() % 2 == 1 )
                {
                    hitSound = "land_hit_2";
                }
                omi::SoundPool::play(
                        omi::ResourceManager::getSound( hitSound ),
                        false,
                        !.0F
                );
            }
            else
            {
                // move down
                m_transform->translation.y -=
                        FALL_SPEED * omi::fpsManager.getTimeScale();
            }
            break;
        }
        case unit::STATE_INPLACE:
        {
            // fade the trail
            m_trailFade -= TRAIL_FADE_SPEED * omi::fpsManager.getTimeScale();
            if ( m_trailFade <= 0.0F )
            {
                m_trail->visible = false;
                m_trail->getMaterial().glow = NULL;
                m_landHit->visible = false;
                m_landHit->getMaterial().glow = NULL;

                m_landingLight->active = false;

                m_state = unit::STATE_STD;
            }
            else
            {
                delete m_trail->getMaterial().glow;
                m_trail->getMaterial().glow = new omi::Glow(
                        m_colour,
                        m_trailFade
                );
                m_trail->getMaterial().colour.a = m_trailFade;

                delete m_landHit->getMaterial().glow;
                m_landHit->getMaterial().glow = new omi::Glow(
                        m_colour,
                        m_trailFade
                );
                m_landHit->getMaterial().colour.a = m_trailFade;

                m_landingLight->setPower( m_trailFade );

                // expand the trail
                m_landHitGrow += LANDHIT_SPEED * omi::fpsManager.getTimeScale();
                m_landHitT->scale.x = m_landHitGrow;
                m_landHitT->scale.z = m_landHitGrow;
            }

            break;
        }
        case unit::STATE_STD:
        {
            // fire?
            fireWeapon();

            break;
        }
    };

    if ( m_state == unit::STATE_FALLING )
    {
        return;
    }

    // move the rule pointer
    m_ruleT->rotation.y += 1.0F * omi::fpsManager.getTimeScale();

    if ( m_ruleT->rotation.y >= 360.0F )
    {
        m_ruleT->rotation.y -= 360.0F;
    }

    m_ruleT->translation.y =
            util::math::sind( m_ruleT->rotation.y * 4.0F ) * 0.25F;

    switch( m_rule )
    {
        case unit::RULE_NONE:
        {
            m_noRuleMesh->visible = true;
            m_downRuleMesh->visible = false;
            m_upRuleMesh->visible = false;
            break;
        }
        case unit::RULE_DOWN:
        {
            m_noRuleMesh->visible = false;
            m_downRuleMesh->visible = true;
            m_upRuleMesh->visible = false;
            break;
        }
        case unit::RULE_UP:
        {
            m_noRuleMesh->visible = false;
            m_downRuleMesh->visible = false;
            m_upRuleMesh->visible = true;
            break;
        }
    }

    float x = m_transform->translation.x;
    float y = m_transform->translation.y;
    float z = m_transform->translation.z;

    // check if this is in a block
    GroundBlock* currentBlock = m_environment->getBlock( x, y + 0.5F, z );
    if ( currentBlock )
    {
        m_transform->translation.y += 1.0F;

        int base = 10;
        if ( m_rule == unit::RULE_DOWN )
        {
            base = 16;
        }

        hp -= base + rand() % 5;

        return;
    }

    // check if there is a block below
    currentBlock = m_environment->getBlock( x, y - 0.5F, z );
    if ( currentBlock == NULL )
    {
        m_transform->translation.y -= 1.0F;

        int base = 10;
        if ( m_rule == unit::RULE_UP )
        {
            base = 16;
        }
        hp -= base + rand() % 5;

        return;
    }
}

void Artillery::hardRemove()
{
    addEntity( new UnitDead( m_transform->translation ) );


    float x = m_transform->translation.x;
    float y = m_transform->translation.y;
    float z = m_transform->translation.z;

    m_environment->removeBlock( x, y, z, true );

    m_environment->removeBlock( x + 3, y, z, true );
    m_environment->removeBlock( x - 3, y, z, true );
    m_environment->removeBlock( x,     y, z + 3, true );
    m_environment->removeBlock( x,     y, z - 3, true );

    m_environment->removeBlock( x, y - 3, z, true );

    // play sound
    omi::SoundPool::play(
            omi::ResourceManager::getSound( "unit_dead" ),
            false,
            1.0F
    );

    remove();
}

void Artillery::setRule( unit::Rule rule )
{
    m_rule = rule;
}

void Artillery::setAngle( float angle )
{
    m_transform->rotation.y = angle;
}

const glm::vec3& Artillery::getPos()
{
    return m_transform->translation;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Artillery::fireWeapon()
{
    if ( !m_readyToFire )
    {
        m_reloadTimer += 0.005F * omi::fpsManager.getTimeScale();
        if ( m_reloadTimer >= 1.0F )
        {
            m_readyToFire = true;
        }

        return;
    }

    m_readyToFire = false;
    m_reloadTimer = 0.0F;

    bool invert = false;
    if ( m_team == unit::ENEMY )
    {
        invert = true;
    }

    if ( m_rule == unit::RULE_NONE )
    {
        return;
    }

    unsigned pT = 0;
    if ( m_rule == unit::RULE_UP )
    {
        pT = 1;
    }

    float aO = ( static_cast< float >( rand() % 1000 ) / 1000.0F ) - 0.5F;
    aO *= 4.5F;

    // create the projectile
    addEntity( new Projectile(
            m_transform->translation,
            m_transform->rotation.y + aO,
            invert,
            pT,
            m_environment
    ) );

    // play sound
    std::string fireSound( "unit_fire_1" );
    unsigned r = rand() % 3;
    if ( r == 1 )
    {
        fireSound = "unit_fire_2";
    }
    else if ( r == 2 )
    {
        fireSound = "unit_fire_3";
    }

    omi::SoundPool::play(
            omi::ResourceManager::getSound( fireSound ),
            false,
            0.5F
    );
}
