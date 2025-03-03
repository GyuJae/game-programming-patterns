#pragma once
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

class Texture {
	Texture() {}
};

class Terrain {
public:
	Terrain(int movementCost, bool isWater, Texture texture): movementCost_(movementCost), isWater_(isWater), texture_(texture) {};

	int GetMovementCost() { return this->movementCost_; }
	bool IsWater() { return this->isWater_; }
	const Texture& GetTexture() const { return this->texture_; }

private:
	int movementCost_;
	bool isWater_;
	Texture texture_;
};

class TerrainFactory {
public:
	static TerrainFactory instance;
	static TerrainFactory& GetInstance() {
		return instance;
	}

	const Terrain& GetTerrian(const std::string& type) {
		// TODO assert
		return *terrains_[type];
	}

private:
	unordered_map<string, shared_ptr<Terrain>> terrains_;
	Texture grassTexture_, hillTexture_, riverTexture_;
};

class World {
public:
    World() { generateTerrain(); }

    const Terrain& getTile(int x, int y) const { return *tiles_[x][y]; }

    void printTerrain(int x, int y) {

    }

private:
    static const int WIDTH = 10;
    static const int HEIGHT = 10;

    shared_ptr<Terrain> tiles_[WIDTH][HEIGHT];

    void generateTerrain() {
        TerrainFactory& factory = TerrainFactory::GetInstance();

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                if ((x + y) % 7 == 0) {
                    tiles_[x][y] = make_shared<Terrain>(factory.GetTerrian("hill"));
                }
                else if ((x + y) % 5 == 0) {
                    tiles_[x][y] = make_shared<Terrain>(factory.GetTerrian("river"));
                }
                else {
                    tiles_[x][y] = make_shared<Terrain>(factory.GetTerrian("grass"));
                }
            }
        }
    }
};
