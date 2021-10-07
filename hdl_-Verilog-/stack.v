/* nanoRisc - stack */
/* reset, push e pop sincronos; leitura assincrona */

module stack(
	input clk,
		   reset,
		   stackOp,//0=pop,1=push
	      stack_en,
		   stackOp_en,//habilitar as operações
	input [7:0] dataIn,
	output reg stackOverflow,
			     stackUnderflow,
	output reg [7:0] stackTop,  //stack peeking
		              stackTopMO //top Minus One
);

	reg [7:0] stack_mem [0:31];
	integer i;//index para reset loop
	integer stackPointer; //qnt elementos na stack

	task resetValues(
		inout reg stackOverflow,
				    stackUnderflow,
		inout integer stackPointer
	); 
		begin
			stackOverflow=0;
			stackUnderflow=0;
			stackPointer=-1;
		end
	endtask

	initial begin
		$monitor("clk:%d reset: %d stackOp: %d stack_en: %d stackOp_en: %d dataIn: %d so: %d su: %d st: %d sto: %d sp: %d",
			clk,
		   reset,
		   stackOp,//0=pop,1=push
	      stack_en,
		   stackOp_en,//habilitar as operações
			dataIn,
			stackOverflow,
			stackUnderflow,
			stackTop,
			stackTopMO,
			stackPointer
		);
		resetValues(
			stackOverflow,
			stackUnderflow,
		   stackPointer
		);
	end

	always@(posedge clk & stack_en)begin
		if(reset==1)begin
			resetValues(
				stackOverflow,
				stackUnderflow,
			   stackPointer
			);	
			stack_mem[0]=8'b0;
			stack_mem[31]='d31;
			for(i=1;i<=30;i=i+1)begin
				stack_mem[i]=i;
			end		
		end
		else if(reset==0 && stackOp_en==1)begin
			if(stackPointer<=-1 && stackOp==0)begin//detecta underflow
				stackUnderflow=1;
			end 
			else if(stackUnderflow!=1 && stackOp==0)begin//pop
				stackOverflow=0;
				stack_mem[stackPointer]=8'b0;
				stackPointer=stackPointer-1;
			end
			if(stackPointer>=31 && stackOp==1)begin//detecta overflow
				stackOverflow<=1;
			end 
			else if(stackOverflow!=1 && stackOp==1)begin//push
				stackUnderflow=0;
				stackPointer=stackPointer+1;
				stack_mem[stackPointer]=dataIn;
			end
			if(stackPointer>-1)begin
				stackTop = stack_mem[stackPointer];
			end
			if(stackPointer>0)begin
				stackTopMO = stack_mem[stackPointer-1];
			end
		end
	end
endmodule
