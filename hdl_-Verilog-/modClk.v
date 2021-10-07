// f = 50M / 2^23 = 6Hz

module modClk(input CLOCK_50, reset, output newClk);
	reg [22:0] counter;

	always@(negedge CLOCK_50 or posedge reset)
		begin	
			if(reset == 1)
				counter[22:0] = 22'b0;
			else
				counter = counter + 1;
		end
		
	assign newClk = counter[22];
endmodule


/*
//achei, no caso o contador seria ate 8388608
//e para chegar ate esse numero a qnt de bits
//do binario precisa ser 23, pois 2^23 8.388.608
//pois se 50m/counter ~= 6hz

always @(posedge clk_in) begin
   count_20 <= count_20 + 1;
   if(count_20 == 1000000)
   begin
      count<=0;
      clk_out <= !clk_out;
   end
end
*/
