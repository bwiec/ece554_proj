
.PHONY: all clean

all:  $(WS_DIR)/$(PLATFORM_NAME)/platform.spr

 $(WS_DIR)/$(PLATFORM_NAME)/platform.spr: $(XSA)
	mkdir -p $(WS_DIR)
	xsct -nodisp -sdx pfm.tcl $(PLATFORM_NAME) $(XSA_DIR) $(WS_DIR)

clean:
	rm -rf $(PLATFORM_NAME) $(WS_DIR) .Xil
