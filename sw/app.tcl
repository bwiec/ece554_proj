set platform_name [lindex $argv 0]
puts "The platform name is \"$platform_name\""

set xsa_path [lindex $argv 1]
puts "The xsa path is \"$xsa_path\""

set ws_path [lindex $argv 2]
puts "The ws path is \"$ws_path\""

setws $ws_path
platform active $platform_name

# Create the applications
#app create -name r5_ui -hw $xsa_path/$platform_name.xsa -proc psu_cortexr5_0 -os standalone -lang C++ -template {Empty Application (C++)}
app create -name r5_ui -platform $platform_name -proc psu_cortexr5_0 -os standalone -lang C++ -template {Empty Application (C++)}
importsources -name r5_ui -path "r5_ui/" -soft-link

#app create -name r5_function_generator -hw $xsa_path/$platform_name.xsa -proc psu_cortexr5_1 -os standalone -lang C++ -template {Empty Application (C++)}
app create -name r5_function_generator -platform $platform_name -proc psu_cortexr5_1 -os standalone -lang C++ -template {Empty Application (C++)}
importsources -name r5_function_generator -path "r5_function_generator/" -soft-link

# Build the applications
#app build -name r5_ui
#app build -name r5_function_generator