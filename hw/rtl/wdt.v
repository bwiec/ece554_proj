`timescale 1ns / 1ps

module wdt
#(
  parameter TERMINAL_CNT = 10000 
)
(
  input clk,
  input rst,
  input pet,
  output irq
);

  // Main counter
  localparam DWIDTH = $clog2(TERMINAL_CNT);
  reg [DWIDTH:0] cnt = 0;
  always @ (posedge clk) begin
    if (rst || pet) begin
      cnt <= 0;
    end else begin
      cnt <= cnt + 1'b1;
    end
  end

  // If interrupt happens, latch it until reset (NOT pet)
  reg irq_i = 0;
  always @ (posedge clk) begin
    if (rst) begin
      irq_i <= 0;
    end else begin
      if (cnt == TERMINAL_CNT) begin
        irq_i <= 1;
      end
    end
  end
  assign irq = irq_i;

endmodule