#pragma once

#include "AnimatedEntity.hpp"

class Enemy : public AnimatedEntity {
	void OnPlayerCollision() override;
public:
	Enemy();
};