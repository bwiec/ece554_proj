set PLATFORM_NAME [lindex $argv 0]

open_project build/proj/proj.xpr
update_compile_order -fileset sources_1

launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1

write_hw_platform -fixed -hw -include_bit -force -file "build/${PLATFORM_NAME}.xsa"
