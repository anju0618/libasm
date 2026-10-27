section .text
global ft_strcpy

ft_strcpy:
    xor rcx, rcx

.loop:
    mov dl, byte [rsi + rcx]
    mov byte [rdi + rcx], dl
    cmp byte [rsi + rcx], 0
    je .end
    inc rcx
    jmp .loop

.end:
    mov rax, rdi
    ret