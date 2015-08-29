#include "Packs.hpp"

namespace pack {

void buildTerrainPack()
{
    // sun
    omi::ResourceManager::addMaterialGeometryMesh(
            "sun",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 1.0, 1.0f, 0.8f, 1.0f ),
            "res/gfx/geometry/gameplay/terrain/sun.obj",
            0,
            omi::material::SHADELESS
    );

    // grass block texture and material
    omi::ResourceManager::addTexture(
            "block_grass_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/grass_1.png"
    );
    omi::ResourceManager::addMaterial(
            "block_grass_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_grass_1"
    );

    // dirt block texture and material
    omi::ResourceManager::addTexture(
            "block_dirt_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/dirt_1.png"
    );
    omi::ResourceManager::addMaterial(
            "block_dirt_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_dirt_1"
    );

    // mountain grass block texture and material
    omi::ResourceManager::addTexture(
            "block_mountain_grass_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/mountain_grass.png"
    );
    omi::ResourceManager::addMaterial(
            "block_mountain_grass_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_mountain_grass_1"
    );

    // dirty snow block texture and material
    omi::ResourceManager::addTexture(
            "block_dirty_snow_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/dirty_snow.png"
    );
    omi::ResourceManager::addMaterial(
            "block_dirty_snow_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_dirty_snow_1"
    );

    // snow block texture and material
    omi::ResourceManager::addTexture(
            "block_snow_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/snow.png"
    );
    omi::ResourceManager::addMaterial(
            "block_snow_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_snow_1"
    );

    // gravel block texture and material
    omi::ResourceManager::addTexture(
            "block_gravel_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/gravel.png"
    );
    omi::ResourceManager::addMaterial(
            "block_gravel_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_gravel_1"
    );

    // stone block texture and material
    omi::ResourceManager::addTexture(
            "block_stone_1",
            resource_group::GAMEPLAY,
            "res/gfx/texture/gameplay/terrain/stone_1.png"
    );
    omi::ResourceManager::addMaterial(
            "block_stone_1",
            resource_group::GAMEPLAY,
            "default_shader",
            "block_stone_1"
    );
};

} // namespace pack
