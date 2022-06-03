set platform_name [lindex $argv 0]
puts "The platform name is \"$platform_name\""

set xsa_path [lindex $argv 1]
puts "The xsa path is \"$xsa_path\""

set ws_path [lindex $argv 2]
puts "The ws path is \"$ws_path\""

setws $ws_path

platform create -name ${platform_name} -desc "Platform for ECE554 final project targeting KV260 with FIFOs and WDT in the PL and including baremetal BSPs for both R5 cores" -hw $xsa_path/$platform_name.xsa

domain create -name r5_ui_dom -proc psu_cortexr5_0 -os standalone
domain create -name r5_function_generator_dom -proc psu_cortexr5_1 -os standalone

platform generate
