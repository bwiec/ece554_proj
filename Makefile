
TIME := $(shell date "+%Y_%m_%d")
CWD := $(shell readlink -f .)

export PLATFORM_NAME := ece554_proj
export XSA_DIR := $(CWD)/hw/build
export XSA := $(XSA_DIR)/$(PLATFORM_NAME).xsa
export WS_DIR := $(CWD)/ws

.PHONY: all xsa bitstream platform sw publish clean
.ONESHELL:

all: xsa bitstream

xsa: $(XSA)
$(XSA):
	make -C hw all

bitstream: build/proj/proj.runs/top.bit
build/proj/proj.runs/top.bit: $(XSA)
	make -C hw bitstream

platform: 
	make -C platform all

sw: 
	make -C sw all

publish: all
	cd ..
	zip -r $(TIME)_ece554_proj_bwiec.zip ece554_proj

clean_hw:
	make -C hw clean

clean_platform:
	make -C platform clean

clean_sw:
	make -C sw clean

clean: clean_hw clean_platform clean_sw
	rm -rf .Xil
	rm -f *.jou *.log