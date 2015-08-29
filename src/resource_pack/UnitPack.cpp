#include "Packs.hpp"

namespace pack {

void buildUnitPack()
{
    // artillery
    omi::ResourceManager::addMaterialGeometryMesh(
            "artillery_body",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.2F, 0.2F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/artillery.obj",
            0
    );

    // trail
    omi::ResourceManager::addMaterialGeometryMesh(
            "entry_trail",
            resource_group::GAMEPLAY,
            "default_shader",
            glm::vec4( 0.2F, 0.2F, 1.0F, 1.0F ),
            "res/gfx/geometry/gameplay/unit/entry_trail.obj",
            0,
            omi::material::SHADELESS
    );
}

} // namespace pack
