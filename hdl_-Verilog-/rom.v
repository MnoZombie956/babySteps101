module ROM(
	input en_read,
			en_read1,
			en_read2,
	input [7:0] address1,
					address2,
	output [7:0] data1Out,
					 data2Out	
);	
	reg [7:0] rom_mem [0:255]; // matriz de 256 itens indexaveis, profundidade de 8 bits
	
	initial begin
		$readmemb("~/instrMemory.txt", rom_mem); // memory file
	end
	
	assign data1Out = (en_read & en_read1) ? rom_mem[address1] : 8'bz;
	assign data2Out = (en_read & en_read2) ? rom_mem[address2] : 8'bz;
endmodule
