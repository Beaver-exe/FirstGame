#include "entities/Player.h"
#include "external/glm/glm.hpp"

#include <string>

Player::Player(const glm::ivec2& position, bool active)
    : Entity(position, active),
    startTile(position),
    targetTile(position),
    worldPosition(glm::vec2(position)),
    isMoving(false),
    moveTime(0.0f),
    moveDuration(0.15f),
    direction(DOWN)
{
}

void Player::setInputState(const InputState& input) {
    currentInput = input;
}

glm::vec2 Player::getWorldPosition() const {
    return worldPosition;
}

void Player::update(float deltaTime) {
    if (isMoving) {
        updateMovement(deltaTime);
    } else {
        handleInput();
    }
}

void Player::handleInput() {

    if (currentInput.up) {
        direction = UP;
        startMovement(currentInput.sprint);
    } else if (currentInput.down) {
        direction = DOWN;
        startMovement(currentInput.sprint);
    } else if (currentInput.left) {
        direction = LEFT;
        startMovement(currentInput.sprint);
    } else if (currentInput.right) {
        direction = RIGHT;
        startMovement(currentInput.sprint);
    } else {

    }

}

void Player::startMovement(bool sprint) {
    glm::ivec2 offset(0);

    switch (direction) {
        case UP:    offset.y -= 1; break;
        case DOWN:  offset.y += 1; break;
        case LEFT:  offset.x -= 1; break;
        case RIGHT: offset.x += 1; break;
    }

    startTile = tilePosition;
    targetTile = tilePosition + offset;

    isMoving = true;
    moveTime = 0.0f;

    moveDuration = sprint ? 0.15f : 0.65f;

}

void Player::updateMovement(float deltaTime) {

    moveTime += deltaTime;
    float time = moveTime / moveDuration;

    if (time >= 1.0f) {
        tilePosition = targetTile;
        worldPosition = glm::vec2(tilePosition);
        isMoving = false;
        moveTime = 0.0f;
        return;
    }

    glm::vec2 start = glm::vec2(startTile);
    glm::vec2 end = glm::vec2(targetTile);
    
    worldPosition = glm::mix(start, end, time);
}

