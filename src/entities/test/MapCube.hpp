#ifndef OMICRON_ENTITIES_TEST_MAPCUBE_HPP_
#   define OMICRON_ENTITIES_TEST_MAPCUBE_HPP_

#include "src/omicron/entity/Entity.hpp"

class MapCube : public omi::Entity {
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
