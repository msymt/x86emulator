## 1. C言語とアセンブリ言語

```
mov dword [ebp-0x4],0x0
```

数値0を, ebp-0x4で表される番地から始まるメモリ上の32bitの領域へコピーする.
コピー元の場所ではなく, コピーする値を直接指定できる.
このように直接指定する値の事を, **即値**や**リテラル**と呼ぶ.

**[ebp-0x4]**: 数値としてのebp-0x4ではなく, ebp-0x4が指すメモリ領域を表す.

アセンブリ言語における, あるメモリ領域を指定するために必要な情報
- 先頭の番地
- その領域の大きさ

```
#include <stdio.h>
#include <stdint.h>

int main(void) {
  int8_t s_val = -41;
  uint8_t u_val = s_val;
  printf("signed = %d (%x), unsigned = %d (%x)\n",
    s_val, s_val, u_val, u_val);
  return 0;
}

$ gcc -o compl compl.c
$ ./compl
signed = -41 (ffffffd7), unsigned = 215 (d7)
```

`%x`: int, short, unsigned int, unsigned shor<br>t
int8_t: signed char<br>
ffffffd7: s_valがint型に拡張<br>
C言語では, int型より小さな型をもつ値を式の中で使うと, まずint型への変換(汎整数拡張)が行われる.<br>

s_val: signedにより, 最上位ビットが1 => 1で空きビットを埋めて拡張<br>
u_val: unsignedにより, 最上位ビットが0 => 0で空きビットを埋めて拡張<br>


## 参考

https://os.mbed.com/handbook/C-Data-Types