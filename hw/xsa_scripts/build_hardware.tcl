#-----------------------------------------------------------
# Abort if design already exists
#-----------------------------------------------------------
set proj_name "proj"
if { [file exists ${proj_name}] == 1 } {
	puts "Aborting. Project already exists"
	exit -1
}

#-----------------------------------------------------------
# Create project
#-----------------------------------------------------------
create_project ${proj_name} "${proj_name}" -part xczu9eg-ffvb1156-2-e
set_property BOARD_PART xilinx.com:kv260_som:part0:1.2 [current_project]

#-----------------------------------------------------------
# Add HDL source to design
#-----------------------------------------------------------
add_files -norecurse -fileset sources_1 "../rtl/"
set_property top top [current_fileset]

#-----------------------------------------------------------
# Create BD source
#-----------------------------------------------------------
source "../xsa_scripts/bd.tcl"

#-----------------------------------------------------------
# Generate BD output products
#-----------------------------------------------------------
generate_target all [get_files "${proj_name}/${proj_name}.srcs/sources_1/bd/design_1/design_1.bd"]
make_wrapper -files [get_files "${proj_name}/${proj_name}.srcs/sources_1/bd/design_1/design_1.bd"] -top
import_files -force -norecurse "${proj_name}/${proj_name}.srcs/sources_1/bd/design_1/hdl/design_1_wrapper.v"
set_property top "design_1_wrapper" [current_fileset]

#-----------------------------------------------------------
# Export to XSA
#-----------------------------------------------------------
set_property platform.platform_state "pre_synth" [current_project]
write_hw_platform -force -fixed "design_1_wrapper.xsa"
validate_hw_platform "design_1_wrapper.xsa" -verbose

exit

