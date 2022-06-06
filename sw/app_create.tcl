set platform_name [lindex $argv 0]
puts "The platform name is \"$platform_name\""

set ws_path [lindex $argv 1]
puts "The ws path is \"$ws_path\""

set app_name [lindex $argv 2]
puts "The app_name is \"$app_name\""

setws ${ws_path}
platform active ${platform_name}

set r5_core_num 0
if {${app_name} == "r5_ui"} {
  set r5_core_num 0
} elseif  {${app_name} == "r5_function_generator"} {
  set r5_core_num 1
} else {
  puts "ERROR! Illegal app name"
  exit
}

app create -name ${app_name} \
  -platform ${platform_name} \
  -proc psu_cortexr5_${r5_core_num} \
  -os standalone -lang C++ -template {Empty Application (C++)}

set CWD [pwd]
importsources -name ${app_name} -path "${CWD}/${app_name}/src" -soft-link
importsources -name ${app_name} -path "${CWD}/common/src" -soft-link

app config -name ${app_name} -add include-path "${CWD}/${app_name}/include"
app config -name ${app_name} -add include-path "${CWD}/common/include"

