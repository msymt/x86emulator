#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "emulator.h"

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

// 汎用レジスタに32bitの即値をコピーする, mov命令に対応
void mov_r32_imm32(Emulator* emu){
  uint8_t reg = get_code8(emu, 0) - 0xB8; // オペコードを取得
  uint32_t value = get_code32(emu, 1);    // 32bitの即値
  emu->registers[reg] = value;
  emu->eip += 5;
}

// 1byteのメモリ番地をとるjmp命令に対応
void short_jump(Emulator* emu){
  int8_t diff = get_sign_code8(emu, 1); // オペランドに8bit(1byte)符号付整数としてdiffに読み込む
  emu->eip += (diff + 2);
}

uint32_t get_code8(Emulator* emu, int index){
  return emu->memory[emu->eip + index];
}
int32_t get_sign_code8(Emulator* emu, int index){
  return (int8_t)emu->memory[emu->eip + index];
}
uint32_t get_code32(Emulator* emu, int index){
  int i;
  uint32_t ret = 0;
  // リトルエンディアンでメモリの値を取得
  for(i = 0; i < 4; i++){
    // 8bitずつ左にずらす
    // 最終的に32bit取得
    ret |= get_code8(emu, index + i) << (i * 8);
  }
  return ret;
}\

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