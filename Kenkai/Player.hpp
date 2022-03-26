#pragma once

#include "AnimatedEntity.hpp"

class Player : public AnimatedEntity {
	std::string username;
public:
	Player(Tools::PlayerConfig config);
};