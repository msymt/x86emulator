## ポインタとアセンブリ言語

CPUとメモリの関係

| | | | |
|--|--|--|--|
|CPU(レジスタ群)|(番地)|->|メモリ|
|(同上)|(データ)|<->|(同上)|

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
- `ebp-0x8`: 0x00007bf0
- `[ebp-0x8]`: メモリアドレス0x00007bf0
- `eax` <=　0x00007bf0 

`mov [ebp-0x4],  eax`: eax(変数valの番地)の値が変数ptr([ebp-0x4])に格納
- `eax`: 0x00007bf0
- `ebp-0x4`:  0x00007bf4
- `[ebp-0x4]`: メモリアドレス0x00007bf4
- メモリアドレス0x00007bf4 <= eax(0x00007bf0)

```
*ptr = 41;
```

`mov  eax,  [ebp-0x4]`: 変数ptrの値をeaxに読み出す.
- `ebp-0x4`: 0x00007bf4 
- `[ebp-0x4]`: メモリアドレス0x00007bf4
- `eax` <= メモリアドレス0x00007bf4

`mov dword [eax],  41`: eaxで示される32bit(4バイト)のメモリ領域に41を書き込む
- `eax`: 0x00007bf4
- `[eax]`: メモリアドレス0x00007bf4
- `dword [eax]`: メモリアドレス上の0x00007bf4から32bit分
- メモリアドレス上の0x00007bf4から32bit(32bytes) <=  41

こうして, 変数`val`に41が書き込まれる.


## 初めてのエミュレータ

関数ポインタテーブル
- 関数を登録するための配列
- オペコードの値を添字に指定すると、そのオペコードに対応する処理を行う関数を呼び出せる仕組み

- `uint8_t`: 8bitのunsigned int
- `uint32_t`: unsigned long int, 32bitのunsigned int

```
void mov_r32_imm32(Emulator* emu);
```

オペコード: r: レジスタ番号として`0xb8 + r`
- オペコード自身がレジスタの指定を含むタイプの命令
- オペコードのすぐ後に32bitの即値が来る

```
void short_jump(Emulator* emu);
```

- 1byteのメモリ番地を取る、jmp命令(ショートジャンプ)に相当
- オペランドを8bit(1byte)の符号付整数をとり、eipに加算
- 現在地から前に127byte, 後ろに128byteの範囲内でジャンプ
- オペランドに8bit(1byte)符号付整数としてdiffに読み込む(`int8_t diff = get_sign_code8(emu, 1);`)
- jmp命令は**その次の命令の番地を基点に、ジャンプ先の計算を行うため、eipには`diff + 2(ショートジャンプ:2byte命令)`を加算**


`get_sign_code8`や`get_code32`など
- memory配列の指定した番地から8bit, 32bitの値を取得する
- 第二引数: その時のeipからのオフセットを指定すると、その番地から値を読み取って返す

`get_code32`
- for文で1byteずつ読み取るごとに8bitずつ左にずらす処理を行う