#pragma once

#include "AnimatedEntity.hpp"

class Enemy : public AnimatedEntity {
	void OnPlayerCollision() override;
	void UniqueUpdate() override;
public:
	Enemy();
};