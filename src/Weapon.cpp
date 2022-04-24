#include "Weapon.hpp"

Weapon::Weapon() {

}

void Weapon::setDamage(int damage) { this->damage = damage; }
int Weapon::getDamage() { return damage; }