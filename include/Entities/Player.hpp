#pragma once

#include "AnimatedEntity.hpp"

class Player : public AnimatedEntity {
	std::string username;
	void Die() override;
	void UniqueUpdate() override;
public:
	Player(Tools::PlayerConfig config);
	void Jump();
}; 