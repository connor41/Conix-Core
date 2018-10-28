.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

#Open A20
in  $0x92, %al
or  $2, %al
out %al, $0x92

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	mov  $stack_top, %esp
	push %ebx
	push %eax
	call main
	cli
1: hlt
	jmp 1b

.size _start, . - _start
