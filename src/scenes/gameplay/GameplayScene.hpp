#ifndef RULECORE_SCENES_GAMEPLAYSCENE_HPP_
#   define RULECORE_SCENES_GAMEPLAYSCENE_HPP_

#include "src/omicron/scene/Scene.hpp"

class GameplayScene : public omi::Scene
{
public:

    GameplayScene( bool flat );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual void init();

    /** #Override */
    virtual bool update();

    /** #Override */
    virtual omi::Scene* nextScene();

    bool m_flat;
};

#endif
