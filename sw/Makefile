R5_UI_APP := $(WS_DIR)/$(PLATFORM_NAME)/r5_ui.elf
R5_FUNCTION_GENERATOR_APP := $(WS_DIR)/$(PLATFORM_NAME)/r5_function_generator.elf

.SILENT:
.PHONY: all clean

all: $(R5_UI_APP) $(R5_FUNCTION_GENERATOR_APP)

$(R5_UI_APP):
	xsct -nodisp -sdx app.tcl $(PLATFORM_NAME) $(XSA_DIR) $(WS_DIR)

$(R5_FUNCTION_GENERATOR_APP):
	echo "Not yet implemented"

clean:
	rm -f $(R5_UI_APP) $(R5_FUNCTION_GENERATOR_APP)