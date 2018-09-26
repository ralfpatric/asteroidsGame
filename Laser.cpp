
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "Laser.hpp"
#include "SpaceShip.hpp"
#include "sre/Renderer.hpp"
#include <iostream>

Laser::Laser(const sre::Sprite &sprite, glm::vec2 pos, float rot) : GameObject(sprite) {
	scale = glm::vec2(0.5f, 0.5f);
	winSize = sre::Renderer::instance->getWindowSize();
	radius = 23;
	position = pos;
	rotation = rot;
	velocity = glm::rotateZ(glm::vec3(0, 1, 0), glm::radians(rotation));
}

void Laser::update(float deltaTime) {

	position += velocity * deltaTime;
	bool isAlive = LaserLifespan();


	float acceleration = deltaTime * thrustPower;
	glm::vec2 direction = glm::rotateZ(glm::vec3(0, acceleration, 0), glm::radians(rotation));
	velocity += direction;
	float speed = glm::length(velocity);
	if (speed > maxSpeed) {
		velocity = velocity * (maxSpeed / speed);
	}


	// wrap around
	if (position.x < 0) {
		position.x += winSize.x;
	}
	else if (position.x > winSize.x) {
		position.x -= winSize.x;
	}
	if (position.y < 0) {
		position.y += winSize.y;
	}
	else if (position.y > winSize.y) {
		position.y -= winSize.y;
	}
}

bool Laser::LaserLifespan() {

	lifespan++;
	while (lifespan < 60) {
		return false;
	}
	return true;
}

void Laser::onCollision(std::shared_ptr<GameObject> other) {
	// Add asteroids splits here on collision
}

