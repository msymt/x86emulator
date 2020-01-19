#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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