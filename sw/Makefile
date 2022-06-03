APP_PRJS := $(WS_DIR)/r5_ui/r5_ui.prj \
					  $(WS_DIR)/r5_function_generator/r5_function_generator.prj
APPS := $(WS_DIR)/r5_ui/Debug/r5_ui.elf \
			  $(WS_DIR)/r5_function_generator/Debug/r5_function_generator.elf

.PHONY: all clean

all: $(APPS)

$(APP_PRJS):
	xsct -nodisp -sdx app_create.tcl $(PLATFORM_NAME) $(WS_DIR) $(basename $(@F))

$(APPS): $(APP_PRJS)
	xsct -nodisp -sdx app_build.tcl $(PLATFORM_NAME) $(WS_DIR) $(basename $(@F))

clean:
	rm -rf .Xil
	xsct -nodisp -sdx -eval "setws $(WS_DIR); platform active $(PLATFORM_NAME); app remove r5_ui"
	xsct -nodisp -sdx -eval "setws $(WS_DIR); platform active $(PLATFORM_NAME); app remove r5_function_generator"