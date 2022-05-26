
`timescale 1ns / 1ps

module udiv
#(
	parameter DWIDTH = 8
)
(
	input               clk,
	input               rst,
	input               ce,
	input               input_data_valid,
	output              input_ready_for_data,
	input  [DWIDTH-1:0] dividend,
	input  [DWIDTH-1:0] divisor,
	output              output_data_valid,
	output [DWIDTH-1:0] quotient,
	output [DWIDTH-1:0] remainder
);

	// Input data capture register
	reg [DWIDTH-1:0] dividend_latched = 0;
	reg [DWIDTH-1:0] divisor_latched  = 0;
	always @ (posedge clk) begin
		if (ce && input_data_valid && input_ready_for_data) begin
			dividend_latched <= dividend;
			divisor_latched  <= divisor;
		end
	end

	// Main FSM
	reg                     input_ready_for_data_i = 0;
	reg [clog2(DWIDTH)-1:0] calc_cycle_cnt         = 0;
	reg                     capture_strobe         = 0;
	reg [1:0]               state                  = 0;
	localparam [1:0] IDLE    = 2'b00,
	                 CALC    = 2'b01,
					 CAPTURE = 2'b10;
	always @ (posedge clk) begin	
		if (rst) begin
			state <= 0;
		end else begin
			if (ce) begin
			    // Default assignments
                input_ready_for_data_i <= 1'b00;
                calc_cycle_cnt         <= 0;
                capture_strobe         <= 1'b0;
				case (state)
					IDLE: begin
						input_ready_for_data_i <= 1'b1;
						if (input_data_valid) begin
							input_ready_for_data_i <= 1'b0;
							state <= CALC;
						end
					end CALC: begin
						calc_cycle_cnt <= calc_cycle_cnt + 1'b1;
						if (calc_cycle_cnt == DWIDTH-1) begin
							state <= CAPTURE;
						end
					end CAPTURE: begin
						capture_strobe <= 1'b1;
						state <= IDLE;
					end default: begin
						state <= IDLE;
					end
						
				endcase
			end
		end
	end
	
	// Main arithmetic
	reg [DWIDTH-1:0] dividend_reg = 0;
	always @ (posedge clk) begin // Numerator shifting
		if (ce) begin
			if (state != CALC) begin
				dividend_reg <= dividend;
			end else begin
				dividend_reg <= dividend_reg << 1;
			end
		end
	end
	
	reg  [DWIDTH-1:0] remainder_reg         = 0;
	wire [DWIDTH-1:0] remainder_reg_concatd = {remainder_reg[DWIDTH-1:1], dividend_reg[DWIDTH-1]};
	wire [DWIDTH-1:0] remainder_mux         = (remainder_reg_concatd >= divisor_latched) ? (remainder_reg_concatd-divisor_latched) : remainder_reg_concatd;
	wire [DWIDTH-1:0] remainder_rsh         = remainder_mux << 1;
	always @ (posedge clk) begin // Denominator shifting
		if (state != CALC && ce) begin
			remainder_reg <= 0;
		end else begin
			if (ce) begin
				remainder_reg <= remainder_rsh;
			end
		end
	end
	
	reg [DWIDTH-1:0] quotient_sr = 0;
	always @ (posedge clk) begin // Quotient shifting
		if (state != CALC && ce) begin
			quotient_sr <= 0;
		end else begin
			if (ce) begin
				quotient_sr <= {quotient_sr[DWIDTH-2:0], (remainder_reg_concatd >= divisor_latched)};
			end
		end
	end
	
	// Output capture registers
	reg [DWIDTH-1:0] quotient_i          = 0;
	reg [DWIDTH-1:0] remainder_i         = 0;
	reg [DWIDTH-1:0] remainder_i_1       = 0;
	always @ (posedge clk) begin
		if (ce) begin
			remainder_i         <= remainder_mux;
			remainder_i_1       <= remainder_i;
			quotient_i          <= quotient_sr;
		end
	end
	
	// Final output wire assignments
	assign input_ready_for_data = input_ready_for_data_i;
	assign output_data_valid    = capture_strobe;
	assign quotient             = quotient_i;
	assign remainder            = (capture_strobe) ? remainder_i_1 : 0;
	
endmodule

