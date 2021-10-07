/* nanoRisc - ALU */
/*
	0000 - add - standard - aez, aof - accumulator=pilhas[k][p]+pilhas[k][p+1]
	0001 - addi- linked   - aez, aof - accumulator=pilhas[k][p]+pura
	0010 - sub - standard - aez, aof - accumulator=accumulator=pilhas[k][p]-pilhas[k][p+1]
	0011 - subi- linked   - aez, aof - accumulator=accumulator=pilhas[k][p]-pura
	0100 - and - standard - accumulator=pilhas[k][p] AND pilhas[k][p+1]   //bit a bit do byte
	0101 - or  - standard - accumulator=pilhas[k][p] OR pilhas[k][p+1]    //bit a bit do byte
	0110 - nand- standard - accumulator=pilhas[k][p] NAND pilhas[k][p+1]  //bit a bit do byte
	0111 - nor - standard - accumulator=pilhas[k][p] NOR pilhas[k][p+1]   //bit a bit do byte
	1000 - xor - standard - accumulator=pilhas[k][p] XOR pilhas[k][p+1]   //bit a bit do byte
	1001 - xnor- standard - accumulator=pilhas[k][p] XNOR pilhas[k][p+1]  //bit a bit do byte
	1010 - mul - standard - aez, aof - accumulator=pilhas[k][p] * pilhas[k][p+1]
	1011 - muli- linked   - aez, aof - accumulator=pilhas[k][p] * puro
	1100 - div - standard - aez,     - accumulator=pilhas[k][p]           // pilhas[k][p+1]
	1101 - divi- linked   - aez,     - accumulator=pilhas[k][p]/puro
	1110 - not - standard - accumulator=NOT pilhas[k][p]                  //bit a bit do byte
	1111 - comp- standard - #101 = pilhas[k][p] == pilhas[k][p+1] ? (z01:<?(z00:z11))
*/
module shiftUnit(
	input shiftDirection,
	input unsigned [7:0] a,
	input unsigned [2:0] shiftAmount, // - 1
	output reg unsigned [7:0] result
);
	always@(*)begin
		if(shiftDirection == 0) begin
			result = a << shiftAmount + 1;
		end
		else if(shiftDirection == 1) begin
			result = a >> shiftAmount + 1;
		end
	end
endmodule
module arithmeticUnit(
	input [7:0] a,b,
	input [3:0] op,
	input en_unsigned,
	output zero, overflow, underflow, divByZero,
	output reg [1:0] comp,
	output reg [7:0] result,remainder
);
	reg opType; // se a operacao for +,-,* ou / ele recebe 1
	reg extendedResult; // sign bit
	
	always@(*) begin
		case(op)
			4'b0000,4'b0001:{extendedResult,result} <= a+b;//os x abrem espaco para os ops de imediatos
			4'b0010,4'b0011:{extendedResult,result} <= a-b;
			4'b0100:{extendedResult,result} <= a&b;
			4'b0101:{extendedResult,result} <= a|b;
			4'b0110:{extendedResult,result} <= ~(a&b);
			4'b0111:{extendedResult,result} <= ~(a|b);
			4'b1000:{extendedResult,result} <= a^b;
			4'b1001:{extendedResult,result} <= ~(a^b);
			4'b1010,4'b1011:{extendedResult,result} <= a*b;
			4'b1100,4'b1101: begin
				if(b!=8'b0)begin
					result<=a/b;
					remainder<=a%b;
				end
			end
			4'b1110:{extendedResult,result}= ~ a;
			4'b1111: begin
				if(a>b)
					comp<=2'b10;
				else if(a==b)
					comp<=2'b01;
				else // a<b
					comp<=2'b00;
			end
		endcase	
		if(op==4'b0000||op==4'b0001||op==4'b0010||op==4'b0011||op==4'b1010||op==4'b1011||op==4'b1100||op==4'b1101)
			opType <= 1;
		else
			opType <= 0;
	end
	
	assign divByZero = 
		((op[3]&(op[2])&(~op[1])&(~op[0]))|(op[3]&(op[2])&(~op[1])&op[0])) & (~(|b));
	
	assign underflow =  
		((~en_unsigned)&(opType)&({extendedResult, result[7]} == 2'b10 ? 1:0))
		|((en_unsigned)&(opType)&(a<b?1:0));
	assign overflow = 
		(~en_unsigned)&(opType)&({extendedResult, result[7]} == 2'b01 ? 1:0);
	/*adicionaria um para o caso unsigned mas vi que eh uma pratica
	comum deixar acontecer um "arithmetic wraparound"*/
	assign zero = ~(|result); // z=1 se r[7]&...&r[0]==0
endmodule
