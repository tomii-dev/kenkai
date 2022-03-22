#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Properties.hpp"

namespace Tools {

	struct AnimationInfo {
		sf::Texture idleAnim[4];
		sf::Texture leftAnim[4];
		sf::Texture rightAnim[4];
	};

	static AnimationInfo GetAnimsById(std::string id) {
		AnimationInfo anims;

		for (int i = 0; i < 4; i++) {
			sf::Texture texture;
			texture.loadFromFile("assets/animations/" + id + "/idle/" + std::to_string(i + 1) + ".png");
			anims.idleAnim[i] = texture;
			//texture.loadFromFile("assets/animations/" + id + "/left/" + std::to_string(i + 1) + ".png");
			//anims.leftAnim[i] = texture;
			//texture.loadFromFile("assets/animations/" + id + "/right/" + std::to_string(i + 1) + ".png");
			//anims.rightAnim[i] = texture;
		}

		return anims;
	}
}