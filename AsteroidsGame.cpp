//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <ctime>
#include <iostream>
#include <glm/gtc/constants.hpp>
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Asteroids.hpp"
#include "Laser.hpp"

// Unfortunately the game is not complete by hand-in time.
// It is still in development. To see the fully updated version please check it out on Github:
// https://github.com/ralfpatric/asteroidsGame


using namespace sre;

AsteroidsGame::AsteroidsGame() {
    r.setWindowTitle("Asteroids");

    r.init()
     .withSdlWindowFlags(SDL_WINDOW_OPENGL);

    time_t t;                                               // random seed based on time
    srand((unsigned) time(&t));

    atlas = SpriteAtlas::create("asteroids.json","asteroids.png");

    auto spaceshipSprite = atlas->get("playerShip1_blue.png");
	auto asteroidSprite = atlas->get("Meteors/meteorBrown_big4.png");

    gameObjects.push_back(std::make_shared<SpaceShip>(spaceshipSprite));

	// remember to destroy your shared pointer ( EX 4-5 )

	gameObjects.push_back(std::make_shared<Asteroids>(asteroidSprite));
	gameObjects.push_back(std::make_shared<Asteroids>(asteroidSprite));
	gameObjects.push_back(std::make_shared<Asteroids>(asteroidSprite));
	gameObjects.push_back(std::make_shared<Asteroids>(asteroidSprite));

    camera.setWindowCoordinates();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };

    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}

void AsteroidsGame::update(float deltaTime) {
	for (int i = 0; i < gameObjects.size();i++) {
		gameObjects[i]->update(deltaTime);
    }
}

void drawCircle(std::vector<glm::vec3>& lines, glm::vec2 position, float radius){
    float quaterPi = glm::quarter_pi<float>();
    for (float f = 0;f<glm::two_pi<float>();f += quaterPi){
        // line from
        lines.push_back(glm::vec3{position.x + cosf(f)*radius,
                                  position.y + sinf(f)*radius,
                                  0
        });
        // line to
        lines.push_back(glm::vec3{position.x + cosf(f+quaterPi)*radius,
                                  position.y + sinf(f+quaterPi)*radius,
                                  0
        });
    }
}

void AsteroidsGame::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {.20, .60, .86, 1})
            .build();
    auto spriteBatchBuilder = SpriteBatch::create();

    for (int i = 0; i < gameObjects.size();i++) {
        gameObjects[i]->render(spriteBatchBuilder);
    }
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);

    if (debugCollisionCircles){
        std::vector<glm::vec3> lines;
        for (auto & go : gameObjects){
            auto col = std::dynamic_pointer_cast<Collidable>(go);
            if (col != nullptr){
                drawCircle(lines, go->position, col->getRadius());
            }
        }
        renderPass.drawLines(lines);
    }

    ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x/2-100, .0f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 70), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::LabelText("GOs", "%i", (int)gameObjects.size());
    ImGui::LabelText("Score", "%i",score);
    ImGui::End();
}

void AsteroidsGame::keyEvent(SDL_Event &event) {
    for (int i = 0; i < gameObjects.size();i++) {
        gameObjects[i]->onKey(event);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
        debugCollisionCircles = !debugCollisionCircles;
    }

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
		auto laserSprite = atlas->get("Lasers/laserBlue01.png");
		gameObjects.push_back(std::make_shared<Laser>(laserSprite, glm::vec2 (gameObjects[0]->position.x, gameObjects[0]->position.y), float (gameObjects[0]->rotation)));

	}
}

int main(){
    new AsteroidsGame();
    return 0;
}