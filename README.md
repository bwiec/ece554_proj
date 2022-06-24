# Introduction

This repository implements the design published in *Design of a Software-Defined Multi-Channel Function Generator* which demonstrates the design of a multi-channel function generator. The pattern generators are fully software defined allowing maximum flexibility. Four different patterns are chosen as examples to demonstrate the ability to generate any desired waveform using simple software implementation. The design is built on an embedded FPGA/SoC platform (AMD Zynq Ultrascale+) which proves feasibility to deploy this design in a real-world product. 

# Pre-requisites
This design was tested on an Ubuntu 20.04 build machine.

## Hardware
* Xilinx ZCU102
* Micro USB cable
* Second Micro USB cable or other JTAG debugger

## Software
* Xilinx Vitis 2021.2
* Xilinx Vivado 2021.2

# Building the Design
Execute the following steps to build the design

## Setting Up the Shell Environment
Prior to running the Makefile to build this design, you must first source the Vitis and Petalinux settings script to set up your environment properly

```bash
source <xilinx_install>/Vitis/2021.2/settings64.sh
```
## Building
1. Clone the repository
```bash
git clone https://github.com/bwiec/ece554_proj
```
2. Run `make`
```bash
make
```
Upon successful completion of the build, a directory called `ws` will be created. This directory is a Vitis workspace.

# Running the Design
Once the build is complete, follow these steps to run the design on the target.

## Setting Up the Hardware
1. Connect the 6-pin power connector to the ZCU102
2. Connect a micro USB cable from the USB UART connector on the board to a host PC
3. On the host PC, open a serial terminal connection to this UART COM port at 115200 baud rate
4. Connect another micro USB cable from the host PC to the USB JTAG connector on the board. Alternatively, connect a debugger to the JTAG port
5. Set the boot mode swtich SW6 to JTAG
6. Power on the board

## Launching the Applications
Having successfully powered up the board and connected to it, follow these steps to launch the two R5 applications
1. Launch Vitis and select to the `ws` directory
2. Replace the contents of both `lscript.ld` files in this project with the ones in the `src` directories
3. Build the project 
4. Right-click one of the r5_* applications and select `Debug Configurations` then create a new `TCF Single Application Debug` configuration
5. Select the `Application` tab then make sure both boxes are checked for the `psu_cortexr5_0` and `psu_cortexr5_1` cores and ensure that `psu_cortexr5_0` is being loaded with `r5_ui.elf` and that `psu_cortexr5_1` is loaded with `r5_function_generator.elf`.
6. Click `Debug`. This will program the FPGA bitstream, load the elf files, and start the debugger.

At this point, both applications are running and you should see the main menu printed in the UART terminal 

## Viewing the Output Waveforms
Now that the applications are up and running, view the output waveforms by:
1. Launch Vivado
2. Select `Open Hardware Manager` then `Open Target` and connect to your JTAG cable
3. Open the `hw_ila_1` window
4. In the `Trigger Setup` tab, add the signals `axi_fifo_mm_s_0_AXI_STR_TXD_TREADY` and `axi_fifo_mm_s_0_AXI_STR_TXD_TVALID`, set both their `Values` to `1`, and set the trigger condition to `and`
5. In the `Settings` tab, change the `Number of Windows` to `50`
6. Arm the ILA

At this point, the ILA window will capture samples and update the waveform. Initially, all the waveforms (i.e. all the `axi_fifo_mm_s_0_AXI_STR_TXD_TDATA` signals) will be blank because no channels have been turned on yet.

Next, turn on the waveforms and make any desired changes via the UART menu. Updated waveforms can again be captured by running step 6 above to arm the ILA.
