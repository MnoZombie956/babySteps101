# Marco Túlio Siqueira da Mata 20193007156
	.data
vet1: .word 29,29,-29,2,2,-2,7,3,3,3,-7,11,11,-11,3,0,0,0,16
vet1_size: .word 19 # o tamanho do vetor1 de teste
vet2: .space 76 # espaço pior caso de vetor, vet1_size*4Bytes para inteiros
vet2_size: .word 0  # o vetor ainda não existe
msg: .asciiz "resultado:\n\n"
msg1:.asciiz "primos:\n"
msg2:.asciiz "sem repetidos:\n"
msg3:.asciiz "crescente:\n"
quebra: .asciiz "\n"
spc: .asciiz " "

	.text          
	.globl main

######################################### funcao main
main:
	la $a0, msg   # load the argument string
    li $v0, 4     # load the system call (print)
    syscall       # print the string

  	la $s0, vet1      # reg[s0] = &vet1[0]
  	lw $s1, vet1_size # reg[s1] = vet1_size
	la $s2, vet2      # reg[s2] = &vet2[0]
	lw $s3, vet2_size # reg[s3] = vet2_size
	addi $s4, $zero, 0#futuro tamanho em bytes de vet2

	addi $t0,$zero,0 # loop2 i=0
	addi $t1,$s0,-4  # memIndex1=vet1-4
	addi $t2,$s2,0  # memIndex2=vet2

#usa a subrotina de eh primos para criar o vet2
criandoVet2:
	bge $t0, $s1, vet2Pronto # while i<vet1_size
	
	addi $t1, $t1, 4         # memIndex1 += 4
	lw $a2, ($t1)            # a2 = s0[memIndex1+&vet1[0]]
	jal eh_primo             # a2 eh primo ? go to check it
 
	beqz $v0, naoAdd         # dependendo do retorno v0 do eh_primo (1:0)
	sw $a2, 0($t2)           # adicione ao vet2, &(t2==(s4+4*i))=a2
	addi $t2,$t2, 4          # memIndex2 += 4, vet2 new size em bytes
	addi $s3, $s3, 1         #vet2 new size
naoAdd: 		
	addi $t0,$t0,1   # i++
	b criandoVet2	
vet2Pronto:
	move $s4, $t2     
	  
    la $a0, msg1  # load the argument string
    li $v0, 4     # load the system call (print)
    syscall       # print the string     
	
	jal printVet2
#agr remova repetidos de vet2
	jal removeRep
	
	la $a0, msg2  # load the argument string
    li $v0, 4     # load the system call (print)
    syscall       # print the string   
    
	jal printVet2
#ordene o vet2	
	jal ordenaVet
	
	la $a0, msg3  # load the argument string
    li $v0, 4     # load the system call (print)
    syscall       # print the string   
    
	jal printVet2 
    li $v0, 10      # exit program
    syscall   
    
######################################### fim main

######################################### funcao printVet
printVet2:
	addi $t0,$zero,0 # i=0
	addi $t2,$s2,0  # memIndex2=vet2
printVet2s:
	bge $t0, $s3, printVet2e # while(i<vet2_size)

	lw $a0, ($t2)   
    li $v0, 1 # 1 codigo para exibir int  
    syscall   # print int number vet2[i]
 
    la $a0, spc 
    li $v0, 4 # 4 codigo para exibir space     
    syscall   # space btw numbers   

	addi $t2,$t2,4
	addi $t0,$t0,1
	b printVet2s
 printVet2e:  
 	la $a0, quebra   # load the argument string
    li $v0, 4     # load the system call (print)
    syscall       # print the string
 	jr $ra
######################################### fim printVet

######################################### funcao eh primo
eh_primo:
	addi $t8,$zero,2 # t8=i=2
	div $t9, $a2, 2  # t9=n/2

	blt $a2, 2, return0 # se n<2 retorne 0
	beq $a2, 2, return1 # se n==2, unica excessão retorne 1 

loop1s:
	bge $t8, $t9, return1 #enquanto i<n/2

	div $a2, $t8        # hi=a2/t8 
	mfhi $t7            # t7=hi
	beqz $t7, return0 # n % t8 == 0 return0

	addi $t8,$t8,1      # t8+=1
	b loop1s
return1:
	addi $v0, $zero, 1 # retorne vdd
	b eh_primo_fim
return0:
	addi $v0, $zero, 0 # retorne falso
eh_primo_fim:
	jr $ra
######################################### fim eh primo

######################################### funcao retireRep
removeRep:
	#$s2, &vet2[0]  e  $s4, &vet2[vet2_size]
	add $t0,$zero,$s2 # i 
	addi $t1,$zero,0   # t1 = vet2[i]
	addi $t2,$zero,0   #t2=vet2[i+1]
	addi $t3,$zero,0   # j
	addi $t4,$zero,0   # vet2[j+1]
	l1s:                  #loop 1 start
		bgt $t0, $s4, l1e #while i<endereço final vet2

		lw $t1, ($t0)     #t1=vet2[i]
		lw $t2, 4($t0)    #t2=vet2[i+1]
		bne $t1, $t2, neq # go if vet[i]!=vet[i+1]

		
		addi $t3,$t0,0        # j=i
		l2s:		          # do the shift here
			bge $t3, $s4, l2e # while j<vet2_size

			lw $t4, 4($t3)    # t4 = *t3 + 4 = vet2[j+1]
			sw $t4, ($t3)     # vet2[j]=vet[j+1]	

			addi $t3,$t3,4 # j++
			b l2s
		l2e:
		
		subi $s4,$s4,4#endereço onde acaba diminui
		subi $s3,$s3,1#tamanho inteiro do vetor tbm diminui
		subi $t0,$t0,4#i-- para recheck
	neq:
		addi $t0,$t0,4#i+=1 procede loop
		b l1s
l1e:
	jr $ra
######################################### fim retireRep

######################################### funcao ordena
	#$s2, &vet2[0]  e  $s4, &vet2[vet2_size]
ordenaVet: 
	add $a0, $zero,$s2    # first position, works as Index
    add $a1, $zero, $s4    # last postion 
    addi $a2, $a1, -4    #last position for j, i-4  
    
    add $a3, $0, $0   #j-th position, goes until i-1
    add $t0, $0, $0   # *j
    add $t1, $0, $0   # *(j+1)
    add $t2, $0, $0   #aux for swap
    
outerLs_OV:
	bge $a0, $a1, outerLe_OV 
		
	addi $a3, $a0, 0      #j=i
	innerLs_OV:
		slt $t4, $a3, $a2 # t4 = j<i-1 ? 
		beqz $t4, innerLe_OV
		
		lw $t0, ($a3)     # t0 = vet[j]
		lw $t1, 4($a3)    # t1 = vet[j+1]
		
		sgt $t5, $t0, $t1 # t5 = vet[j] > vet[j+1] ?
		beqz $t5, innerLc_OV
		
		sw $t1, 0($a3)    # vet[j]=the lesser
		sw $t0, 4($a3)    # vet[j+1]=the greater	
		
	    addi $a3, $s2, -4 # reset j
	innerLc_OV:
		addi $a3, $a3, 4 # j++
		b innerLs_OV
	innerLe_OV:	
outerLc_OV:
	addi $a0, $a0, 4     # i++
	b outerLs_OV
outerLe_OV:   
	jr $ra
######################################### fim ordena
