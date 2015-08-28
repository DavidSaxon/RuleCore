#ifndef OMICRON_ENTITIES_TEST_GLOWCUBE_H_
#    define OMICRON_ENTITIES_TEST_GLOWCUBE_H_

#include "src/omicron/entity/Entity.hpp"

class GlowCube : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    GlowCube();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the position of the cube
    omi::Transform* m_transform;
    // the collision detector of the cube
    omi::CollisionDetector* m_collisionDetect;
    // the mesh of the cube
    omi::Mesh* m_mesh;
    // the light source of the cube
    omi::PointLight* m_light;

    // the colour of the cube
    glm::vec4 m_colour;
    // counter for changing
    float m_colourChange;
    // counter for flickering
    float m_flickerCounter;
};

#endif
