#ifndef OMICRON_ENTITIES_TEST_TESTFPS_HPP_
#   define OMICRON_ENTITIES_TEST_TESTFPS_HPP_

#include <sstream>

#include "src/omicron/entity/Entity.hpp"

class TestFps : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

private:

    omi::Text* m_text;

    float m_counter;
};

#endif
