#include <iostream>
#include <tuple>

// Define the GameEntityType enum
enum GameEntityType {
    ExplosionType,
    MineType,
    NoneType,
    ShipType
};

// Base GameEntity class
class GameEntity {
protected:
    std::tuple<int, int> position;
    GameEntityType type;

public:
    GameEntity(int x, int y, GameEntityType entityType) : position(x, y), type(entityType) {}

    std::tuple<int, int> getPos() const {
        return position;
    }

    GameEntityType getType() const {
        return type;
    }

    virtual void apply(GameEntity& entity) = 0;  // Pure virtual function

    virtual ~GameEntity() = default;
};

// Explosion class, inherits from GameEntity
class Explosion : public GameEntity {
public:
    // Constructor
    Explosion(int x, int y) : GameEntity(x, y, ExplosionType) {}

    // Override the apply function
    void apply(GameEntity& entity) override {
        // Change the affected entity's position and type
        entity.position = std::make_tuple(-1, -1);
        entity.type = NoneType;
    }
};

// Ship class, inherits from GameEntity
class Ship : public GameEntity {
public:
    // Constructor
    Ship(int x, int y) : GameEntity(x, y, ShipType) {}

    // Move function to change the ship's position
    void move(int dx, int dy) {
        position = std::make_tuple(std::get<0>(position) + dx, std::get<1>(position) + dy);
    }

    // Print the ship's position
    void printPosition() const {
        std::cout << "Ship position: (" << std::get<0>(position) << ", " << std::get<1>(position) << ")" << std::endl;
    }
};

// Mine class, inherits from GameEntity
class Mine : public GameEntity {
public:
    // Constructor
    Mine(int x, int y) : GameEntity(x, y, MineType) {}

    // Explode function to return an Explosion and change the mine type
    Explosion explode() {
        // Change the type of the mine to NoneType after it explodes
        type = NoneType;
        return Explosion(std::get<0>(position), std::get<1>(position));
    }

    // Print the mine's status
    void printStatus() const {
        if (type == NoneType) {
            std::cout << "Mine has exploded and is now inactive." << std::endl;
        } else {
            std::cout << "Mine is active at position: (" << std::get<0>(position) << ", " << std::get<1>(position) << ")" << std::endl;
        }
    }
};

// Main function to test the classes
int main() {
    // Create a Ship at position (5, 5)
    Ship ship(5, 5);
    ship.printPosition();

    // Move the ship by (2, 3)
    ship.move(2, 3);
    ship.printPosition();

    // Create a Mine at position (7, 7)
    Mine mine(7, 7);
    mine.printStatus();

    // Mine explodes and generates an Explosion
    Explosion explosion = mine.explode();
    mine.printStatus();

    // Apply the explosion to the ship
    explosion.apply(ship);

    // Print the ship's position after the explosion
    ship.printPosition();

    return 0;
}
