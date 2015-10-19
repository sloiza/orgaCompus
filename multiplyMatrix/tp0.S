#include <mips/regdef.h>
#include <sys/syscall.h>
	.text
	.abicalls
	.align 2
	.globl	multiplicarMatrices
	.ent 	multiplicarMatrices
multiplicarMatrices:
		
	.frame  $fp, 48, ra
	.set 	noreorder
	.cpload t9
	.set	reorder
	subu sp, sp, 48
	.cprestore 32
	sw ra, 40(sp)
	sw $fp, 36(sp)
	move $fp,sp
	
	la a0, hola	# print("hola: ");
	li v0, 4
	syscall

	move sp, $fp
	lw $fp, 28(sp) #recupero fp
	lw ra, 32(sp) #recupero ra
	addu sp,sp,40 
	jr ra
	.end multiplicarMatrices

	.rdata

hola:		.asciiz "holaaaa:"
