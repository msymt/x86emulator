## ポインタとアセンブリ言語

CPUとメモリの関係

CPU                   (番地) ->   メモリ <br>
(eax, ecx, esp...) <-（データ)->


レジスタ  : CPU内部に存在.SRAMなため, 高速<br>
メモリ    : CPU外部に存在.DRAMなため, 低速 

lea命令: 指定されたメモリ番地を計算し, その結果の番地をレジスタに書き込む.
- mov命令との違い: **メモリに格納された値ではなく**, **メモリ番地そのものをレジスタに書き込む**点.
- (例)`lea eax, [ebp-0x8]`: ebp-0x8の値をeaxレジスタに格納
- Load Effective Address(実効番地のロード)
- 実効番地: 色々な計算を行った最終的な番地.
- []の中に指定した式により, 計算した最終的な番地をレジスタに読み込む(ロードする)ことからleaと命名


例

```
void func(void)
{
    int val;
    int *ptr = &val;
    *ptr = 41;
}
```

```
lea eax,  [ebp-0x8]
mov [ebp-0x4],  eax

mov eax,  [ebp-0x4]
mov dword [eax],  41
```

`ebp`: 0x00007bf8 として

```
int val;
int *ptr = &val;
```

`lea eax,  [ebp-0x8]`: 変数val([ebp-0x8])の番地がeaxに送り込まれる
- ebp-0x8: 0x00007bf0
- [ebp-0x8]: メモリアドレス0x00007bf0
- eax <=　0x00007bf0 

`mov [ebp-0x4],  eax`: eax(変数valの番地)の値が変数ptr([ebp-0x4])に格納
- eax: 0x00007bf0
- ebp-0x4:  0x00007bf4
- [ebp-0x4]: メモリアドレス0x00007bf4
- メモリアドレス0x00007bf4 <= eax(0x00007bf0)

```
*ptr = 41;
```

`mov  eax,  [ebp-0x4]`: 変数ptrの値をeaxに読み出す.
- ebp-0x4: 0x00007bf4 
- [ebp-0x4]: メモリアドレス0x00007bf4
- eax <= メモリアドレス0x00007bf4

`mov dword [eax],  41`: eaxで示される32bit(4バイト)のメモリ領域に41を書き込む
- eax: 0x00007bf4
- [eax]: メモリアドレス0x00007bf4
- `dword [eax]`: メモリアドレス上の0x00007bf4から32bit分
- メモリアドレス上の0x00007bf4から32bit(32bytes) <=  41

こうして, 変数valに41が書き込まれる.