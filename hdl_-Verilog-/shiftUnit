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
