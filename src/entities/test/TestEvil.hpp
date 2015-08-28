#ifndef OMICRON_ENTITIES_TEST_EVIL_HPP_
#   define OMICRON_ENTITIES_TEST_EVIL_HPP_

#include "src/omicron/entity/Entity.hpp"

class TestEvil : public omi::Entity {
public:

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

    omi::Transform* m_transform;
    omi::KeyFrameMesh* m_mesh;
    omi::Mesh* m_visMesh;

    float m_transTimer;
    bool m_trans;
    bool m_walk;
};

#endif
