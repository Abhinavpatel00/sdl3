#include <SDL3/SDL.h>
#include <stdio.h>

// Main entry point
int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_CreateWindowAndRenderer("My SDL Window", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS, &window, &renderer);

    if (!window || !renderer) {
        printf("Failed to create window or renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        
       float x = 100, y = 100, width = 200, height = 150;
      for (float i = 0; i < height; i++) {
            SDL_RenderLine(renderer, x, y + i, x + width, y + i); // Draw each horizontal line
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
