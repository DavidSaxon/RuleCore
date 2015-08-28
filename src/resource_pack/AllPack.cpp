#include "Packs.hpp"

namespace pack {

void buildAllPack()
{
    //---------------------------------SHADERS----------------------------------

    // default shader
    omi::ResourceManager::addShader(
        "default_shader",
        resource_group::ALL,
        "res/gfx/shader/omicron/default_vertex.glsl",
        "res/gfx/shader/omicron/default_fragment.glsl"
    );

    //-----------------------------------FONT-----------------------------------

    // default font
    omi::ResourceManager::addFont(
        "default_font",
        resource_group::ALL,
        "res/gfx/fonts/clear_sans.ttf"
    );
}

} // namespace pack
