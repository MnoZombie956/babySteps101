.globl main
		.data											# main
		Array: .word 1,2,3,4,32,43,12,98,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	# array 'a'
		sizeArray: .word 32									# tamanho 
		result:	.word 0
		x: .word 0
		y: .word 0

.text												
main:
		lw $s0, result									
		lw $t1, x
		lw $t2, y
		addi $t1, $t1, 31								# carregando x
		addi $t2, $t2, 34								# carregando y
		j FuncG
FuncG: 
		la $t0, Array									# endereco do array
		la $t5, sizeArray								# endereco do tamanho do array
		add $t3, $zero, $t1								
		j forG
Resultado:
		subi $t7, $t7, 4								# a = a - 4
		add $t5, $t7, $t0								# $t5 fica com endereco de Array[i-1]
		lw $s0, ($t5)									# result = array[i-1]
		j Exit		
forG:			
		slt $t4, $t3, $t2 								
		beq $t4, 0, Resultado								# se nao for menor, ir pra resultado 
		add $t7, $t3, $t3
		add $t7, $t7, $t7								# $t1 sempre multiplicado por 4
		add $t5, $t7, $t0								# $t5 contém o endereco de cada posição do Array
		add $t6, $t3, $t2								# $t6 = i + y 
		sw $t6, ($t5)									# salva 
		addi $t3, $t3, 1
		j forG										#"loop" chamado até q não satisfaça mais a condição
Exit:												# sair	
		li $v0, 10				
		syscall	
