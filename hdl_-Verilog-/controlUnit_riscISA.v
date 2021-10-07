/* nanoRisc controlUnit */
module controlUnit(
	//instructions, branch's comparassion
	input [7:0] rom_data_out1,
	input [1:0] cmp_data_out,
	//para control signals
	output reg rom_en_read1, rom_en_read2,
	output reg pc_en_w,pc_en_inc,pc_incM,pc_rst,
	output reg ram_en_r,ram_en_w,
	output reg rb_en_w,rb_en_r, output reg [3:0] rb_reg_w_select,rb_reg_r_select,
	output reg [3:0] alu_op,
	output reg acc_en_w,acc_reset,
	output reg s_en,s_reset,s_op,s_en_op,s_en_popQuantity,s_en_noOpPop,
	output reg [2:0]su_sa,
	output reg su_sd,
	//para control mux signals
	output reg mux_pc_data_in,mux_ram_data_in,mux_su_data_in,
	output reg [1:0]mux_ram_adrs_in_w,mux_ram_adrs_in_r,mux_stk_data_in,mux_acc_data_in,mux_alu_data_in_a,mux_alu_data_in_b,
	output reg [2:0] mux_reg_data_in,
	//para registradores internos de estados
	output wire c_mode_on_unsigned,c_mode_on_aluIn,c_mode_on_stackRepo,
	output reg shall_branch
); 	
	
	reg mode_on_unsigned,mode_on_aluIn,mode_on_stackRepo;
	assign c_mode_on_unsigned=mode_on_unsigned;
	assign c_mode_on_aluIn=mode_on_aluIn;
	assign c_mode_on_stackRepo=mode_on_stackRepo;
	
	wire [3:0] opcode = rom_data_out1[7:4];
	wire [3:0] functional = rom_data_out1[3:0];
	
	initial begin
		mode_on_aluIn<=0;
		mode_on_stackRepo<=0;
		mode_on_unsigned<=0;	
		pc_en_w=0;
		pc_en_inc=1;
		pc_incM=0;//alterado caso seja standard ou linked
		pc_rst=0;
		rom_en_read1=1;
		rom_en_read2=1;
	end
	
	always@(*)begin
		case(opcode) 
			4'b0000: begin//lwm
				pc_incM<=1;
				ram_en_r<=1;
				rb_en_w<=1;
				rb_reg_w_select<=functional;	
				
				mux_ram_adrs_in_r<=1;
				mux_reg_data_in<=3'b10;
				
				pc_en_w<=0;
				ram_en_w<=0;
				rb_en_r<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;				
			end				
			4'b0001: begin//lwi
				pc_incM<=1;
				rb_en_w<=1;
				rb_reg_w_select<=functional;
		
				mux_reg_data_in<=3'b11;		
				
				pc_en_w<=0;
				ram_en_r<=0;
				ram_en_w<=0;
				rb_en_r<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b0010: begin//swm
				pc_incM<=1;
				ram_en_w<=1;
				rb_en_r<=1;
				rb_reg_r_select<=functional;
	
				mux_ram_adrs_in_w<=1;
				mux_ram_data_in<=0;
				
				pc_en_w<=0;
				ram_en_r<=0;
				rb_en_w<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b0011: begin//swi
				pc_incM<=1;
				rb_en_r<=1;
				ram_en_w<=1;
				rb_reg_r_select<=functional;

				mux_ram_adrs_in_w<=0;
				mux_ram_data_in<=1;
				
				pc_en_w<=0;
				ram_en_r<=0;
				rb_en_w<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b0100: begin//atr
				pc_incM<=0;
				rb_en_w<=1;
				rb_reg_w_select<=functional;

				mux_reg_data_in<=2'b00;
				
				pc_en_w<=0;
				ram_en_r<=0;
				ram_en_w<=0;
				rb_en_r<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b0101: begin//rta
				pc_incM<=0;
				rb_en_r<=1;
				rb_reg_r_select<=functional;

				mux_acc_data_in<=2'b01;
				
				pc_en_w<=0;
				ram_en_r<=0;
				ram_en_w<=0;
				rb_en_w<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b0110: begin
				if(functional[3]==0)begin//slrr
					pc_incM<=0;
					rb_en_r<=1;
					rb_en_w<=1;
					rb_reg_w_select<=functional[2:0];
					rb_reg_r_select<=functional[2:0];
					su_sa<=1;
					su_sd<=1;

					mux_reg_data_in<=3'b100;
					mux_su_data_in<=1;	
	
					pc_en_w<=0;
					ram_en_r<=0;
					ram_en_w<=0;
					acc_en_w<=0;
					acc_reset<=0;
					s_en<=0;
					s_reset<=0;
					shall_branch<=0;	
				end
				else if(functional[3]==1)begin//slra
					pc_incM<=0;
					acc_en_w<=1;
					su_sa<=functional[2:0];
					su_sd<=1;
					
					mux_acc_data_in<=2'b10;
					mux_su_data_in<=0;
					
					pc_en_w<=0;
					ram_en_r<=0;
					ram_en_w<=0;
					rb_en_w<=0;
					rb_en_r<=0;
					acc_reset<=0;
					s_en<=0;
					s_reset<=0;
					shall_branch<=0;
				end
			end
			4'b0111: begin
				if(functional[3]==0)begin//sllr
					pc_incM<=0;
					rb_en_r<=1;
					rb_en_w<=1;
					rb_reg_w_select<=functional[2:0];
					rb_reg_r_select<=functional[2:0];
					su_sa<=1;
					su_sd<=0;

					mux_reg_data_in<=3'b100;
					mux_su_data_in<=2'b01;	
					
					pc_en_w<=0;
					ram_en_r<=0;
					ram_en_w<=0;
					acc_en_w<=0;
					acc_reset<=0;
					s_en<=0;
					s_reset<=0;
					shall_branch<=0;

				end
				else if(functional[3]==1)begin//slla
					pc_incM<=0;
					acc_en_w<=1;
					su_sa<=functional[2:0];
					su_sd<=0;
					
					mux_acc_data_in<=2'b10;
					mux_su_data_in<=0;	
					
					pc_en_w<=0;
					ram_en_r<=0;
					ram_en_w<=0;
					rb_en_w<=0;
					rb_en_r<=0;
					acc_reset<=0;
					s_en<=0;
					s_reset<=0;
					shall_branch<=0;
				end
			end
			4'b1000: begin // ALU operation
				alu_op <= functional;//c 3
				if(mode_on_aluIn==0)begin//acc = acc op pilhaTop
					case(functional)
						4'b0000,4'b0010,4'b0100,4'b0101,
						4'b0110,4'b0111,4'b1000,4'b1001,
						4'b1010,4'b1100,4'b1110        : begin
						//add,sub,and,or,nand,nor,xor,xnor,mul,div,not
							pc_incM<=0;//c 1
							acc_en_w <= 1;//c 5
							
							mux_acc_data_in <= 2'b11;//c 5 
							mux_alu_data_in_a <= 1;//c 2
							mux_alu_data_in_b <= 0;//c 2
							
							pc_en_w<=0;
							ram_en_r<=0;
							ram_en_w<=0;
							rb_en_w<=0;
							rb_en_r<=0;
							acc_reset<=0;
							s_en<=1;
							s_reset<=0;
							shall_branch<=0;
							
							if(mode_on_stackRepo==1) begin
								s_en_noOpPop <= 1;
								s_en_popQuantity <= 0;								
							end
							else if(mode_on_stackRepo==0)
								s_en_noOpPop <= 0;
						end
						4'b0001,4'b0011,4'b1011,4'b1101: begin
						//addi, subi, muli, divi
							pc_incM<=1;//c 1
							acc_en_w <= 1;//c 5
							
							mux_acc_data_in <= 2'b11;//c 5 
							mux_alu_data_in_a <= 1;//c 2
							mux_alu_data_in_b <= 2'b10;//c 2
							
							pc_en_w<=0;
							ram_en_r<=0;
							ram_en_w<=0;
							rb_en_w<=0;
							rb_en_r<=0;
							acc_reset<=0;
							s_en<=0;
							s_reset<=0;
							shall_branch<=0;
						end
						4'b1111: begin//comp
							pc_incM<=0;												
							mux_alu_data_in_a <= 1;//c 2
							mux_alu_data_in_b <= 0;//c 2	

							pc_en_w<=0;
							ram_en_r<=0;
							ram_en_w<=0;
							rb_en_w<=0;
							rb_en_r<=0;
							acc_en_w<=0;
							acc_reset<=0;
							s_en<=1;
							s_reset<=0;
							shall_branch<=0;
							
							if(mode_on_stackRepo==1) begin
								s_en_noOpPop <= 1;
								s_en_popQuantity <= 0;								
							end
							else if(mode_on_stackRepo==0)begin
								s_en_noOpPop <= 0;
							end						
						end
					endcase
				end
				else if(mode_on_aluIn==1)begin//pilhaTop = pilhaTop op pilhaTop2
					case(functional)
						4'b0000,4'b0010,4'b0100,4'b0101,4'b0110,4'b0111,4'b1000,4'b1001,4'b1010,4'b1100,4'b1110: begin
						//add,sub,and,or,nand,nor,xor,xnor,mul,div,not
							pc_incM<=0;//c 1
							
							mux_alu_data_in_a <= 0;//c 2
							mux_alu_data_in_b <= 1;//c 2
							
							s_en_op<=1;
							s_op<=1;//c 5, push
							mux_stk_data_in<=0;
							
							pc_en_w<=0;
							ram_en_r<=0;
							ram_en_w<=0;
							rb_en_w<=0;
							rb_en_r<=0;
							acc_en_w<=0;
							acc_reset<=0;
							s_en<=1;
							s_reset<=0;
							shall_branch<=0;
							
							if(mode_on_stackRepo==1) begin//c 3
								s_en_noOpPop <= 1;
								s_en_popQuantity <= 1;								
							end
							else if(mode_on_stackRepo==0)
								s_en_noOpPop <= 0;
						end
						4'b0001,4'b0011,4'b1011,4'b1101: begin
						//addi,subi,muli,divi
							pc_incM<=1;//c 1
							
							mux_alu_data_in_a <= 0;//c 2
							mux_alu_data_in_b <= 2'b10;//c 2
							
							s_en_op<=1;
							s_op<=1;//c 5, push
							mux_stk_data_in<=0;
							
							pc_en_w<=0;
							ram_en_r<=0;
							ram_en_w<=0;
							rb_en_w<=0;
							rb_en_r<=0;
							acc_en_w<=0;
							acc_reset<=0;
							s_en<=1;
							s_reset<=0;
							shall_branch<=0;
							
							if(mode_on_stackRepo==1) begin//c 3
								s_en_noOpPop <= 1;
								s_en_popQuantity <= 0;								
							end
							else if(mode_on_stackRepo==0)
								s_en_noOpPop <= 0;
						end
						4'b1111: begin//comp
							pc_incM<=0;		
							mux_alu_data_in_a <= 0;//c 2
							mux_alu_data_in_b <= 1;//c 2
							
							pc_en_w<=0;
							ram_en_r<=0;
							ram_en_w<=0;
							rb_en_w<=0;
							rb_en_r<=0;
							acc_en_w<=0;
							acc_reset<=0;
							s_en<=0;
							s_reset<=0;
							shall_branch<=0;
							
							if(mode_on_stackRepo==1) begin
								s_en_noOpPop <= 1;
								s_en_popQuantity <= 1;								
							end
							else if(mode_on_stackRepo==0)begin
								s_en_noOpPop <= 0;
							end
						end
					endcase				
				end	
			end
			4'b1001: begin//pushr
				pc_incM<=0;
				mux_stk_data_in<=2'b10;
				s_en_op<=1;
				s_op<=1;
				rb_en_r<=1;
				rb_reg_r_select<=functional;		
		
				pc_en_w<=0;
				ram_en_r<=0;
				ram_en_w<=0;
				rb_en_w<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=1;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b1010: begin
				case(functional)
					4'b0000: begin //pushi
						pc_incM<=1;
						mux_stk_data_in<=2'b11;
						s_en_op<=1;
						s_op<=1;
						
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=1;
						s_reset<=0;
						shall_branch<=0;
					end
					4'b0001: begin //uns
						pc_incM<=0;
						
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;
						shall_branch<=0;
						if(mode_on_unsigned==0)
							mode_on_unsigned<=1;
						else if(mode_on_unsigned==1)
							mode_on_unsigned<=1;
					end
					4'b0010:begin//pop
						pc_incM<=0;		
						
						s_en_op<=1;
						s_op<=0;			
			
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=1;
						s_reset<=0;
						shall_branch<=0;
					end
					4'b0011:begin//srst
						pc_incM<=0;		
						
						s_en<=1;
						s_reset<=1;		
				
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						shall_branch<=0;
					end
					4'b0100:begin//arst
						pc_incM<=0;		
						acc_reset<=1;	
				
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						s_en<=0;
						s_reset<=0;
						shall_branch<=0;
					end
					4'b0101:begin//srep
						pc_incM<=0;
						
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;
						shall_branch<=0;
						
						if(mode_on_stackRepo==0)
							mode_on_stackRepo<=1;
						else if(mode_on_stackRepo==1)
							mode_on_stackRepo<=0;
						
					end
					4'b0110:begin//aaim
						pc_incM<=0;
						
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;
						shall_branch<=0;
						
						if(mode_on_aluIn==0)
							mode_on_aluIn<=1;
						else if(mode_on_aluIn==1)
							mode_on_aluIn<=0;
					end
				endcase
			end
			4'b1011: begin
				case(functional)
					4'b0000:begin//bi 
						pc_incM<=1;
						pc_en_w<=1;
						mux_pc_data_in<=2'b10;
						shall_branch<=1;
						
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;
					end
					4'b0001,4'b0010,4'b0011,4'b0101:begin
					//bil,bie,big,bne
						pc_incM<=1;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;		
						if(
							(cmp_data_out==2'b00 && functional==4'b0001)//condicao bil
						   ||(cmp_data_out==2'b01 && functional==4'b0010)//bie
							||(cmp_data_out==2'b10 && functional==4'b0011)//big
							||(cmp_data_out!=2'b01 && functional==4'b0101)//bne
						)begin
							pc_en_w<=1;
							mux_pc_data_in<=2'b10;
							shall_branch<=1;	
						end
						else begin
							pc_en_w<=0;
							shall_branch<=0;
						end
					end
					4'b0100:begin//bal
						pc_incM<=1;
						pc_en_w<=1;
						rb_en_w<=1;					
						rb_reg_w_select<=4'b1010;
						
						mux_reg_data_in<=3'b101;
						mux_pc_data_in<=2'b10;					
						shall_branch<=1;

						ram_en_r<=0;
						ram_en_w<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;	
					end
					4'b0101:begin//halt
						pc_en_inc<=0;
						
						pc_en_w<=0;
						ram_en_r<=0;
						ram_en_w<=0;
						rb_en_w<=0;
						rb_en_r<=0;
						acc_en_w<=0;
						acc_reset<=0;
						s_en<=0;
						s_reset<=0;
						shall_branch<=0;
					end
				endcase
			end
			4'b1100: begin//br
				rb_en_r<=1;
				pc_en_w<=1;
				rb_reg_r_select<=functional;
				mux_pc_data_in<=2'b01;
				
				ram_en_r<=0;
				ram_en_w<=0;
				rb_en_w<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=1;
			end
			4'b1101: begin//lwr
				pc_incM<=1;
				ram_en_r<=1;
				rb_en_r<=1;
				rb_en_w<=1;
				rb_reg_r_select<=4'b1100;
				rb_reg_w_select<=functional;
				mux_ram_adrs_in_r<=2'b10;
				mux_alu_data_in_a<=2'b10;//reg
				mux_alu_data_in_b<=2'b10;//pure
				
				pc_en_w<=0;
				ram_en_w<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
			4'b1110: begin//swr
				pc_incM<=1;
				ram_en_w<=1;
				rb_en_r<=1;
				rb_en_w<=1;
				rb_reg_r_select<=functional;
				rb_reg_w_select<=4'b1110;
				mux_ram_adrs_in_w<=2'b10;
				mux_alu_data_in_a<=2'b10;//reg
				mux_alu_data_in_b<=2'b10;//pure
				
				pc_en_w<=0;
				ram_en_r<=0;
				acc_en_w<=0;
				acc_reset<=0;
				s_en<=0;
				s_reset<=0;
				shall_branch<=0;
			end
		endcase
	end
endmodule
