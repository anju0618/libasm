# libasm

x86-64 アセンブリ(NASM, Intel 構文)で、libc の一部の関数を自作するプロジェクト。

## 関数一覧

| 関数 | ファイル |
|---|---|
| `ft_strlen` | `ft_strlen.s` |
| `ft_strcpy` | `ft_strcpy.s` |
| `ft_strcmp` | `ft_strcmp.s` |
| `ft_write` | `ft_write.s` |
| `ft_read` | `ft_read.s` |
| `ft_strdup` | `ft_strdup.s` |
| `ft_calloc` | `ft_calloc.s` |

## ビルド

```sh
make          # libasm.a を生成
make test     # main.c と libasm.a をリンクして test を生成
make clean    # オブジェクトファイルを削除
make fclean   # libasm.a, test も削除
make re       # 作り直し
```

## アセンブリの解説

### セクションとシンボル

```nasm
section .text      ; 実行コードを置く領域
global ft_strlen   ; 他のファイル(C など)から見えるようにする
```

`global` を付けた名前が、C 側から呼べる関数名になる。

### レジスタ

CPU 内の高速な変数置き場。主なもの:

| レジスタ | 用途 |
|---|---|
| `rax` | 戻り値。計算用にも使う |
| `rdi` | 第1引数 |
| `rsi` | 第2引数 |
| `rdx` | 第3引数 |
| `rcx` | 汎用(カウンタによく使う) |

### レジスタのサイズ別の名前

1つのレジスタは、下位の一部だけを別名で扱える。

| 64bit | 32bit | 16bit | 8bit |
|---|---|---|---|
| `rax` | `eax` | `ax` | `al` |
| `rbx` | `ebx` | `bx` | `bl` |
| `rcx` | `ecx` | `cx` | `cl` |
| `rdx` | `edx` | `dx` | `dl` |
| `rsi` | `esi` | `si` | `sil` |
| `rdi` | `edi` | `di` | `dil` |

- `eax` は `rax` の下位32bit、`al` は下位8bit。
- 1バイト(`char`)を扱うときは8bitの名前、`int` は32bit、ポインタや `size_t` は64bitを使う。
- 32bitレジスタに書き込むと、64bitレジスタの上位32bitは自動で0になる。
- 8bit・16bitに書き込んでも、残りのビットは変わらない。上位に前の値が残るので、1バイトを読むときは `movzx` を使う。

### 呼び出し規約(System V ABI)

C と関数をやり取りするための決まり。

- 引数は `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` の順に渡される。
- 戻り値は `rax` に入れて `ret` する。
  - 呼ぶ側の C は、関数から戻った直後に `rax` を読む。
  - `int` は32bitなので、`eax` に入っていれば戻り値になる。
  - ポインタや `size_t` は `rax` 全体を使う。
- `rax`, `rcx`, `rdx`, `rsi`, `rdi`, `r8`〜`r11` は自由に壊してよい。
- `rbx`, `rbp`, `r12`〜`r15` は、関数が戻るときに元の値へ戻す。使うなら退避が必要。

### 使う命令

| 命令 | 意味 |
|---|---|
| `mov a, b` | `b` を `a` にコピー。メモリ同士は不可 |
| `movzx a, b` | 小さい `b` を、上位を0で埋めて大きい `a` にコピー(例: `movzx eax, byte [rdi]`) |
| `xor a, a` | `a` を 0 にする(定番の書き方) |
| `inc a` | `a` を +1 |
| `sub a, b` | `a = a - b` |
| `cmp a, b` | `a` と `b` を比べ、結果をフラグに残す。値は変えない |
| `jmp label` | 無条件でジャンプ |
| `je label` | 直前の `cmp` で等しければジャンプ |
| `jne label` | 直前の `cmp` で等しくなければジャンプ |
| `ret` | 呼び出し元へ戻る |

`cmp` は結果をフラグに残すだけで、その直後の `je` / `jne` などがフラグを見て分岐する。

### メモリアクセス

`[ ]` で囲むと、そのアドレスの中身を読み書きする。

```nasm
byte [rdi + rax]   ; rdi の指す先から rax バイト目の 1 バイト
```

サイズ指定(`byte`, `word`, `dword`, `qword`)が必要。メモリからメモリへ直接 `mov` はできないので、いったんレジスタを経由する。

### ラベル

`.loop` のように `.` で始まるラベルは、直前の関数ラベルに属するローカルラベル。ループや分岐の飛び先に使う。

## Resources
 - [命令セット](https://www.ibm.com/docs/ja/aix/7.3.0?topic=reference-instruction-set)
