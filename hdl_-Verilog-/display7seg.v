module display7seg(input [3:0] sel, output reg [0:6] port);
	always@(*)begin	
		case({sel[3:0]})
			4'b0000: port = 7'b0000001;
			4'b0001: port = 7'b1001111;
			4'b0010: port = 7'b0010010;
			4'b0011: port = 7'b0000110;
			4'b0100: port = 7'b1001100;
			4'b0101: port = 7'b0100100;
			4'b0110: port = 7'b0100000;
			4'b0111: port = 7'b0001111;
			4'b1000: port = 7'b0000000;
			4'b1001: port = 7'b0000100;
			default: port = 7'b1111111;
		endcase
	end
endmodule
