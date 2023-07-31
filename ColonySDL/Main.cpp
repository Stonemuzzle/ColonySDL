#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <SDL.h>
#undef main
#include "Logging.hpp"
#include "json.hpp"
#include <SDL_image.h>
#include "Render.hpp"
#include <vector>


using json = nlohmann::json;


int main() {
    std::ifstream f("config.json");
    json data = json::parse(f);

    std::string directory_path = "textures";
    
    const int SCREEN_WIDTH = data["SCREEN_WIDTH"];
    const int SCREEN_HEIGHT = data["SCREEN_HEIGHT"];
    const int TILE_SIZE = data["TILE_SIZE"];
    const int MAP_WIDTH = data["MAP_WIDTH"]; // Number of tiles horizontally
    const int MAP_HEIGHT = data["MAP_HEIGHT"]; // Number of tiles vertically
    const int NUM_LAYERS = data["NUM_LAYERS"]; // Number of layers in your tile-based space
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* tilesetTexture = nullptr;
    
    // Initialize SDL and create a window and renderer
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Tile-Based Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initialize SDL_image for loading images (you can add error handling here)
    IMG_Init(IMG_INIT_PNG);

    // Load your tileset image and store it in tilesetTexture (you can add error handling here)
    auto iterator_object = std::filesystem::directory_iterator(directory_path);
    int fileCount = std::count_if(
        begin(iterator_object),
        end(iterator_object),
        [](auto& entry) { return entry.is_regular_file(); }
    );
    std::vector<SDL_Texture*> tileSet;
    int totalNumberOfTilesInTileset = 0;
    std::vector<std::vector<std::vector<int>>> tileMap(NUM_LAYERS, std::vector<std::vector<int>>(MAP_HEIGHT, std::vector<int>(MAP_WIDTH)));
    
    for (auto& file : iterator_object) {
        std::filesystem::path file_path = file.path();
        tileSet.push_back(IMG_LoadTexture(renderer, file_path.string().c_str()));
        totalNumberOfTilesInTileset++;
    }
    // Set up your tile map and layers (for demonstration purposes, initialize the map with random tiles)
    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                tileMap[layer][y][x] = rand() % totalNumberOfTilesInTileset;
            }
        }
    }

    // Main loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the tile map
        renderTileMap(tileMap);

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(tilesetTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}