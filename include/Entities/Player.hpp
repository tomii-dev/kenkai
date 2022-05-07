#pragma once

#include "AnimatedEntity.hpp"
#include "Weapon.hpp"
#include "UIElement.hpp"

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
	UIElement cursor;
	Player(Tools::PlayerConfig config);
	void Jump();
	Weapon getCurrentWeapon();
}; 