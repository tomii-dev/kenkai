#include "Events.hpp"
#include "Assets.hpp"
#include "Game.hpp"

#include <iostream>
#include <functional>

class Setup {
public:
	Setup() {
		Assets::initAssets();
		Events::RegisterEvents();
		Events::HookTo(EventId::StartPressed, [](){ Game::getInstance().setState(PLAYING); });
	}
};