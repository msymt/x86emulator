#include <stdio.h>
#include <stdlib.h>

// メモリ: 1MB
#define MEMORY_SIZE (1024 * 1024);

typedef struct {
  // 汎用レジスタ
  uint32_t registers[REGISTERS_COUNT];

  // ELFAGSレジスタ
  uint32_t eflags;

  // メモリ(バイト列)
  uint8_t memory;

  // プログラムカウンタ
  uint32_t eip;
} Emulator;

Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp);

void destroy_emu(Emulator* emu);

void mov_r32_imm32(Emulator* emu);

void short_jump(Emulator* emu);

uint32_t get_code8(Emulator* emu, int index);
int32_t get_sign_code8(Emulator* emu, int index);
uint32_t get_code32(Emulator* emu, int index);
