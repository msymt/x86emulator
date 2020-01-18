void func(void){
  int val = 0;
  val++;
}

/*
$ make all
$ ndisasm -b 32 casm-c-sample.bin
00000000  55                push ebp
00000001  48                dec eax
00000002  89E5              mov ebp,esp
00000004  C745FC00000000    mov dword [ebp-0x4],0x0
0000000B  8345FC01          add dword [ebp-0x4],byte +0x1
0000000F  90                nop
00000010  5D                pop ebp
00000011  C3                ret

$ gcc -c -g -o casm-c-sample.o casm-c-sample.c
// -c:リンクしない
$ objdump -d -S -M intel casm-c-sample.o
// -S:逆アセンブル結果にC言語のソースコードを混ぜる
casm-c-sample.o:     ファイル形式 elf64-x86-64


セクション .text の逆アセンブル:

0000000000000000 <func>:
void func(void) {
   0:   55                      push   rbp
   1:   48 89 e5                mov    rbp,rsp
  int val = 0;
   4:   c7 45 fc 00 00 00 00    mov    DWORD PTR [rbp-0x4],0x0
  val++;
   b:   83 45 fc 01             add    DWORD PTR [rbp-0x4],0x1
}
   f:   90                      nop
  10:   5d                      pop    rbp
  11:   c3                      ret   
*/