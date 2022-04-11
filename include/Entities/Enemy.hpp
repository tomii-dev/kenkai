#pragma once

#include "AnimatedEntity.hpp"

class Enemy : public AnimatedEntity {
	bool done;
	void OnPlayerCollision() override;
	void UniqueUpdate() override;
	void JumpLoop();
public:
	Enemy();
};