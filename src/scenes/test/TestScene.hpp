#ifndef OMICRON_SCENES_TESTSCENE_HPP_
#   define OMICRON_SCENES_TESTSCENE_HPP_

#include "src/omicron/input/Input.hpp"
#include "src/omicron/scene/Scene.hpp"

#include "src/entities/test/GlowCube.hpp"
#include "src/entities/test/Human.hpp"
#include "src/entities/test/MapCube.hpp"
#include "src/entities/test/Monkey.hpp"
#include "src/entities/test/TestEnvironment.hpp"
#include "src/entities/test/TestEvil.hpp"
#include "src/entities/test/TestFps.hpp"
#include "src/entities/test/TestPlayer.hpp"
#include "src/entities/test/TestSun.hpp"

/***************************************\
| Testing scene for the Omicron Engine. |
\***************************************/
class TestScene : public omi::Scene {
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
};

#endif
