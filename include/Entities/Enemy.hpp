#pragma once

#include "AnimatedEntity.hpp"

class Enemy : public AnimatedEntity {
	void OnPlayerCollision() override;
	void UniqueUpdate() override;
	void Die() override;
	void OnPlayerAttacked();
	void AnimUpdate() override;
public:
	Enemy();
};