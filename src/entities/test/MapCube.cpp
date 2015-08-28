#include "MapCube.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void MapCube::init()
{
    // transformation
    omi::Transform* transform = new omi::Transform(
            "",
            glm::vec3( 0.0f, -1.34f, 5.0f ),
            glm::vec3(),
            glm::vec3( 1.3f, 1.3f, 1.3f )
        );
    m_components.add( transform );

    omi::Mesh* mesh =
        omi::ResourceManager::getMesh( "map_test", "", transform );
    mesh->getMaterial().specular =
        new omi::Specular(
            64.0f,
            glm::vec3( 1.0f, 1.0f, 1.0f ),
            omi::ResourceManager::getTexture( "test_specular_map" )
        );
    m_components.add( mesh );
}

void MapCube::update()
{

}
