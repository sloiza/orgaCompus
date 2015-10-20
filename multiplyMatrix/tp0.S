#include <mips/regdef.h>
#include <sys/syscall.h>
	.text
	.abicalls
	.align 2
	.globl	multiplicarMatrices
	.ent 	multiplicarMatrices
multiplicarMatrices:
		
	.frame  $fp, 32, ra
	.set 	noreorder
	.cpload t9
	.set	reorder
	subu sp, sp,80
	.cprestore 64
	sw ra, 72(sp)
	sw $fp, 68(sp)
	move $fp,sp
	


	sw a0,80(sp) #f1
	sw a1,84(sp) #c1
	sw a2,88(sp) #f2
	sw a3,92(sp) #c2

	lw a0, 80(sp) #f1 LTA
	lw a1,84(sp) #c1 LTA
	lw a2,88(sp) #f2 LTA
	lw a3,92(sp) #c2 LTA
	lw t0, 96(sp) #dir M1
	lw t1, 100(sp) #dir M2
	lw t2,104(sp) #dir outs

	sw t0, 16(sp)
	sw t1, 20(sp)
	sw t2, 24(sp)

	lw t0,80(sp) #t0=f1
	lw t1,84(sp) #t1=c1
	lw t2,88(sp) #t2=f2
	lw t3,92(sp) #t3=c2

	sw t0, 0(sp) #guardo f1
	sw t1, 4(sp)
	sw t2, 8(sp)
	sw t3, 12(sp)

	li t0,0
	sw t0,28(sp)
	sw t0,32(sp)
	lw t1,0(sp) #t1=f1
	lw t2,4(sp) #t2=c1
	mul t1,t1,t2 #t1=f1*c1
	sw  t1,48(sp)

	lw t1,8(sp) #t1=f2
	lw t2,12(sp) #t2=c2
	mul t1,t1,t2 #t1=f2*c2
	sw  t1,52(sp)

f1: lw t0, 32(sp)  #t0= i
	lw t1, 48(sp)  #t1 = f1*c1
	bge t0,t1,endf1  #i< f1*c1
	li  t0,0
	sw  t0,40(sp) # k=0
f2: lw  t0,40(sp) #t0 = k
	lw  t1,12(sp)  #t1= c2
	bge t0,t1,endf2   #k<c2
	li.d  $f0,0.00000  #f0=sum=0
	lw  t1,32(sp)
	sw  t1, 44(sp) #m =i
	lw  t2, 40(sp) #t2=k
	sw  t2, 36(sp) #j=k
f3: lw  t2, 36(sp) #t2 =j
	lw  t3, 52(sp) #t3=f2*c2
	bge t2,t3,endf3 #j< f2*c2
	lw  t3, 16(sp) #t3=m1
	sll t2,t2,3 #j=j*8 (8bytes)
	addu t3,t3,t2  #t3 = &m1[j]
	lw t1,44(sp) #t1=m
	lw  t4, 20(sp) #t4=m2
	sll t1,t1,3  #t1= m*8
	addu t4,t4,t1  #t4= &m2[m]
	l.d   $f2,0(t3) #f1 = m1[j]
	l.d   $f4,0(t4) #f2= m2[m]
	mul.d $f2,$f2,$f4
	add.d $f0,$f0,$f2
	lw  t1,44(sp)
	addi t1,t1,1
	sw  t1,44(sp) # m++
	lw  t1,36(sp) #t1=j
	lw  t2,12(sp)  #t2 =c2
	addu t1,t1,t2  #t1= j+c2
	sw   t1,36(sp) #j= j+C2
	j    f3
endf3: lw t1, 24(sp) #t1=out
		lw t2, 28(sp) #t2=pos
		sll t2,t2,3  #t2=pos*8
		addu t1,t1,t2 # t1= &out[pos]
		s.d  $f0,0(t1)  #out[pos]=sum
		lw t2,28(sp) #t2=pos
		addi t2,t2,1 #pos++
		sw  t2,28(sp)
		lw  t0,40(sp)
		addi t0,t0,1 #k++
		sw t0,40(sp)
		j   f2
endf2: lw t0, 32(sp) #t0 = i
		lw t1,4(sp) #t1 =c1
		addu t0,t0,t1 # i=i+c1
		sw  t0,32(sp)
		j  f1









#f1: lw t0,32(sp)




#sw t0,96($fp) #dir M1
#sw t1,100($fp) #dir M2
#sw t3,104($fp) #dir outs
	#lw t0,96(sp)
	#li t3,0
	#sll t3,t3,3
	#lw t1,0(t0)
	#lw t1, 84(sp)
	#lw t2,84(sp)
#	li  t4,1
#	lw  t0,96(sp)  #t0= array m1
#	l.d $f4,0(t0)  #t2= m1[0]
#	lw  t3,104(sp) #t3=array out
#	s.d  $f4,0(t3)
#
#	sll t4,t4,3
#	addu t0,t0,t4
#	addu t3,t3,t4
#	l.d   $f2,0(t0)
#
#	add.d $f0,$f2,$f4
#
#	s.d   $f0,0(t3)



	#la t1, hola
	#addu t1,t1,t2



#	li v0,4
#	li a0, 1
#	la a1, 0(t1)
#	li a2, 10
#	syscall

#	li v0,4
#	li a0,1
#	la a1, 0(t1)# print("hola: ");
#	li a2,9
#	syscall




#
#
#
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



endf1: 	move sp, $fp
	lw $fp, 68(sp) #recupero fp
	lw ra, 72(sp) #recupero ra
	addu sp,sp,80
	jr ra
	.end multiplicarMatrices

	.rdata

hola:		.asciiz "holalqpeorjfngjkwkwwkwkwkaaa:\n"
