section .text
global ft_strcmp

ft_strcmp:
    xor rcx, rcx

.loop:
    movzx eax, byte [rdi + rcx]
    movzx edx, byte [rsi + rcx]

    cmp eax, edx
    jne .diff

    cmp byte [rsi + rcx], 0
    je .end

    inc rcx
    jmp .loop

.diff:
    sub eax, edx
    ret

.end:
    mov rax, 0
    ret