#include <iostream>
#include <tuple>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Define an enum for different game entity types
enum GameEntityType {
    ExplosionType,
    MineType,
    NoneType,
    ShipType
};

// Define the GameEntity base class
class GameEntity {
protected:
    std::tuple<int, int> position;  // Entity's position
    GameEntityType type;            // Entity's type

public:
    // Constructor, takes coordinates and entity type as arguments
    GameEntity(int x, int y, GameEntityType entityType) : position(x, y), type(entityType) {}

    // Returns the entity's position
    std::tuple<int, int> getPos() const {
        return position;
    }

    // Returns the entity's type
    GameEntityType getType() const {
        return type;
    }

    // Pure virtual function to be implemented in derived classes
    virtual void apply(GameEntity& entity) = 0;

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~GameEntity() = default;
};
