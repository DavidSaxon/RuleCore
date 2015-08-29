#ifndef RULECORE_ENTITIES_GAMEPLAY_UNIT_ARTILLERY_HPP_
#   define RULECORE_ENTITIES_GAMEPLAY_UNIT_ARTILLERY_HPP_

#include "src/omicron/entity/Entity.hpp"

namespace unit
{

enum State
{
    STATE_FALLING = 0,
    STATE_INPLACE
};

} // namespace unit

//------------------------------------------------------------------------------
//                             FORWARD DECELERATIONS
//------------------------------------------------------------------------------

class Environment;

class Artillery : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Artillery( Environment* environment );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    Environment* m_environment;

    // the current state of the unit
    unit::State m_state;

    // the transform of the unit
    omi::Transform* m_transform;

    // the mesh of the trail
    omi::Mesh* m_trail;
};


#endif
