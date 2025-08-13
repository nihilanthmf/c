#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int create_window(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(0) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow("Name", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!*window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    return 0;
}

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running = true;
    SDL_Event event;

    SDL_Rect player = {100, 100, 50, 50};
    SDL_Rect square = {200, 200, 100, 100};
    int speed = 1;

    bool collided = false;

    create_window(&window, &renderer);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player);
        SDL_RenderFillRect(renderer, &square);

        // input
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_ESCAPE]) running = false;
        if (keys[SDL_SCANCODE_D]) player.x += 1 * speed;
        if (keys[SDL_SCANCODE_A]) player.x += 1 * speed;
        if (keys[SDL_SCANCODE_W]) player.y += -1 * speed;
        if (keys[SDL_SCANCODE_S]) player.y += * 1 * speed;

        // collision
        if (player.x + player.w > square.x && player.x < square.x + square.w &&
            player.y + player.h > square.y && player.y < square.y + square.h) {
            collided = true;
        } else {
            collided = false;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }
}