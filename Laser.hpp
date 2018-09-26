#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"

class Laser : public GameObject, public Collidable {
public:
	Laser(const sre::Sprite &sprite, glm::vec2 pos, float rot);

	void update(float deltaTime) override;

	bool LaserLifespan();

	int lifespan = 0;

	bool isAlive;

	void onCollision(std::shared_ptr<GameObject> other) override;
	
	glm::vec2 velocity;
private:
	float drag = 0.80f;
	float maxSpeed = 200.0f;
	float thrustPower = 600.0f;
	float rotationSpeed = 100.0f;
	glm::vec2 winSize;
};


#pragma once
