SYSWRITE = 4
FDNOSTD = 1
.global myputs
.text
myputs:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    movl $FDNOSTD, %ebx
    movl 8(%ebp), %ecx
    movl 12(%ebp), %edx
    movl $SYSWRITE, %eax
    int $0x80
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret
