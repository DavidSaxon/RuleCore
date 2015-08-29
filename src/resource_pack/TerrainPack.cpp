#include "Packs.hpp"

namespace pack {

void buildTerrainPack()
{
    // standard terrain cube
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "std_ground_cube",
        resource_group::GAMEPLAY,
        "default_shader",
        "res/gfx/texture/gameplay/terrain/grass_1.png",
        "res/gfx/geometry/gameplay/terrain/ground_block.obj",
        0
    );
};

} // namespace pack
