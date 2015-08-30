#ifndef RULECORE_ENTITIES_START_UP_MAINMENU_HPP_
#   define RULECORE_ENTITIES_START_UP_MAINMENU_HPP_

#include "src/omicron/entity/Entity.hpp"

class MainMenu : public omi::Entity
{
public:

    ~MainMenu();

    /** #Override */
    void init();

    /** #Override */
    void update();

    // music
    omi::Music* m_menuMusic;
};

#endif
