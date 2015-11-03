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

		sw		a0,80(sp) #f1
		sw 		a1,84(sp) #c1
		sw 		a2,88(sp) #f2
		sw 		a3,92(sp) #c2

		lw 		a0, 80(sp) #f1 LTA #cargo en registros los argumentos recibidos por a funci´on
		lw 		a1,84(sp) #c1 LTA
		lw 		a2,88(sp) #f2 LTA
		lw 		a3,92(sp) #c2 LTA
		lw 		t0, 96(sp) #dir M1
		lw 		t1, 100(sp) #dir M2
		lw 		t2,104(sp) #dir outs

		sw 		t0, 16(sp) #guardo en SF la direccion de m1, m2, out
		sw 		t1, 20(sp) 
		sw 		t2, 24(sp) 

		lw 		t0,80(sp) #t0=f1
		lw 		t1,84(sp) #t1=c1
		lw 		t2,88(sp) #t2=f2
		lw 		t3,92(sp) #t3=c2

		sw 		t0, 0(sp) #guardo f1, c1, f2,c2
		sw 		t1, 4(sp) 
		sw 		t2, 8(sp)
		sw 		t3, 12(sp)

		li 		t0,0 #cargo valor el valor 0 en t0
		sw 		t0,28(sp) #pos = 0
		sw 		t0,32(sp) # i = 0
		lw 		t1,0(sp) #t1=f1
		lw 		t2,4(sp) #t2=c1
		mul 	t1,t1,t2 #t1=f1*c1
		sw  	t1,48(sp) #cantidad de elementos matriz 1

		lw 		t1,8(sp) #t1=f2
		lw 		t2,12(sp) #t2=c2
		mul 	t1,t1,t2 #t1=f2*c2
		sw  	t1,52(sp) #cantidad de elementros matriz 2

f1: 	lw 		t0, 32(sp)  #t0= i
		lw 		t1, 48(sp)  #t1 = f1*c1
		bge 	t0,t1,endf1  #i< f1*c1
		li  	t0,0
		sw  	t0,40(sp) # k=0
f2:		lw  	t0,40(sp) #t0 = k
		lw  	t1,12(sp)  #t1= c2
		bge 	t0,t1,endf2   #k<c2
		li.d  	$f0,0.00000  #f0=sum=0
		lw  	t1,32(sp) #t1 = i
		sw  	t1, 44(sp) #m =i
		lw  	t2, 40(sp) #t2=k
		sw  	t2, 36(sp) #j=k
f3: 	lw  	t2, 36(sp) #t2 =j
		lw  	t3, 52(sp) #t3=f2*c2
		bge 	t2,t3,endf3 #j< f2*c2
		lw 		t1,44(sp) #t1=m
		lw  	t3, 16(sp) #t3=m1
		sll 	t1,t1,3 #t1=m*8 (8bytes)
		addu 	t3,t3,t1  #t3 = &m1[m]
		lw  	t4, 20(sp) #t4=m2
		sll 	t2,t2,3  #t2= j*8
		addu 	t4,t4,t2  #t4= &m2[j]
		l.d   	$f2,0(t3) #f1 = m1[m]
		l.d   	$f4,0(t4) #f2= m2[j]
		mul.d 	$f2,$f2,$f4
		add.d 	$f0,$f0,$f2
		lw  	t1,44(sp) #cargo en t1 el valor de m
		addi 	t1,t1,1 #m = m+1
		sw  	t1,44(sp) # actualizo m
		lw  	t1,36(sp) #t1=j
		lw  	t2,12(sp)  #t2 =c2
		addu 	t1,t1,t2  #t1= j+c2
		sw   	t1,36(sp) #j= j+C2
		j    	f3
endf3: 	lw 		t1, 24(sp) #t1=out
		lw 		t2, 28(sp) #t2=pos
		sll 	t2,t2,3  #t2=pos*8
		addu 	t1,t1,t2 # t1= &out[pos]
		s.d 	$f0,0(t1)  #out[pos]=sum
		lw 		t2,28(sp) #t2=pos
		addi 	t2,t2,1 #pos++
		sw  	t2,28(sp)
		lw  	t0,40(sp)
		addi 	t0,t0,1 #k++
		sw 		t0,40(sp)
		j   	f2
endf2: 	lw 		t0, 32(sp) #t0 = i
		lw 		t1,4(sp) #t1 =c1
		addu 	t0,t0,t1 # i=i+c1
		sw  	t0,32(sp)
		j  		f1


endf1: 	move sp, $fp
	lw $fp, 68(sp) #recupero fp
	lw ra, 72(sp) #recupero ra
	addu sp,sp,80 #restablezco stack frame
	jr ra
	.end multiplicarMatrices

