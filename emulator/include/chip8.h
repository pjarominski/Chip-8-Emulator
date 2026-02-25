#pragma once
class chip8
{
	unsigned short opcode; // Current opcode

	unsigned char memory[4096]; //Memory - 4kB

	unsigned char V[16]; // 8 - bit, V-registers (V0-VF) 

	unsigned short I; // Index register
	unsigned short pc; // Program counter
	 
	unsigned short stack[16]; // Stack - 16 levels
	unsigned short sp; // Stack pointer

public:
  chip8();
  ~chip8();
  void init();
  bool loadApplication(const char* filename);
  void emulateCycle();
  bool drawFlag;

  unsigned char delay_timer; // Delay timer
  unsigned char sound_timer; // Sound timer

  unsigned char gfx[64 * 32]; // Total amount of pixels: 2048

  unsigned char key[16]; // Keyboard - 16 keys
};

