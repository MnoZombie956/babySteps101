module programCounter(
	input clk,
			en,
			write,
	      shallIncrement,
			incrementMode,//PC+1 or PC+2
			reset,
	input [7:0] writeValue,
	output wire [7:0] valueOut, 
	output wire [7:0] valueOut2
);

	reg [7:0] pc;

	initial begin
		pc = 8'b0;
	end

	always@(posedge clk & en) begin
		if(reset == 1)
			pc <= 8'b0;
		else begin 
			if(write == 1)
				pc <= writeValue;
			else begin
				if(shallIncrement == 1) begin
					if(incrementMode == 0)
						pc <= pc + 8'b1000;
					else if(incrementMode == 1)
						pc <= pc + 8'b10000;
				end
			end
		end
		
	end

	assign valueOut = pc;
	assign valueOut2 = pc + 1'b1000;

endmodule
