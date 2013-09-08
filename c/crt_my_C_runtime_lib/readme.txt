These are source files which can be used to make a C runtime lib.
I get it from a popular book, I bought that boom with my money, so I 
suppose I can use the codes in it freely. The codes are designed to
run on both Windows and Linux, but I am a Linux programmer, I only
care about Linux version, so what you can see here is Linux version
CRT.

To compile it:
# gcc -c -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c stdio.c string.c printf.c

And make the lib:
# ar -rs minicrt.a malloc.o printf.o stdio.o string.o

To test it:
# gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c

To use it:
# ld -static -e mini_crt_entry entry.o test.o minicrt.a -o test
