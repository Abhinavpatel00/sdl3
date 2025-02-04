#include <SDL3/SDL.h>
#include <stdio.h>
#include "types.h"

// Define the world_position structure
#define TILE_COUNT_Y 10
#define TILE_COUNT_X 10
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

internal inline void
RecononicalizeCoord(world *World, uint32 *Tile, real32 *TileRel) {
  // NOTE: world is assumed to be toroidal
  int32 Offset = FloorReal32ToInt32(*TileRel / World->TileSizeInMeters);
  *Tile += Offset;
  *TileRel -= Offset * World->TileSizeInMeters;

  Assert(*TileRel >= 0);
  Assert(*TileRel < World->TileSizeInMeters);
}

internal inline world_position
RecononicalizePosition(world *World, world_position Pos) {
  world_position Result = Pos;
  RecononicalizeCoord(World, &Result.AbsTileX, &Result.TileRelX);
  RecononicalizeCoord(World, &Result.AbsTileY, &Result.TileRelY);
  return Result;
}

// Function to draw a rectangle using SDL
void DrawRectangle(SDL_Renderer *renderer, float RealMinX, float RealMinY, float RealMaxX, float RealMaxY, float R, float G, float B) {
    SDL_FRect rect = {RealMinX, RealMinY, RealMaxX - RealMinX, RealMaxY - RealMinY};
    SDL_SetRenderDrawColor(renderer, (int)(R * 255), (int)(G * 255), (int)(B * 255), 255);
    SDL_RenderFillRect(renderer, &rect);
}

// Function to render the tile map
void RenderTileMap(SDL_Renderer *renderer, uint32_t Tiles[TILE_COUNT_Y][TILE_COUNT_X], int tileSize, float centerX, float centerY) {

    for (int relY = 0; relY < TILE_COUNT_Y; relY++) {
        for (int relX = 0; relX < TILE_COUNT_X; relX++) {
            float tileMinX = relX * tileSize + centerX - TILE_COUNT_X * tileSize / 2;
            float tileMinY = relY * tileSize + centerY - TILE_COUNT_Y * tileSize / 2;
            float gray = (Tiles[relY][relX] == 0) ? 0.5f : 1.0f;
            DrawRectangle(renderer, tileMinX, tileMinY, tileMinX + tileSize, tileMinY + tileSize, gray, gray, gray);
        }
    }
}

// Function to render the player
void RenderPlayer(SDL_Renderer *renderer, float centerX, float centerY, float playerRelX, float playerRelY, float playerWidth, float playerHeight) {
    float playerMinX = centerX + playerRelX * 55 - 0.5f * playerWidth;
    float playerMaxX = playerMinX + playerWidth;
    float playerMinY = centerY + playerRelY * 55;
    float playerMaxY = playerMinY + playerHeight;

    DrawRectangle(renderer, playerMinX, playerMinY, playerMaxX, playerMaxY, 1.0f, 1.0f, 0.0f);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer("",WINDOW_WIDTH,WINDOW_HEIGHT, 0, &window, &renderer);

    if (!window || !renderer) {
        printf("Failed to create window or renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Game variables
    uint32 Tiles[TILE_COUNT_Y][TILE_COUNT_X] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}
    };

    float centerX = 400.0f;  // Center X (screen center)
    float centerY = 300.0f;  // Center Y (screen center)
    float playerRelX = 5.0f; // Player's relative X position (tile-based)
    float playerRelY = 5.0f; // Player's relative Y position (tile-based)
    float playerWidth = 0.75f;
    float playerHeight = 1.4f;
    int tileSize = 60; // Tile size in pixels

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        // Clear the screen with a black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render the tile map
        RenderTileMap(renderer, Tiles, tileSize, centerX, centerY);

        // Render the player
       RenderPlayer(renderer, centerX, centerY, playerRelX, playerRelY, playerWidth, playerHeight);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
