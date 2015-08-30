#include "Packs.hpp"

namespace pack {

void buildUnitPack()
{
    // selection box
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_selection_box",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/selection_box.obj",
            0
    );

    // selection box
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_outline",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/outline.obj",
            0
    );

    // no rule
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_no_rule",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/no_rule.obj",
            0
    );
    // down rule
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_down_rule",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/down_rule.obj",
            0
    );
    // up rule
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_up_rule",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/up_rule.obj",
            0
    );

    // artillery
    omi::ResourceManager::addMaterialGeometryMesh(
            "artillery_body",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.25F, 0.25F, 0.25F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/artillery_body.obj",
            0
    );
    omi::ResourceManager::addMaterialGeometryMesh(
            "artillery_support",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.7F, 0.7F, 0.7F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/artillery_support.obj",
            0
    );
    omi::ResourceManager::addMaterialGeometryMesh(
            "artillery_mount",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.2F, 0.2F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/artillery_mount.obj",
            0
    );
    omi::ResourceManager::addMaterialGeometryMesh(
            "artillery_barrel",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.5F, 0.5F, 0.5F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/artillery_barrel.obj",
            0
    );

    // trail
    omi::ResourceManager::addMaterialGeometryMesh(
            "entry_trail",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/entry_trail.obj",
            1,
            omi::material::SHADELESS
    );

    // land hit
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_land_hit",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 1.0F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/land_hit.obj",
            1,
            omi::material::SHADELESS
    );

    // projectile
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_projectile",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 0.5F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/projectile.obj",
            1,
            omi::material::SHADELESS
    );

    // down explosion
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_down_explosion",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 0.5F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/down_explosion.obj",
            1,
            omi::material::SHADELESS
    );

    // up explosion
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_up_explosion",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.8F, 1.0F, 0.2F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/up_explosion.obj",
            1,
            omi::material::SHADELESS
    );

    // unit dea
    omi::ResourceManager::addMaterialGeometryMesh(
            "unit_dead",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0F, 0.5F, 0.1F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/unit_dead.obj",
            1,
            omi::material::SHADELESS
    );

    // text motherfucker
    omi::ResourceManager::addMaterialText(
        "UI_text",
        resource_group::GAMEPLAY,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        10,
        "default_font",
        "0",
        0.1f,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addMaterialText(
        "MENU_TITLE_TEXT",
        resource_group::GAMEPLAY,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        10,
        "default_font",
        "0",
        0.2f,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addMaterialText(
        "MAIN_MENU_TEXT",
        resource_group::GAMEPLAY,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        10,
        "default_font",
        "0",
        0.15f,
        omi::material::SHADELESS
    );

    //----------------------------------SOUNDS----------------------------------

    omi::ResourceManager::addSound(
        "unit_entry",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/unit_entry.ogg",
        2
    );

    omi::ResourceManager::addSound(
        "land_hit_1",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/land_hit_1.ogg",
        3
    );
    omi::ResourceManager::addSound(
        "land_hit_2",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/land_hit_2.ogg",
        3
    );

    omi::ResourceManager::addSound(
        "unit_fire_1",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/unit_fire_1.ogg",
        3
    );
    omi::ResourceManager::addSound(
        "unit_fire_2",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/unit_fire_2.ogg",
        3
    );
    omi::ResourceManager::addSound(
        "unit_fire_3",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/unit_fire_3.ogg",
        3
    );

    omi::ResourceManager::addSound(
        "proj_down_1",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/proj_down_1.ogg",
        3
    );
    omi::ResourceManager::addSound(
        "proj_down_2",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/proj_down_2.ogg",
        3
    );

    omi::ResourceManager::addSound(
        "proj_up_1",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/proj_up_1.ogg",
        3
    );
    omi::ResourceManager::addSound(
        "proj_up_2",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/proj_up_2.ogg",
        3
    );

    omi::ResourceManager::addSound(
        "unit_dead",
        resource_group::GAMEPLAY,
        "res/sound/fx/gameplay/unit_dead.ogg",
        2
    );
}

} // namespace pack
