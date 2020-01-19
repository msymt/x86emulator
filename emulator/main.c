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

// エミュレータを破壊
void destroy_emu(Emulator* emu){
  free(emu->memory);
  free(emu);
}

int main(int argc, char* argv[]){
  FILE* binary;
  Emulator* emu;

  if(argc != 2){
    fprintf(stderr, "Usage: px86 filename\n");
    exit(1);
  }

  // EIPが0, ESPが0x7c00の状態のエミュレータを作成
  emu = create_emu(MEMORY_SIZE, 0x0000, 0x7c00);
  
  // 読み取りモード
  binary = fopen(argv[1], "rb");
  if(binary == NULL){
    fprintf(stderr, "can't open %s file\n", argv[1]);
    exit(1);
  }
  
  // 機械語ファイルを読み込む(MAX 512 bytes)
  // binaryから1bytesずつ0x200個読み取り, emu->memoryへ格納
  fread(emu->memory, 1, 0x200, binary);
  fclose(binary);

  destroy_emu(emu);
  
  return 0;
}