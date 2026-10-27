; char *ft_strdup(const char *s)
; rdi = s    戻り値: rax = 複製した文字列(malloc 失敗なら NULL)
;

section .text
global ft_strdup
extern ft_strlen
extern malloc
extern ft_strcpy

ft_strdup:
    push rdi

    call ft_strlen
    inc rax
    mov rdi, rax

    call malloc wrt ..plt
    cmp rax, 0
    je .error

    mov rdi, rax
    pop rsi
    call ft_strcpy
    ret

.error:
    pop rdi
    ret