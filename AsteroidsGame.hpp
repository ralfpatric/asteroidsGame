#pragma once

#include <vector>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

class GameObject;

class AsteroidsGame {
public:
    AsteroidsGame();
private:
    void update(float deltaTime);
    void render();
    void keyEvent(SDL_Event &event);

    sre::Camera camera;
    sre::SDLRenderer r;
    std::shared_ptr<sre::SpriteAtlas> atlas;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    bool debugCollisionCircles = false;
    int score = 0;
};


