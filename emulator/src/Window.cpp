#include "Window.h"
#include "SDL.h"
#include <stdio.h>
Window::Window(int w, int h)
    : window(nullptr), renderer(nullptr), texture(nullptr), width (w), height(h) {

}
Window::~Window() {
    // Release SDL resources in reverse order of creation
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    printf("SDL cleaned up successfully.\n"); 
} 
bool Window::init() {
    // Initialize SDL subsystems: Video for display, Audio for beeps, Timer for clock
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Create the application window
    window = SDL_CreateWindow("CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN);

    if (!window) return false;

    // Create an accelerated renderer (uses GPU if available)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    // Create a texture to act as the CHIP-8 display buffer (64x32 resolution)
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        64, 32);

    return true; //Success

}
void Window::update(const unsigned char* gfx) {
    uint32_t pixels[2048]; // Bufor 32-bit colors

    for (int i = 0; i < 2048; ++i) {
        // Map CHIP-8 binary pixels to ARGB colors
         // If gfx[i] is 1, set pixel to White (0xFFFFFFFF), otherwise Black (0xFF000000)
        pixels[i] = (gfx[i] == 1) ? 0xFFFFFFFF : 0xFF000000;
    }

    // Update the texture with the new pixel data
    SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(uint32_t));

    // Clear the screen, copy the texture, and present it
    SDL_RenderClear(renderer);
    // SDL_RenderCopy automatically scales the 64x32 texture to the window size
    SDL_RenderCopy(renderer, texture, NULL, NULL); // To automatycznie rozci¹gnie 64x32 na ca³e okno!
    SDL_RenderPresent(renderer);
}
void Window::handleInput(unsigned char* keys, bool& quit) {
    SDL_Event event;
    // Process all events in the queue
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) quit = true;

        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            // Set value to 1 if key is pressed, 0 if released
            int val = (event.type == SDL_KEYDOWN) ? 1 : 0;

            switch (event.key.keysym.sym) {
            // Map QWERTY keys to CHIP-8 Hex Keypad
            case SDLK_1: keys[0x1] = val; break;
            case SDLK_2: keys[0x2] = val; break;
            case SDLK_3: keys[0x3] = val; break;
            case SDLK_4: keys[0xC] = val; break;

            case SDLK_q: keys[0x4] = val; break;
            case SDLK_w: keys[0x5] = val; break;
            case SDLK_e: keys[0x6] = val; break;
            case SDLK_r: keys[0xD] = val; break;

            case SDLK_a: keys[0x7] = val; break;
            case SDLK_s: keys[0x8] = val; break;
            case SDLK_d: keys[0x9] = val; break;
            case SDLK_f: keys[0xE] = val; break;

            case SDLK_z: keys[0xA] = val; break;
            case SDLK_x: keys[0x0] = val; break;
            case SDLK_c: keys[0xB] = val; break;
            case SDLK_v: keys[0xF] = val; break;

            case SDLK_ESCAPE: quit = true; break;
            }
        }
    }
}