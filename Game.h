#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

// Ship class, inherits from GameEntity
class Ship : public GameEntity {
public:
    Ship(int x, int y) : GameEntity(x, y, ShipType) {}

    void move(int dx, int dy) {
        position = std::make_tuple(std::get<0>(position) + dx, std::get<1>(position) + dy);
    }
};

// Explosion class, inherits from GameEntity
class Explosion : public GameEntity {
public:
    Explosion(int x, int y) : GameEntity(x, y, ExplosionType) {}

    void apply(GameEntity& entity) override {
        entity.position = std::make_tuple(-1, -1);
        entity.type = NoneType;
    }
};

// Mine class, inherits from GameEntity
class Mine : public GameEntity {
public:
    Mine(int x, int y) : GameEntity(x, y, MineType) {}

    Explosion explode() {
        type = NoneType;
        return Explosion(std::get<0>(position), std::get<1>(position));
    }
};

// Utils class with static helper methods
class Utils {
public:
    static std::tuple<int, int> generateRandomPos(int gridWidth, int gridHeight) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        int x = std::rand() % gridWidth;
        int y = std::rand() % gridHeight;
        return std::make_tuple(x, y);
    }

    static double calculateDistance(std::tuple<int, int> pos1, std::tuple<int, int> pos2) {
        int x1 = std::get<0>(pos1);
        int y1 = std::get<1>(pos1);
        int x2 = std::get<0>(pos2);
        int y2 = std::get<1>(pos2);

        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }
};

// Game class definition
class Game {
private:
    std::vector<GameEntity*> entities;  // Vector of GameEntity pointers

public:
    // Getter and setter for entities
    std::vector<GameEntity*> get_entities() const {
        return entities;
    }

    void set_entities(const std::vector<GameEntity*>& newEntities) {
        entities = newEntities;
    }

    // Method to initialize the game with ships and mines
    std::vector<GameEntity*> initGame(int numShips, int numMines, int gridWidth, int gridHeight) {
        for (int i = 0; i < numShips; ++i) {
            auto [x, y] = Utils::generateRandomPos(gridWidth, gridHeight);
            entities.push_back(new Ship(x, y));
        }

        for (int i = 0; i < numMines; ++i) {
            auto [x, y] = Utils::generateRandomPos(gridWidth, gridHeight);
            entities.push_back(new Mine(x, y));
        }

        return entities;
    }

    // Game loop simulation
    void gameLoop(int maxIterations, double mineDistanceThreshold) {
        int iteration = 0;
        while (iteration < maxIterations) {
            // Move all Ship objects by (1, 0)
            for (auto entity : entities) {
                if (entity->getType() == ShipType) {
                    static_cast<Ship*>(entity)->move(1, 0);
                }
            }

            // Check proximity between Ships and Mines
            for (auto shipEntity : entities) {
                if (shipEntity->getType() == ShipType) {
                    for (auto mineEntity : entities) {
                        if (mineEntity->getType() == MineType) {
                            double distance = Utils::calculateDistance(shipEntity->getPos(), mineEntity->getPos());
                            if (distance <= mineDistanceThreshold) {
                                Explosion explosion = static_cast<Mine*>(mineEntity)->explode();
                                explosion.apply(*shipEntity);
                            }
                        }
                    }
                }
            }

            // Check if all ships are destroyed
            bool allShipsDestroyed = true;
            for (auto entity : entities) {
                if (entity->getType() == ShipType) {
                    allShipsDestroyed = false;
                    break;
                }
            }

            if (allShipsDestroyed) {
                std::cout << "All ships destroyed. Game over!" << std::endl;
                return;
            }

            iteration++;
        }

        std::cout << "Max iterations reached. Game over!" << std::endl;
    }

    // Destructor to clean up dynamically allocated memory
    ~Game() {
        for (auto entity : entities) {
            delete entity;
        }
    }
};

// Main function to test the game
int main() {
    Game game;

    // Initialize the game with 3 ships and 2 mines on a 10x10 grid
    game.initGame(3, 2, 10, 10);

    // Start the game loop with a max of 10 iterations and a mine distance threshold of 2.0
    game.gameLoop(10, 2.0);

    return 0;
}
