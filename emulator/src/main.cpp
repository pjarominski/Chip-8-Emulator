///////////////////////////////////////////////////////////////////////////////
//
// Name: Chip8 Emulator
// Description: Main entry point and emulation loop.
// Author: Patryk Jarominski
// License: MIT
// Copyright (C) 2026 Patryk Jarominski
//
///////////////////////////////////////////////////////////////////////////////

#include <SDL.h> 
#include <stdlib.h>
#include <stdio.h>
#include "chip8.h" 
#include "Window.h" 

// Display size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

int main(int argc, char* argv[])
 {
    // Ensure a ROM file was provided
    if (argc < 2) {
        printf("Usage: chip8 <ROM_PATH>\n");
        return 1;
    }

    chip8 myChip8;
    int scale = 10; // Scaling factor for the window
    bool quit = false;
    Window window(SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale);

    // Initialize systems
    if (!myChip8.loadApplication(argv[1])) exit(EXIT_FAILURE);
    if (!window.init()) exit(EXIT_FAILURE);

 
    uint32_t lastCycleTime = SDL_GetTicks();
    uint32_t timerAccumulator = 0;

    // Main emulation loop
    while (!quit) {
        uint32_t currentTime = SDL_GetTicks();
        uint32_t deltaTime = currentTime - lastCycleTime;
        lastCycleTime = currentTime;
        timerAccumulator += deltaTime;

        // Process user input
        window.handleInput(myChip8.key, quit);

        // Run one CPU cycle
        myChip8.emulateCycle();

        // Update CHIP-8 Timers at 60Hz (approx. every 16.6ms)
        if (timerAccumulator >= 16) { 
            if (myChip8.delay_timer > 0) myChip8.delay_timer--;
            if (myChip8.sound_timer > 0) {
                if (myChip8.sound_timer == 1) printf("BEEP!\n");
                myChip8.sound_timer--;
            }
            timerAccumulator = 0; // Reset accumulator
        }

        // Render if the draw flag is set
        if (myChip8.drawFlag) {
            window.update(myChip8.gfx);
            myChip8.drawFlag = false;
        }
        
        // Small delay to prevent 100% CPU usage
        SDL_Delay(1);
    }

   return 0;
 }