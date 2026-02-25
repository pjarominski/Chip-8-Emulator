#pragma once
#include "chip8.h"
#include <SDL.h>
class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;

public:
    // Constructor: sets window dimensions
    Window(int w, int h);
    // Destructor: cleans up SDL resources (RAII)
    ~Window();

    // Initializes SDL, the window, and the renderer
    bool init();
    // Updates the display using the CHIP-8 graphics buffer
    void update(const unsigned char* gfx);
    // Handles keyboard input and fills the CHIP-8 key array
    void handleInput(unsigned char* keys, bool& quit);
};

