#include "Packs.hpp"

namespace pack {

void buildTestPack()
{
    omi::ResourceManager::addFont(
        "test_font_1", resource_group::TEST,
        "res/gfx/fonts/test/ClearSans-Regular.ttf"
    );

    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_skybox", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/skybox.png",
        "res/gfx/geometry/test/skybox.obj",
        0, 0,
        omi::material::SHADELESS
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_floor_1", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/floor_1.png",
        "res/gfx/geometry/test/floor_1.obj",
        1
    );
    omi::ResourceManager::addTexture(
        "floor_1_spec_map", resource_group::TEST,
        "res/gfx/texture/test/floor_1_spec_map.png"
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_tunnel_1", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/wall_1.png",
        "res/gfx/geometry/test/tunnel_1.obj",
        1
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_tunnel_pipe_1", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/pipe_1.png",
        "res/gfx/geometry/test/tunnel_pipe_1.obj",
        1
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_tunnel_pipe_holder_1", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/pipe_holder_1.png",
        "res/gfx/geometry/test/tunnel_pipe_holder_1.obj",
        1
    );
    omi::ResourceManager::addMaterialGeometryMesh(
        "test_tunnel_light_bulb_1", resource_group::TEST,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        "res/gfx/geometry/test/light_bulb_1.obj",
        1,
        omi::material::SHADELESS
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_tunnel_light_socket_1", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/light_socket_1.png",
        "res/gfx/geometry/test/light_socket_1.obj",
        1
    );
    omi::ResourceManager::addMaterialGeometryMesh(
        "test_monkey", resource_group::TEST,
        "default_shader",
        glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ),
        "res/gfx/geometry/test/monkey.obj",
        2
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_human", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/human.png",
        "res/gfx/geometry/test/human.obj",
        2
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "glow_cube", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/glow_cube.png",
        "res/gfx/geometry/test/glow_cube.obj",
        2, 0,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "lounge_floor", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/carpet_lounge.png",
        "res/gfx/geometry/test/lounge_floor.obj",
        1
    );
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "lounge_wall", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/wall_lounge.png",
        "res/gfx/geometry/test/lounge_wall.obj",
        1
    );

    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "map_test", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/chesterfield.png",
        "res/gfx/geometry/test/glow_cube.obj",
        1
    );
    omi::ResourceManager::addTexture(
        "test_specular_map", resource_group::TEST,
        "res/gfx/texture/test/chesterfield_specular_map.png"
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "test_sun_geo", resource_group::TEST,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        "res/gfx/geometry/test/monkey.obj",
        2, omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialSprite(
        "test_gui", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/chesterfield.png",
        1,
        glm::vec2( 0.5f, 0.5f ),
        glm::vec2( 1.0f, 1.0f ),
        glm::vec2( 0.0f, 0.0f ),
        0, omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "test_evil", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/evil.png",
        "res/gfx/geometry/test/evil.obj",
        1
    );
    omi::ResourceManager::addTexture(
        "test_evil_glow", resource_group::TEST,
        "res/gfx/texture/test/evil_glow.png"
    );

    omi::ResourceManager::addMaterialText(
        "test_text_1", resource_group::TEST,
        "default_shader", // TODO: text shader
        glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ),
        2,
        "test_font_1",
        "Hello World",
        0.25f,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMatrialKeyFrameMesh(
        "test_evil_key", resource_group::TEST,
        "default_shader",
        "res/gfx/texture/test/evil.png",
        1,
        "res/gfx/geometry/test/evil/evil.key"
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "test_evil_vis", resource_group::TEST,
        "default_shader",
        glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ),
        "res/gfx/geometry/test/evil_vis.obj",
        1
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "test_monkey", resource_group::TEST,
        "default_shader",
        glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ),
        "res/gfx/geometry/test/monkey.obj",
        2
    );

    omi::ResourceManager::addSound(
        "explosion_1", resource_group::TEST,
        "res/sound/fx/test/expolsion_1.ogg", 1
    );
}

} // namespace pack
