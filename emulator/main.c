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

// エミュレータ構造体を生成し、初期化
// ファイルから機械語プログラムを読み込む処理
Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp){
  Emulator* emu = malloc(sizeof(Emulator));
  emu->memory = malloc(size);

  // 汎用レジスタの初期値を全て0
  memset(emu->registers, 0, sizeof(emu->registers));

  // レジスタの初期値を指定されたものとする
  emu->eip = eip;
  emu->registers[ESP] = esp;

  return emu;
}