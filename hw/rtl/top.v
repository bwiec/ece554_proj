`timescale 1ns / 1ps

module top
(
);

  localparam [31:0] CLK_PERIOD_NS = 10;
  localparam [31:0] WDT_PERIOD_NS = 1000000; // 1-second

  wire clk_100mhz;
  wire resetn;
  wire wdt_irq;
  wire wdt_pet;
  wire [31:0] sample_period_ns;
  wire sample_ce;

  design_1_wrapper design_1_wraper_inst
  (
    .clk_100mhz(clk_100mhz),
    .resetn(resetn),
    .wdt_irq(wdt_irq),
    .wdt_pet(wdt_pet),
    .sample_period_ns(sample_period_ns),
    .sample_ce(sample_ce)
  );

  wdt
  #(
    .TERMINAL_CNT(WDT_PERIOD_NS/CLK_PERIOD_NS)
  )
  wdt_inst
  (
    .clk(clk_100mhz),
    .rst(!resetn),
    .pet(wdt_pet),
    .irq(wdt_irq)
  );

  sample_ce_generator
  #(
    .CLK_PERIOD_NS(CLK_PERIOD_NS)
  )
  sample_ce_generator_inst
  (
    .clk(clk),
    .rst(rst),
    .sample_period_ns(sample_period_ns),
    .ce(sample_ce)
  );

endmodule