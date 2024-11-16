#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: replace int with this, char is 1 byte...
typedef signed char byte;

SDL_Window *initaliseWindow(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Window *window =
      SDL_CreateWindow("Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  return window;
}

int main(void) {

  SDL_Window *window = initaliseWindow();

  // gcc src/main.c -o main -lSDL2
  byte isRunning = 1;
  SDL_Event ev;

  while (isRunning) {
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT)
        isRunning = 0;
    }

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
