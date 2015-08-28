#include "TestEnvironment.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestEnvironment::init()
{
    // directional lights
    // omi::Transform* t_1 = new omi::Transform(
    //         "",
    //         glm::vec3( -1.0f, 0.5f, 0.0f ),
    //         glm::vec3(),
    //         glm::vec3( 1.0f, 1.0f, 1.0f )
    //     );
    // m_components.add( t_1 );
    // m_components.add( new omi::DirectionalLight(
    //     "", t_1, 0.8f, glm::vec3( 0.3f, 0.3f, 1.0f )
    // ) );
    // point lights
    omi::Transform* t_2 = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.33f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( t_2 );
    // omi::PointLight* l1 = new omi::PointLight(
    //      "", t_2, 1.0f, glm::vec3( 0.75f, 0.5f, 0.9f ), 0.05f, 0.3f, 0.0001f );
    omi::PointLight* l1 = new omi::PointLight(
            "purple_point",
            t_2,
            1.0f,
            glm::vec3( 1.0f, 1.0f, 1.0f ),
            0.05f,
            0.3f,
            0.0001f
    );
    // l1->setInverse( true );
    m_components.add( l1 );
    // spot lights
    // omi::Transform* t_3 = new omi::Transform(
    //         "",
    //         glm::vec3( -4.0f, 1.5f, 0.0f ),
    //         glm::vec3( -90.0f, 0.0f, 0.0f ),
    //         glm::vec3( 1.0f, 1.0f, 1.0f )
    //     );
    // m_components.add( t_3 );
    // m_components.add( new omi::SpotLight(
    //     "", t_3, 1.0f, glm::vec3( 1.0f, 1.0f, 1.0f ),
    //     0.0f, 0.1f, 0.025f, 45.0f, 35.0f
    // ) );

    // meshes
    // m_components.add(
    //         omi::ResourceManager::getMesh( "test_tunnel_1", "", NULL ) );

    // std::cout << "load attempt begin" << std::endl;

    // omi::Mesh* pipeMesh =
    //         omi::ResourceManager::getMesh( "test_tunnel_pipe_1", "", NULL );
    // pipeMesh->getMaterial().specular =
    //     new omi::Specular( 64.0f, glm::vec3( 0.5f, 0.5f, 0.5f ) );
    // m_components.add( pipeMesh );

    // std::cout << "load attempt end" << std::endl;

    // omi::Mesh* pipeHolderMesh =
    //         omi::ResourceManager::getMesh(
    //             "test_tunnel_pipe_holder_1", "", NULL );
    // pipeHolderMesh->getMaterial().specular =
    //     new omi::Specular( 12.0f, glm::vec3( 0.3f, 0.3f, 0.3f ) );
    // m_components.add( pipeHolderMesh );

    // omi::Mesh* lightBulbMesh =
    //         omi::ResourceManager::getMesh(
    //             "test_tunnel_light_bulb_1", "", NULL );
    // lightBulbMesh->getMaterial().glow =
    //     new omi::Glow( glm::vec3( 0.5f, 0.25f, 1.0f ), 1.0f );
    // m_components.add( lightBulbMesh );

    // omi::Mesh* lightSocketMesh =
    //         omi::ResourceManager::getMesh(
    //             "test_tunnel_light_socket_1", "", NULL );
    // lightSocketMesh->getMaterial().specular =
    //     new omi::Specular( 64.0f, glm::vec3( 1.0f, 1.0f, 1.0f ) );
    // m_components.add( lightSocketMesh );

    omi::Mesh* floorMesh =
            omi::ResourceManager::getMesh(
                "test_floor_1", "", NULL );
    floorMesh->getMaterial().specular =
        new omi::Specular(
            128.0f,
            glm::vec3( 1.0f, 1.0f, 1.0f ),
            omi::ResourceManager::getTexture( "floor_1_spec_map" )
    );
    m_components.add( floorMesh );

    // omi::Sprite* guiTest =
    //         omi::ResourceManager::getSprite( "test_gui", "", NULL );
    // guiTest->gui = true;
    // m_components.add( guiTest );

    // omi::Text* textTest =
    //         omi::ResourceManager::getText( "test_text_1", "", NULL );
    // textTest->gui = true;
    // textTest->setHorCentred( true );
    // textTest->setVertCentred( true );
    // m_components.add( textTest );

    // m_components.add(
    //         omi::ResourceManager::getMesh( "lounge_floor", "", NULL ) );
    // m_components.add(
    //         omi::ResourceManager::getMesh( "lounge_wall", "", NULL ) );
}

void TestEnvironment::update()
{
}
