 module registerFile(  
	input clk,
			en_write,
			en_read,
	input [7:0] dataIn,
	input [3:0] regSelectW,
				   regSelectR,
	output [7:0] dataOut
);  
	reg [7:0] reg_mem [0:31];  
 
	always@(posedge clk) begin 
		if(en_write==1)
			reg_mem[regSelectW] <= dataIn;    
	end  
	assign dataOut = (en_read==1)?reg_mem[regSelectR]:8'bz;
 endmodule   
