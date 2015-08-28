#ifndef OMICRON_ENTITIES_TEST_TESTENVIRONMENT_H_
#    define OMICRON_ENTITIES_TEST_TESTENVIRONMENT_H_

#include "src/omicron/entity/Entity.hpp"

class TestEnvironment : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();
};

#endif
