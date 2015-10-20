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

#		li  t0, 0    	  #t0 =0 = i
#		sw  t0, 55(sp)    #pos=0
#		sw  t0, 44(sp)    #i=0
#f1: 	lw  t0, 44(sp)
#		lw  t1, 16(sp)    #t1= f1
#		lw  t2, 20(sp)    #t2=c1
#		mul t1,t1,t2      #t1= f1*c1
#		bge t0,t1,endf1   # i< f1*c1
#		li  t0, 0
#		sw  t0, 52(sp)	  # k=0
#f2: 	lw  t1, 28(sp)    # t1= c2
#		bge t0,t1,endf2   # k< c2
#		li  t0,0          #t0 = 0
#		lw  t1, 44(sp)    #t1= m =i
#		lw  t2, 52(sp)    #t2=k
#		sw  t2, 48(sp)	  #j=k
#f3:		lw  t3, 24(sp)    #t3= f2
#		lw  t4, 28(sp)    #t4= c2
#		mul t3,t3,t4      #t3= f2*c2
#		bge t2,t3,endf3   #j< f2*c2
#		lw  t3, 32(sp)    #t3= m1
#		lw  t4, 36(sp)    #t4= m2
#		addu t3,t3,t1     #t3= &m1[m]
#		addu t4,t4,t2     #t4= &m2[j]
#		lw   t5,0(t3)	  #t5= m1[m]
#		lw   t3,0(t4)	  #t3= m2[j]
#		mul  t3,t3,t5	  #t3=m1[m] * m2[j]
#		addu t0,t0,t3     #sum=+ m1[m]*m2[j]
#		addi t1,t1,1      # m++
#		lw   t3, 28(sp)   #t3 = c2
#		addu t2,t2,t3     #t2= j+c2
#		sw   t2,48(sp)	  #j= j+c2
#		j    f3
#endf3:  lw t1, 40(sp)	  #t1= out
#	    lw t2, 56(sp)	  #t2= pos
#	    addu t1,t1,t2     #t1= &out[pos]
#	    sw   t0,0(t1)	  # out[pos]= sum
#	    addi t2,t2,1	  # pos ++
#	    sw   t2,56(sp)
#	    lw   t0,52(sp)    # t0 =k
#	    addi t0,t0,1      # k++
#	    sw   t0,52(sp)
#	    j	 f2
#endf2:	lw   t0,44(sp)	  #t0 = i
#		lw 	 t1,20(sp)    #t1 =c1
#		addu t0,t0,t1	  # t0 = i+c1
#		sw	 t0,44(sp)	  # i = i+c1
#		j	 f1
#endf1:
#

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
