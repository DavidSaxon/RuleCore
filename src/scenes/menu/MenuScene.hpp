#ifndef OMICRON_SCENES_MENUSCENE_H_
#   define OMICRON_SCENES_MENUSCENE_H_

#include "src/omicron/scene/Scene.hpp"

class MenuScene : public omi::Scene {
public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual void init();

    /** #Override */
    virtual bool update();

    /** #Override */
    virtual omi::Scene* nextScene();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    bool m_exit;
    bool m_flat;
};

#endif
