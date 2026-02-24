# Chip-8 Emulator

A high-performance Chip-8 interpreter written in C++ using the SDL2 library. This project was developed as a portfolio piece to demonstrate low-level system emulation, memory management, and clean object-oriented design.

## Features
- **Full Instruction Set:** Support for all 35 standard Chip-8 opcodes.
- **Hardware Accelerated Graphics:** Rendering via SDL2 textures with automatic scaling to maintain aspect ratio and clarity.
- **Accurate Timing:** Implements a 60Hz frequency for both Delay and Sound timers, independent of the CPU instruction cycle.
- **Custom Window Abstraction:** A dedicated `Window` class to manage SDL2 resources, rendering states, and input polling.
- **Portability:** Designed with a clean separation between the core emulation logic (`chip8` class) and the platform-specific rendering (`Window` class).

## Tech Stack
- **Language:** C++17 (or higher)
- **Library:** SDL2 (Graphics, Input, and Timing)
- **Environment:** Developed and tested using Visual Studio 2022

## Controls
The original 4x4 hex keypad of the Chip-8 has been mapped to the modern QWERTY layout as follows:

| Chip-8 Key | PC Key |   | Chip-8 Key | PC Key |
| :---: | :---: | - | :---: | :---: |
| **1** | `1` | | **C** | `4` |
| **2** | `2` | | **D** | `R` |
| **3** | `3` | | **E** | `F` |
| **4** | `Q` | | **F** | `V` |
| **5** | `W` | | **8** | `S` |
| **6** | `E` | | **9** | `D` |
| **7** | `A` | | **0** | `X` |
| **A** | `Z` | | **B** | `C` |

*Press **ESC** to exit the emulator.*

## Project Structure
- `src/` - Implementation files (`.cpp`)
- `include/` - Header files (`.h`)
- `roms/` - Sample ROMs for testing (e.g., Pong, Tetris, Maze)
- `emulator.sln` - Visual Studio Solution file

## Build and Run
1. Clone the repository.
2. Open `emulator.sln` in Visual Studio 2022.
3. Ensure the **SDL2** library is installed (this project uses NuGet for dependency management).
4. Build the solution in **Release** / **x64** mode.
5. Run the emulator by passing the path to a ROM file as a command-line argument:
   ```bash
   emulator.exe roms/pong.ch8