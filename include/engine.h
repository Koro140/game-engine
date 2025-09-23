#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>

#define WINDOW_NAME "GameEngine"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


typedef struct AppState {
	SDL_Window* window;
	SDL_Renderer* renderer;
}AppState;

#endif // !ENGINE_H