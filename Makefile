
TIME := $(shell date "+%Y_%m_%d")
export CWD := $(shell readlink -f .)

export XSA_DIR := $(CWD)/hw/build
export XSA := $(XSA_DIR)/design_1_wrapper.xsa


.SILENT:
.PHONY: all xsa publish clean
.ONESHELL:

all: xsa

xsa: $(XSA)
$(XSA):
	make -C hw all

publish: all
	cd ..
	zip -r $(TIME)_ece554_proj_bwiec.zip ece554_proj


clean:
	make -C hw clean
	#make -C sw clean
	rm -rf .Xil