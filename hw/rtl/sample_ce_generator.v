`timescale 1ns / 1ps

module sample_ce_generator
#(
  parameter [31:0] CLK_PERIOD_NS = 10
)
(
  input clk,
  input rst,
  input [31:0] sample_period_ns,
  output ce
);

  // Any time there's a change on sample_period_ns, update terminal_cnt
  reg rst_1 = 0;
  reg update_terminal_cnt = 0;
  reg [31:0] sample_period_ns_1 = 0;
  always @ (posedge clk) begin
    rst_1 <= rst;
    sample_period_ns_1 <= sample_period_ns;
    update_terminal_cnt <= 0;
    if (!rst && rst_1) begin // Falling edge on reset
      update_terminal_cnt <= 1;
    end else begin
      if (sample_period_ns != sample_period_ns_1) begin
        update_terminal_cnt <= 1;
      end
    end
  end

  // Determine the number of clock ticks per sample period by floor(sample_period_ns/clk_period_ns)
  wire udiv_data_valid;
  wire [31:0] quotient;
  udiv
  #(
    .DWIDTH(32)
  )
  udiv_inst
  (
    .clk(clk),
    .rst(rst),
    .ce(1),
    .input_data_valid(update_terminal_cnt),
    .input_ready_for_data(), // Assuming software will always be slower
    .dividend(sample_period_ns),
    .divisor(CLK_PERIOD_NS),
    .output_data_valid(udiv_data_valid),
    .quotient(quotient),
    .remainder()
  );
  
  // Latch quotient
  reg [31:0] terminal_cnt;
  always @ (posedge clk) begin
    if (rst) begin
        terminal_cnt <= 0-1; // If 0, then it will go high immediately forever
    end else begin
        if (udiv_data_valid) begin
            terminal_cnt <= quotient;
        end
    end
  end

  // Main counter
  reg [31:0] cnt = 0;
  always @ (posedge clk) begin
    if (rst || ce) begin
      cnt <= 0;
    end else begin
      cnt <= cnt + 1'b1;
    end
  end

  assign ce = cnt == terminal_cnt;

endmodule