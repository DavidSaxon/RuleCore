#ifndef OMICRON_ENTITIES_TEST_TESTSUN_HPP_
#   define OMICRON_ENTITIES_TEST_TESTSUN_HPP_

#include "src/omicron/entity/Entity.hpp"

class TestSun : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    TestSun();

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
    omi::Transform* m_lightT;
    float m_move;
};

#endif
