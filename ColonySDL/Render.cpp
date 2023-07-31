#include <SDL.h>
#undef main
#include "json.hpp"
#include <fstream>
#include <vector>

using json = nlohmann::json;

std::ifstream f("config.json");
json data = json::parse(f);

const int SCREEN_WIDTH = data["SCREEN_WIDTH"];
const int SCREEN_HEIGHT = data["SCREEN_HEIGHT"];
const int TILE_SIZE = data["TILE_SIZE"];
const int MAP_WIDTH = data["MAP_WIDTH"]; // Number of tiles horizontally
const int MAP_HEIGHT = data["MAP_HEIGHT"]; // Number of tiles vertically
const int NUM_LAYERS = data["NUM_LAYERS"]; // Number of layers in your tile-based space

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* tilesetTexture = nullptr;

// Your tile map and layers (you can populate these as needed)
//int tileMap[NUM_LAYERS][MAP_HEIGHT][MAP_WIDTH];

// Function to render the tile map
void renderTileMap(const std::vector<std::vector<std::vector<int>>>& tileMap) {
    SDL_Rect srcRect;
    srcRect.w = TILE_SIZE;
    srcRect.h = TILE_SIZE;

    SDL_Rect dstRect;
    dstRect.w = TILE_SIZE;
    dstRect.h = TILE_SIZE;

    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                int tileID = tileMap[layer][y][x];

                // Calculate the position on the screen
                dstRect.x = x * TILE_SIZE;
                dstRect.y = y * TILE_SIZE;

                // Set the source rectangle to the corresponding tile in the tileset
                srcRect.x = (tileID % MAP_WIDTH) * TILE_SIZE;
                srcRect.y = (tileID / MAP_HEIGHT) * TILE_SIZE;

                // Render the tile from the tileset
                SDL_RenderCopy(renderer, tilesetTexture, &srcRect, &dstRect);
            }
        }
    }
}
