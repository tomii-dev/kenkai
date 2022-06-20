#include "Events.hpp"
#include "Assets.hpp"
#include "Game.hpp"

#include <iostream>

class Setup {
public:
	Setup() {
		Assets::initAssets();
		Events::RegisterEvents();
		// hook events
		Events::HookTo(StartPressed, [](){
			Game::getInstance().setState(PLAYING);
		});
	}
};