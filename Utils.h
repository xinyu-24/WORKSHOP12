#include <random>

class Utils {
public:
    // Generate a random position within the grid
    static std::tuple<int, int> generateRandomPos(int gridWidth, int gridHeight) {
        std::srand(static_cast<unsigned int>(std::time(0)));  // Use time as seed for randomness
        int x = std::rand() % gridWidth;  // Generate random number between 0 and gridWidth-1
        int y = std::rand() % gridHeight; // Generate random number between 0 and gridHeight-1
        return std::make_tuple(x, y);
    }

    // Calculate Euclidean distance between two positions
    static double calculateDistance(std::tuple<int, int> pos1, std::tuple<int, int> pos2) {
        int x1 = std::get<0>(pos1);
        int y1 = std::get<1>(pos1);
        int x2 = std::get<0>(pos2);
        int y2 = std::get<1>(pos2);

        // Calculate Euclidean distance
        double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
        return distance;
    }
};
