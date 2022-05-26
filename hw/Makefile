.SILENT:

all: $(XSA)

$(XSA): xsa_scripts/project.tcl
	vivado -mode batch -notrace -source $^

bitstream: build/proj/proj.runs/top.bit
build/proj/proj.runs/top.bit:
	$(VIVADO) -mode batch -notrace -source xsa_scripts/build_bitstream.tcl

clean:
	rm -rf vivado* build .Xil *dynamic* *.log