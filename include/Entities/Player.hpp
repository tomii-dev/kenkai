#pragma once

#include "Entity.hpp"
#include "AnimatedEntity.hpp"
#include "Weapon.hpp"

class Player : public AnimatedEntity {
	std::string username;
	Weapon currentWeapon;
	bool sprinting;
	void Die() override;
	void UniqueUpdate() override;
	void AnimUpdate() override;
	void Attack();
	void Setup() override;
public:
	Player(Tools::PlayerConfig config);
	void Jump();
	Weapon getCurrentWeapon();
}; 