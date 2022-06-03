.SILENT:

all: $(XSA)

$(XSA): xsa_scripts/project.tcl
	vivado -mode batch -notrace -source $^ $(PLATFORM_NAME)

bitstream: build/proj/proj.runs/top.bit
build/proj/proj.runs/top.bit:
	vivado -mode batch -notrace -source xsa_scripts/build_bitstream.tcl $(PLATFORM_NAME)

clean:
	rm -rf vivado* build .Xil *dynamic* *.log