#include "utils/inc/Menus.h"

#include <memory>


int main ()
{
    const std::shared_ptr<bool> run_game = std::make_shared<bool>(true);
    while (*run_game)
    {
        Menus::mainMenu(run_game);
    }
    return 0;
}
