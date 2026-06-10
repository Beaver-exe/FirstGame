#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "external/glm/glm.hpp"
#include "core/InputHandler.h"

#include <string>

enum PlayerDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public Entity {
public:
    Player(const glm::ivec2& startTile, bool active);
    void update(float deltaTime) override;
    void setInputState(const InputState& input);
    glm::vec2 getWorldPosition() const;

private:
    void handleInput();
    void startMovement(bool sprint);
    void updateMovement(float deltaTime);

    glm::vec2 worldPosition;
    glm::ivec2 startTile;
    glm::ivec2 targetTile;

    bool isMoving;
    float moveTime;
    float moveDuration;

    PlayerDirection direction;
    InputState currentInput;

    std::string spriteSheet = "playerSprites.png";

};

#endif
