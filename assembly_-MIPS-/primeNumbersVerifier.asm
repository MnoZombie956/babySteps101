
////////////////////////////////////////////// main inicio
	.data

	vet1: .word 29,29,-29,2,2,-2,7,3,3,3,-7,11,11,-11,3,0,0,0,16
	//19 itens
	vet1_size: .word 76 // o tamanho do vetor1 de teste, 19*4
	vet2: .space 76     // espaço pior caso de vetor, vet1_size*4Bytes para inteiros
	vet2_size: .word 0  // o vetor que ainda não existe
	msg: .asciiz "vetor entrado:\n"
	res: .asciiz "resultado:\n"
	spc: .asciiz " "

	.text

	sysCall print_string(msg)
	sysCall print_vet(vet1,vet1_size)
	//supondo que um dia eu crie um compilador/interprete que converta para as intruções da ISA rsrs

	lwm $5, vet1      // interpilha2
	lwm $6, vet1_size // interpilha3
	lwm $0, vet2      // temp1
	lwm $1, vet2_size // temp2

	push $0
	// pilha :  acc=vet2
	atr $1            // fazendo com que vet2_size 
	                  // inicie como posição de memoria
	                  // inicial do vet2
	pop

	push $5
	atr $2            // index incrementado em bytes
	                  // inicia com o mesmo valor da primeira
	                  // posicao do vet1

main_L1s:
	push $6
	// pilha :  acc=i, vet1_size
	comp
	pop
	// pilha : acc=i
	big  main_L1e     //n saia enquanto i<vet1_size


	lwm $5, $2        // $5 interPilha1 = $2 (*i)

	bal eh_primo      // branch and link
	pushi 0
	push $10         // $10 resp de retorno
	// pilha : acc=i,0,$10
	comp 
	pop
	pop
	// pilha : acc=i
	beq main_pass     // se $10 == 0, passe

main_add2Vet2:

	swm $10, $1       // guarda o primo em vet2
	push $1           // coloca o vet2_size na pilha
	pushi add 4
	// pilha : acc=i,vet2_size,4
	// pilha : i,acc=vet2_size+4
	atr $1            // guarda o novo valor size
	pop
	// pilha : acc=i

main_pass:
	
	pushi add 4       // fazendo i+=4
	// pilha : acc=i, 4
	// pilha : acc=i+4
	atr $2
	bi main_L1s       // volte ao imediato da label
main_L1e:
	// apos: percorrer o vet1, chamar o eh_primo
	// para o numero na posição,
	// considerar o valor de retorno,
	// adicionar ou não o numero em vet2 e
	// incrementar ou não o novo tamanho de vet2,
	// imprima o resultado de vet2:
	sysCall print_string(res)
	sysCall print_string(vet2,vet2_size)
////////////////////////////////////////////// main fim
////////////////////////////////////////////// eh_primo inicio
// Supondo que o numero está no registrador $4(interPilha1),
// e o endereço de retorno do procedimento no registrador $10(retorno1)
eh_primo:
	nsf         // cria new stack frame
	// pilha : acc=null
	pushi add 2 // dois no acumulador, serve como indice
	// pilha : acc=2
	atr $0      // acumulador no registrador temp1

	rta $4      // acumulador recebe o numero
	// pilha : acc=n
	divi 2      // acumulador divide por 2, é ate onde o indice vai no loop
	// pilha : acc=n, 2
	// pilha : acc=n/2 
	atr $1      // coloca n/2 no registrador temp2
	pop         // retira n/2 da pilha
	// pilha : acc=null
	pushi 2
	// pilha : acc=2
	push $4     // coloca o numero(que esta no reg) a ser testado na pilha
	// pilha : acc=2, n

	comp        // compara o 2 e o numero, que estão na pilha 
	
	bil return0 // caso n>2 retorne falso
	beq return1 // caso n==2 retorne verdadeiro

	pop
	pop
	// pilha : acc=null
eh_p_L1:        // label do primeiro loop
	push $1     // n/2
	push $0     // indice
	// pilha : acc=$1, $0
	comp
	beq return1 // enquanto indice != n/2(arredondado para baixo), se não, retorne vdd

	push $4
	// pilha : acc=$1, $0, n		
	//divide o numero pelo indice e caso de %==0 retorne 0
	div         // os itens da pilha
	// pilha : acc=$1, n%$0, n/$0,
	pop         // remove a divisão da pilha
	pushi 0     // e acrescenta um 0 à pilha
	// pilha : acc=$1, n%$0, 0
	comp        // compara n%$0 e 0
	beq return0 // caso o modulo seja 0, vá para return0
	pop
	pop
	pop
	// pilha : acc=null


	push $0     //coloca o indice na pilha
	// pilha : acc=$0
	addi 1      // indice += 1
	// pilha : acc=$0+1
	atr $0      // guarda o acc no temp1
	pop         // remove a cedeula de index+1 da pilha

	bi eh_p_L1  // branch immediate para a label
return1:
	pushi 1
	atr $10     //retorno1 = 1
	pop
	bi eh_primo_fim
return0:
	pushi 0
	atr $10     //retorno1 = 1
	pop
eh_primo_fim:
	dsf         // deleta o stack criado para a função
	br $12      // volta para o endereço onde foi chamada, address1
////////////////////////////////////////////// eh_primo fim
