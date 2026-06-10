#ifndef ENTITY_H
#define ENTITY_H

#include "external/glm/glm.hpp"

class Entity {
public:
    Entity(const glm::ivec2& position, bool active):
        tilePosition(position), active(active)
    {};

    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;

    glm::ivec2 getTilePosition() { return tilePosition; }
    void setTilePosition(const glm::ivec2& newTilePosition) { tilePosition = newTilePosition; }

    bool isActive() { return active; }
    void setActive(bool state) { active = state; }

protected:
    glm::ivec2 tilePosition;
    bool active;

};

#endif